/* SIMPLE.cpp
 *   by Lut99
 *
 * Created:
 *   2/22/2021, 4:30:58 PM
 * Last edited:
 *   17/04/2021, 17:06:38
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Simple file to test the installed debugger
**/

#include <CppDebugger.hpp>

using namespace std;
using namespace CppDebugger::SeverityValues;


/* Twice nested function */
void nnested() {
    DENTER("nnested");
    DLOG(nonfatal, "Nested #2");
    DRETURN;
}
/* Nested function */
void nested() {
    DENTER("nested");
    DLOG(nonfatal, "Nested #1");
    nnested();
    DRETURN;
}
/* Entrypoint */
int main() {
    DSTART("main"); DENTER("main");

    try {
        DLOG(info, "Hello, world!");
        DINDENT;
        DLOG(auxillary, "Hello, wolrd!");
        DLOG(warning, "This is going down...");
        nested();
        DDEDENT;
        DLOG(fatal, "Jup, it crashed");
    } catch (CppDebugger::Fatal& e) {
        DRETURN -1;
    }

    DRETURN 0;
}
