
/*
**	(C++) Example:
**		Complex literals.
*/

#include <iostream>  /* Standard Library of Input and Output */
#include <complex>   /* Standard's Complex Header */

using namespace std;

int main(void)
{

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

	( 6.25f + 9.2if );   // literal of type:  complex <float>
	( 6.25  + 9.2i  );   // literal of type:  complex <double>
	( 6.25l + 9.2il );   // literal of type:  complex <long double>

	( 9.2if );           // complex literal of value:  ( 0.0f + 9.2if )
	( 9.2i  );           // complex literal of value:  ( 0.0  + 9.2i  )
	( 9.2il );           // complex literal of value:  ( 0.0l + 9.2il )

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

	cout << ( 6.25f + 9.2if ) << endl;
	cout << ( 6.25  + 9.2i  ) << endl;
	cout << ( 6.25l + 9.2il ) << endl;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

	return (0);
}

/* Output:
(6.25,9.2)
(6.25,9.2)
(6.25,9.2)
*/

/*
 * Compiled with: clang++ -std=c++2a
 *
 * Compiler:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 * */
