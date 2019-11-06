/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:17:02 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/06 14:37:24 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Demonstration of a simple flag system for a program */

/* PROGRAM HEADER = = = = = = = = = = = = = = = = = = = = = = */

#include <stdint.h>

typedef uint32_t flag_t;

enum e_program_flags
{
	a_flag = (1 << 0),
	b_flag = (1 << 1),
	c_flag = (1 << 2),
	d_flag = (1 << 3),

	/*
	.
	.
	.
	*/

	z_flag = (1 << 4),

	DEFAULT_FLAGS = a_flag | d_flag /* ... or just 0, meaning no initial flags */
};

/* PROGRAM SOURCE = = = = = = = = = = = = = = = = = = = = = = */

// #include "<program header>.h"

int	store_flags(bitset_t *flags, char **args)
{
    int i;
    int j;

    (*flags) = DEFAULT_FLAGS;
    i = 0;
    while (args[i] && args[i][0] == '-')
    {
        j = 1;
        while ( ISALNUM(args[i][j]) )
            toggle_flag(args[i][j++], flags);
        ++i;
    }
    return (i);
}

int	main(int ac, char **av)
{
    bitset_t flags;
}
