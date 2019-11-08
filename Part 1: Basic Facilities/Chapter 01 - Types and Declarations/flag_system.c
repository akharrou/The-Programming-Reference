/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:53:11 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/08 12:59:25 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Demonstration:
 *		A more complete flag system to use for programs, functions or other.
 */


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Preambule (to be skipped)
*/

#include "readbits.h"

#define DO_SOMETHING (void)0;

#define EXAMPLE_ERROR_HANDLING(c)                       \
    {                                                   \
        printf("error: '%c' illegal option\n", c);      \
        printf("usage: ./<program> [-abcdefghi]\n");    \
        exit(1);                                        \
    }

#define PRINT_FLAGS(flags)                                                                          \
    {                                                                                               \
        char *tmp = readbits_integral(&flags.set, sizeof(flags.set), O_BIG_ENDIAN | O_SPACED );     \
        printf("Bitset: %s\n", tmp);                                                                \
        free(tmp);                                                                                  \
    }


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Prerequisite(s).
*/

#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"

#define PROGRAM_FLAGS(c) ('a' <= c && c <= 'i') // example


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Utility Function(s).
*/

/* Store all flags from the command line. */
int	store_flags(bitset_t *flags, const char **args)
{
	if (!flags || !args)
		return (0);

	int i = 0;

	while (args[i] && args[i][0] == '-')
	{
		size_t j = 1;
		while (args[i][j])
		{
			if (PROGRAM_FLAGS(args[i][j]))
				flags->set |= flagID(args[i][j]);
			else
				EXAMPLE_ERROR_HANDLING(args[i][j]);  // this is just an example of error handling
			++j;
		}
		++i;
	}
    return (i);
}

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Main
*/

int	main(int ac, const char *av[])
{
	bitset_t flags;

	flags.set = 0;

	--ac;
	++av;
	av += store_flags(&flags, av);

	/*
	** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
	** CONVENIANT WAY
	*/

	/* ============================================== */
	/* CHECK FOR FLAGS */

	if (flags.a)
		DO_SOMETHING;

	if (flags.W || flags.P || flags._1)
		DO_SOMETHING;

	PRINT_FLAGS(flags);

	/* ============================================== */
	/* SET FLAGS */

	flags.a = ON;
	flags.o = flags._5 = flags.R = ON;

	PRINT_FLAGS(flags);


	/* ============================================== */
		DO_SOMETHING

	flags.a = OFF;
	flags.o = flags._5 = flags.R = OFF;

	PRINT_FLAGS(flags);


	/* ============================================== */
	/* TOGGLE FLAG */

	flags.a = ~flags.a;
	flags.b = ~flags.b;

	PRINT_FLAGS(flags);

	// Also conventiantly macro'd to

	TOGGLE(flags.a);
	TOGGLE(flags.b);

	PRINT_FLAGS(flags);

	// No conveniant way to toggle multiple flags unfortunately.


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** TRADITIONAL WAY
*/

	/* ============================================== */
	/* CHECK FOR FLAGS */

	if (flags.set & a_flag)
		DO_SOMETHING;

	if (flags.set & (W_flag | P_flag | _1_flag))
		DO_SOMETHING;


	/* ============================================== */
	/* SET FLAGS */

	flags.set |= a_flag;
	flags.set |= (o_flag | _5_flag | R_flag);


	/* ============================================== */
	/* UNSET FLAGS */

	/* You can only toggle flags not unset them, so you
	must first make sure that the flag is ON before toggling
	it OFF, so that it doesn't accidently end up ON. */


	/* ============================================== */
	/* TOGGLE FLAG(S) */

	flags.set ^= a_flag;
	flags.set ^= b_flag;

	flags.set ^= L_flag | _8_flag | h_flag;

	// Also conventiantly macro'd to

	TOGGLES(flags.set, a_flag);
	TOGGLES(flags.set, b_flag);

	TOGGLES(flags.set, o_flag | _5_flag | R_flag);


	// ...

	return (0);
}


/* Output:
Bitset: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
Bitset: 00000010 00000000 00001000 00000000 00000000 00000000 01000000 00000001
Bitset: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
Bitset: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000011
Bitset: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
*/

/*
 * Compiled with: clang -std=c11
 * Files: flag_system.c readbits.c
 *
 * Compiler:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 * */
