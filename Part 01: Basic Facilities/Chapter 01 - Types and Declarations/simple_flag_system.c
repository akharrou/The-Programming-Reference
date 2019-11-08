/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_flag_system.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:17:02 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/08 12:49:30 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  Demonstration:
 *      A simple flag system for programs that can also be used for functions.
 */


/* TO BE IGNORED = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

#define PRINT_FLAGS(flag) {                              \
    tmp = readbits_32bit(flags, BIG_ENDIAN | O_SPACED);  \
    printf("Bitset: %s\n", tmp);                         \
    free(tmp);                                           \
}

/* PROGRAM HEADER = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

#include <stdint.h>
#include "readbits.h"


/* Alias a 32 bit integer type to an identifier that communicates intent and
meaning better for the case we want to use it */

typedef uint32_t bitset_t;


/* This enum will declare all the values that each individual distinct bit
represents. These along with the bitwise operators will allow us to identify,
refer to, access and manipulate specific bits. */

enum e_program_flags
{
	a_flag = (1 << 0),  /* this says to move the bits that represent the integer 1 to the left (left shift) N times */
	b_flag = (1 << 1),  /* 1 is represented by a single one bit at the first column, so here that bit would move to the 2nd column from: 0b00...0001  to  0b00...0010 */
	c_flag = (1 << 2),  /* here to the third column, from: 0b00...0001  to  0b00...0100 */
	d_flag = (1 << 3),  /* to the fourth column: 0b00...01000 */
	e_flag = (1 << 4),  /* 0b00...010000 , you get the point */

	/*
	.
	.
	.
	*/

	z_flag = (1 << 25),
	A_flag = (1 << 26)

    /* ... */
};




/* PROGRAM SOURCE = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

// #include "<flag header>.h"

int	main(void)
{
    bitset_t flags;
    char *tmp;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    flags = 0;

    PRINT_FLAGS(flags)

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    /* Turns on a flag, else does nothing if already on */
    flags |= a_flag;
    flags |= b_flag;

    PRINT_FLAGS(flags)

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    /* Check to see if some flag is on by and'ing (`&`) it with the value the bit represents */
    if (flags & a_flag)
        flags |= d_flag;

    PRINT_FLAGS(flags)

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    /* Toggle a flag ; off if it is on and vice versa */
    flags ^= b_flag;

    PRINT_FLAGS(flags)

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    return (0);
}

/* Output:
Bitset: 00000000 00000000 00000000 00000000
Bitset: 00000000 00000000 00000000 00000011
Bitset: 00000000 00000000 00000000 00001011
Bitset: 00000000 00000000 00000000 00001001
*/

/*
 * Compiled with: clang -std=c11
 * Files: simgple_flag_system.c readbits.c
 *
 * Compiler:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 * */
