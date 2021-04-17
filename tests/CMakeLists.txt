cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(simple VERSION 1.0.0 DESCRIPTION "Simple test")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Load the libraries
find_package(CppDebugger REQUIRED)



##### CPPDEBUGGER TARGET #####
# Specify which file will compile to the library
add_executable(simple ${PROJECT_SOURCE_DIR}/simple.cpp)
# Add which libraries to link
target_link_libraries(simple PUBLIC
                      cppdbg
                      )
