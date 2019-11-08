
/*
**	(C) Example:
**		Complex literals.
*/

#include <stdio.h>      /* Standard Library of Input and Output */
#include <complex.h>    /* Standard's Complex Header */

int main(void)
{

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	( 6.32f + 7.3if );   // literal of type:  _Complex float
	( 6.32  + 7.3i  );   // literal of type:  _Complex double
	( 6.32L + 7.3il );   // literal of type:  _Complex long double

	( 7.3if );           // complex literal of value:  ( 0.0 + 7.3if )
	( 7.3i  );           // complex literal of value:  ( 0.0 + 7.3i  )
	( 7.3il );           // complex literal of value:  ( 0.0 + 7.3il )

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	printf("Real: %.2f ; Imag: %.2f\n", creal( 6.32f + 7.3if ) , cimag( 6.32f + 7.3if ) );
	printf("Real: %.2f ; Imag: %.2f\n", creal( 6.32  + 7.3i  ) , cimag( 6.32  + 7.3i  ) );
	printf("Real: %.2f ; Imag: %.2f\n", creal( 6.32L + 7.3il ) , cimag( 6.32L + 7.3il ) );

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	return (0);
}

/* Output:
Real: 6.32 ; Imag: 7.30
Real: 6.32 ; Imag: 7.30
Real: 6.32 ; Imag: 7.30
*/

/*
 * Compiled with: clang -std=c11 -w
 *
 * Compiler:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 * */
