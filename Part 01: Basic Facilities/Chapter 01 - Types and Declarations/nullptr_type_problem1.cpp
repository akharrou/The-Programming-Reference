/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nullptr_type_problem1.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 08:21:44 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/11 08:21:45 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  (C++) Demonstration:
**      Problem #1 that `nullptr_t` solves.
*/

#include <iostream>
using namespace std;

void f(void *)  { cout << "void *"  << endl; }
void f(int)     { cout << "int"     << endl; }

int main(void)
{
    f(0);
    f(nullptr);
    // f(NULL);  // would be ambiguous if NULL is passed
                 // ambiguous call: all two functions are candidates
                 // ambiguous if NULL is an integral null pointer constant
                 // (as is the case in most implementations)
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
