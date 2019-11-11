/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_literals.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 08:21:53 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/11 08:21:54 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	( 9.2if );           // complex literal of value:  ( 0.0f + 9.2if )
	( 9.2i  );           // complex literal of value:  ( 0.0  + 9.2i  )
	( 9.2il );           // complex literal of value:  ( 0.0l + 9.2il )

	( 6.25f + 9.2if );   // literal of type:  complex <float>
	( 6.25  + 9.2i  );   // literal of type:  complex <double>
	( 6.25l + 9.2il );   // literal of type:  complex <long double>

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
 * Compiled with: clang++ -std=c++2a -w
 *
 * Compiler:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 * */
