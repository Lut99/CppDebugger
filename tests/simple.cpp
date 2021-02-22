/* SIMPLE.cpp
 *   by Lut99
 *
 * Created:
 *   2/22/2021, 4:30:58 PM
 * Last edited:
 *   2/22/2021, 4:34:00 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Simple file to test the installed debugger
**/

#include <CppDebugger.hpp>

using namespace std;
using namespace CppDebugger::SeverityValues;


/* Entrypoint */
int main() {
    DSTART("main"); DENTER("main");

    DLOG(info, "Hello, world!");
    DLOG(auxillary, "Hello, wolrd!");
    DLOG(warning, "This is going down...");
    DLOG(fatal, "Jup, it crashed");

    DRETURN 0;
}
