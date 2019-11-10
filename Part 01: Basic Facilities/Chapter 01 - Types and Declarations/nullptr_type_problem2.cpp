
/*
**  (C++) Demonstration:
**      Problem #2 that `nullptr_t` solves.
*/

#include <iostream>
#include <cstddef>

using namespace std;

void f(int* pi)         { cout << "int * overload\n";     }
void f(double* pd)      { cout << "double * overload\n";  }
void f(nullptr_t nullp) { cout << "nullptr_t overload\n"; }

int main()
{
    double* pd;
    int* pi;

    f(pi);
    f(pd);
    f(nullptr);  // would be ambiguous without void f(nullptr_t)
    // f(0);     // ambiguous call: all three functions are candidates
    // f(NULL);  // ambiguous if NULL is an integral null pointer constant
                 // (as is the case in most implementations)
}

/* Output:
int * overload
double * overload
nullptr_t overload
*/

/* Compiled with: clang++ -std=c++2a -w
 *
 * Version:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 */
