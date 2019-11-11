/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_defined_literals.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 08:21:25 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/11 08:51:44 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  Examples:
 *      User-defined Literals.
 */

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

#include <iostream>
#include <string>

using namespace std;

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**  Structure & Definitions
*/

struct Distance
{
    private:

        long double _kilometers { 0 };

        explicit Distance(long double val) : _kilometers( val ) {}

        friend Distance operator"" _km( long double val );
        friend Distance operator"" _mi( long double val );

    public:

        long double kilometers() const
            { return ( _kilometers ); }

        Distance operator+ ( Distance && rhs ) const
            { return Distance( kilometers() + rhs.kilometers() ); }
};

ostream & operator<< ( ostream & out, const Distance & in )
    { out << in.kilometers() << " km"; return (out); }

Distance operator"" _km(long double val)
    { return Distance( val ); }

Distance operator"" _mi(long double val)
    { return Distance( val * 1.6 ); }

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**  Main.
*/

int main(void) {

    // Construct using: kilometers
    Distance d1{ 402.0_km };
    cout << "d1 = " << d1 << endl;     // 402 km

    // Construct using: miles
    Distance d2{ 402.0_mi };
    cout << "d2 = " << d2 << endl;   // 643.2 km

    // Constructed using: different units
    Distance d3 = 36.0_mi + 42.0_km;
    cout << "d3 = " << d3 << endl;          // 99.6 km

    // Distance d4( 90.0 ); // error constructor not accessible;
                            // essentially forcing users to create a
                            // Distance instance with the literals
                            // `_mi` or _km`.

    return (0);
}

/* Output:
d1 = 402 km
d2 = 643.2 km
d3 = 99.6 km
*/

/* Compiled with: clang++ -std=c++2a
 *
 * Version:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 */

/* Example source: https://docs.microsoft.com/en-us/cpp/cpp/user-defined-literals-cpp?view=vs-2019 */
