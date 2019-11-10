
/*
**  (C++) Demonstration:
**      Solution that `nullptr_t` provides.
*/

#include <iostream>
using namespace std;

void f(void *)  { cout << "void *"  << endl; }
void f(int)     { cout << "int"     << endl; }

int main(void)
{
    f(0);
    f(nullptr);
}

/* Output:
int
void *
*/

/* Compiled with: clang++ -std=c++2a
 *
 * Version:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 */
