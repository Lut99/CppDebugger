# CppDebugger
Simple debugging library that can be used to get more sophisticated debugging information in C++ when enabled, like stack traces and pretty logging.

Below you'll find a quick start guide, moving you through installing, using and then linking the library. For more in-depth information, visit the [wiki]().

## Installation
To install the library on your computer, first make sure you have cmake and git installed.
Then, download this directory as a ZIP (see the [releases](https://github.com/Lut99/CppDebugger/releases)), extract it to some reachable location on your device, and then ```cd``` into it.

Once inside of the project folder, create the build directory and cd into it:
```
mkdir build
cd build
```
Now that you're out of the source, you can safely generate the build files for your system using cmake:
```
cmake ../
```
With the build files generated, it's time to compile the source code itself:
```
cmake --build .
```
If the compilation was successful, you can then install the library on your system with:
```
sudo cmake --install .
```
You might consider making a note of the files that are being installed so you can remove them.

The library should now be fully installed on your system, so you can start to use it in your C++-projects.

### Uninstallation
If you want to uninstall the library, simply remove the list of files that you noted during installation. If you forgot which files it are, simply go through the installation process again to get a new list of files and where they are for your system (they won't be reinstalled). Note that you should use the same version as you installed, as there may be irregularities between the lists otherwise.


## Usage
Once you have installed the library, you can use it from your code via the macro interfaces. We stronly advice you to use the macros and not any functions defined by the library, as that ensures that the library can be easily disabled during compilation.

The installation takes care of installing the header file somewhere where your compiler is very likely to find the file, and thus, to use anything of the debugger, you can simply include it from a library path:
```c++
#include <CppDebugger.hpp>
```
With that included, you can now use any of the Debugger's features.

### Stacktraces
The most powerful thing the library does is adding stacktraces to your code whenever an error occurs. To let the library keep track of where you are, you should make use of the DENTER/DRETURN pair:
```c++
// Shows the usage of DENTER/RETURN
int example_return_function() {
    DENTER("example_return_function");

    ...

    DRETURN 0;
}
```
The string passed to DENTER is the name that the library thinks your function is called. While it's usually best to make this your function header/function name, you can get creative and name it how you like. It is recommended to make the names unique, though (some functions use these names as unique id's: see [here](), for example).

We advice you to try to place the ```DENTER``` on the first line of the function, as the line above the ```DENTER```-statement is marked as the function's location in the source file.

Alternatively, if you don't want to use a return statement, you can also use ```DLEAVE``` to pop the function from the stacktrace but not return yet. It can thus be used for void-functions (although you can also use ```DRETURN``` without value).

### Logging
Another useful feature, that goes hand-in-hand with the stacktracing, is logging. The debugger allows you to log any string to the terminal, accompanied by some _severity value_ that lets the debugger add some extra information (see below). If you want to print non-string values, we recommend casting one of them to a ```std::string```, and using that to combine values together (also look at ```std::to_string```).

The most-used severity values will likely be 'info' (just prints your message), 'warning' (prints your message with the function where the warning occurred) and 'fatal' (prints your message, the stacktrace and then throws an exception). To see each of them in action:
```c++
// The 'info'-severity value
DLOG(CppDebugger::Severity::info, "An informative message");

// The 'warning'-severity value
DLOG(CppDebugger::Severity::warning, "A warning has occurred!");

// The 'fatal'-severity value
DLOG(CppDebugger::Severity::fatal, "A non-recoverable message has occurred!");
```
Note that, while info and warning won't print anything if the debugger is disabled, fatal will simply be throwing the exception it would otherwise throw to make sure your code terminates.

To make your life easier, you can also import the severity values in the toplevel namespace:
```c++
using namespace CppDebugger::SeverityValues;
```
after which you can just use ```info```, ```warning```, etc directly.

### Full example
To combine the two most-used features, a hello-world program in C++ using the debugger may look like this:
```c++
#include <exception>
#include <CppDebugger.hpp>

using namespace CppDebugger::SeverityValues;

int main() {
    DENTER("main");
    // With the 'DENTER' statement, we tell the debugger that main is our current function

    // We add a toplevel try/catch to neatly exit fatal log messages
    try {
        // Run your code here!
        DLOG(info, "Hello, world!");
        DLOG(warning, "Uh-oh, world!");
        DLOG(fatal, "That went wrong, world!");
    } catch (CppDebugger::Exception& e) {
        // Return that it failed
        DRETURN -1;
    } catch (std::exception& e) {
        // A nice thing of having a toplevel try/catch is that we can re-throw any standard exception
        try { DLOG(fatal, e.what()); }
        catch (CppDebugger::Exception& e) { DRETURN -1; }
    }

    // If no exceptions occurred, we end up here, where we return using the debugger's return to pop main correctly.
    DRETURN 0;
}
```

## Linking your code
Linking the CppDebugger library to your code is very simple once it is installed. It can either be done manually (for usage in a Makefile, for example) or using cmake.

### Manually
To manually link the CppDebugger to your code, simply add the dynamic library as ```-lcppdbg``` at the end of your command. For example:
```
g++ -std=c++17 -O2 -o foo foo.cpp -lcppdbg
```
This will always add the debugger as enabled. However, when you are compiling your code for release, you can disable it entirely by adding ```-DNDEBUG``` to your code. This way, you needn't remove the debugger from your code when releasing your project.

### Using CMake
To link the debugger using cmake, you can add the debugger as a package once you installed it:
```cmake
find_package(CppDebugger REQUIRED)
```
Then, add the library as a link target for your executable:
```cmake
target_link_libraries(foo PUBLIC debug cppdbg)
```
We recommend to add the library with the 'debug' keyword, so CMake only links it when ```CMAKE_BUILD_TYPE=Debug``` and not when ```CMAKE_BUILD_TYPE=Release```. Similarly, CMake also takes care of settings ```-DNDEBUG``` for you based on the build type.

With that, you should successfully be able to use the most-used features of the debugger. However, for more advanced or specific uses, such as using the application for multiple threads, please check out our [wiki]().

## Bug reporting
If you encounter any bugs, please leave an issue here on Github with the appropriate tags. Similarly, if you have a suggestion or something that you think doesn't work, let us know via an issue too.
