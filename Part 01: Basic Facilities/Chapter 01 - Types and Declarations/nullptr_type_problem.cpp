
/*
**  (C++) Demonstration:
**      Problem that `nullptr_t` solves.
*/

#include <iostream>
using namespace std;

void f(void *)  { cout << "void *"  << endl; }
void f(int)     { cout << "int"     << endl; }

int main(void)
{
    f(NULL); /* nullptr_type_problem.cpp:15:5: error: call to 'f' is ambiguous
                    f(NULL);    nullptr_type_problem.cpp:16:5: error: call to 'f' is ambiguous
                    ^
                nullptr_type_problem.cpp:10:6: note: candidate function
                void f(void *)  { cout << "void *"  << endl; }
                     ^
                nullptr_type_problem.cpp:11:6: note: candidate function
                void f(int)     { cout << "int"     << endl; }
                     ^
                1 error generated.
            */
}

/* Compiled with: clang++ -std=c++2a
 *
 * Version:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 */

