/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:53:11 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/06 17:21:57 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Demonstration:
 *	A more complete flag system to use for programs, functions or other.
 */

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Header(s).
*/

#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Program Specific Macro(s):
*/

# define PROGRAM_FLAGS(c) ('a' >= c && c <= 'i')  // example

/* Store all flags from the command line. */

int	store_flags(bitset_t *flags, const char **args)
{
	if (!flags)
		return (0);

	size_t i;
	size_t j;

	i = 0;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j])
		{
			if (PROGRAM_FLAGS(args[i][j]))
				flags->set |= flagID(args[i][j++]);
			else
				// error handling
		}
		++i;
	}
    return (i);
}

int	main(int ac, const char *av[])
{
	bitset_t flags;

	flags = 0;
	av += store_flags(&flags, ++av);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** CONVENIANT WAY
*/

	/* ============================================== */
	/* CHECK FOR FLAGS */

	if (flag.a)
		// pass

	if (flag.W || flag.P || flag._1)
		// pass


	/* ============================================== */
	/* SET FLAGS */

	flag.a = ON;
	flag.o = flag._5 = flag.R = ON;


	/* ============================================== */
	/* UNSET FLAGS */

	flag.a = OFF;
	flag.o = flag._5 = flag.R = OFF;


	/* ============================================== */
	/* TOGGLE FLAG */

	flag.a ~= flag.a;
	flag.b ~= flag.b;

	// Also conventiantly macro'd to

	TOGGLE(flag.a);
	TOGGLE(flag.b);

	// No conveniant way to toggle multiple flags unfortunately.


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** TRADITIONAL WAY
*/

	/* ============================================== */
	/* CHECK FOR FLAGS */

	if (flag.set & a_flag)
		// pass

	if (flag.set & (W_flag | P_flag | _1_flag))
		// pass


	/* ============================================== */
	/* SET FLAGS */

	flag.set |= a_flag;
	flag.set |= (o_flag | _5_flag | R_flag);


	/* ============================================== */
	/* UNSET FLAGS */

	/* You can only toggle flags not unset them, so you
	must first make sure that the flag is ON before toggling
	it OFF, so that it doesn't accidently end up ON. */


	/* ============================================== */
	/* TOGGLE FLAG(S) */

	flag.set ^= a_flag;
	flag.set ^= b_flag;

	flag.set ^= L_flag | _8_flag | h_flag;

	// Also conventiantly macro'd to

	TOGGLES(flag.set, a_flag);
	TOGGLES(flag.set, b_flag);

	TOGGLES(flag.set, o_flag | _5_flag | R_flag);


	// ...

	return (0);
}
