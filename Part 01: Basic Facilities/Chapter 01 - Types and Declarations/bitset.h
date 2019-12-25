/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:27:24 by akharrou          #+#    #+#             */
/*   Updated: 2019/12/24 19:23:01 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITSET_H
# define BITSET_H

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**  Header(s).
*/

# include <stdint.h>
# include <limits.h>

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**  Needed Macro(s).
*/

# ifndef ISDIGIT
#  define ISDIGIT(c) (c >= '0' && c <= '9')
# endif

# ifndef ISLOWER
#  define ISLOWER(c) (c >= 'a' && c <= 'z')
# endif

# ifndef ISUPPER
#  define ISUPPER(c) (c >= 'A' && c <= 'Z')
# endif

# ifndef ISALPHA
#  define ISALPHA(c) (ISUPPER(c) || ISLOWER(c))
# endif

# ifndef ISALNUM
#  define ISALNUM(c) (ISALPHA(c) || ISDIGIT(c))
# endif

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**  Macro(s).
*/

# define ON  (1)
# define OFF (0)

# define TOGGLE(flag)              (flag = ~flag)
# define TOGGLES(flagset, flagIDs) (flagset ^= flagIDs)

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**  Bitset of N bits, where N = sizeof(uintmax_t) * CHAR_BIT, whose bits are
**  accessible by a unique bitfield identifier.
*/

# define BITSET_LENGTH (sizeof(uintmax_t) * CHAR_BIT)

typedef union u_bitset
{
	uintmax_t set;
	struct
	{
		char a : 1;  char b : 1;  char c : 1;  char d : 1;  char e : 1;
		char f : 1;  char g : 1;  char h : 1;  char i : 1;  char j : 1;
		char k : 1;  char l : 1;  char m : 1;  char n : 1;  char o : 1;
		char p : 1;  char q : 1;  char r : 1;  char s : 1;  char t : 1;
		char u : 1;  char v : 1;  char w : 1;  char x : 1;  char y : 1;
		char z : 1;

		char A : 1;  char B : 1;  char C : 1;  char D : 1;  char E : 1;
		char F : 1;  char G : 1;  char H : 1;  char I : 1;  char J : 1;
		char K : 1;  char L : 1;  char M : 1;  char N : 1;  char O : 1;
		char P : 1;  char Q : 1;  char R : 1;  char S : 1;  char T : 1;
		char U : 1;  char V : 1;  char W : 1;  char X : 1;  char Y : 1;
		char Z : 1;

		char _0 : 1;
		char _1 : 1; char _2 : 1; char _3 : 1;
		char _4 : 1; char _5 : 1; char _6 : 1;
		char _7 : 1; char _8 : 1; char _9 : 1;

		char none_flag    : 1;
		char special_flag : 1;
	};
} bitset_t;

/*
**  Values identifying each bit, in a set of N bits, where
**  N = sizeof(uintmax_t) * CHAR_BIT.
**
**  This is another way of of identifying and accessing single distinct
**  bits.
**
**  It is done by and'ing (`&`) the bit set with a value that is represented
**  the one single particular bit that one is trying to access. The values
**  that are represented by one single bit are defined below.
*/

enum e_flagID
{
	null_flag,

	a_flag = (1UL << 0),   b_flag = (1UL << 1),   c_flag = (1UL << 2),
	d_flag = (1UL << 3),   e_flag = (1UL << 4),   f_flag = (1UL << 5),
	g_flag = (1UL << 6),   h_flag = (1UL << 7),   i_flag = (1UL << 8),
	j_flag = (1UL << 9),   k_flag = (1UL << 10),  l_flag = (1UL << 11),
	m_flag = (1UL << 12),  n_flag = (1UL << 13),  o_flag = (1UL << 14),
	p_flag = (1UL << 15),  q_flag = (1UL << 16),  r_flag = (1UL << 17),
	s_flag = (1UL << 18),  t_flag = (1UL << 19),  u_flag = (1UL << 20),
	v_flag = (1UL << 21),  w_flag = (1UL << 22),  x_flag = (1UL << 23),
	y_flag = (1UL << 24),  z_flag = (1UL << 25),

	A_flag = (1UL << 26),  B_flag = (1UL << 27),  C_flag = (1UL << 28),
	D_flag = (1UL << 29),  E_flag = (1UL << 30),  F_flag = (1UL << 31),
	G_flag = (1UL << 32),  H_flag = (1UL << 33),  I_flag = (1UL << 34),
	J_flag = (1UL << 35),  K_flag = (1UL << 36),  L_flag = (1UL << 37),
	M_flag = (1UL << 38),  N_flag = (1UL << 39),  O_flag = (1UL << 40),
	P_flag = (1UL << 41),  Q_flag = (1UL << 42),  R_flag = (1UL << 43),
	S_flag = (1UL << 44),  T_flag = (1UL << 45),  U_flag = (1UL << 46),
	V_flag = (1UL << 47),  W_flag = (1UL << 48),  X_flag = (1UL << 49),
	Y_flag = (1UL << 50),  Z_flag = (1UL << 51),

	_0_flag = (1UL << 52),
	_1_flag = (1UL << 53), _2_flag = (1UL << 54), _3_flag = (1UL << 55),
	_4_flag = (1UL << 56), _5_flag = (1UL << 57), _6_flag = (1UL << 58),
	_7_flag = (1UL << 59), _8_flag = (1UL << 60), _9_flag = (1UL << 61),

	none_flag    = (1UL << 62),
	special_flag = (1UL << 63)
};

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**  Table mapping `char`s to their corresponding flag (ID).
*/

typedef struct { char character; enum e_flagID flag; } char_flagID_pair_t;

extern char_flagID_pair_t char2flagID_table[];

char_flagID_pair_t	char2flagID_table[] =
{
	{ '0', _0_flag },
	{ '1', _1_flag }, { '2', _2_flag }, { '3', _3_flag },
	{ '4', _4_flag }, { '5', _5_flag }, { '6', _6_flag },
	{ '7', _7_flag }, { '8', _8_flag }, { '9', _9_flag },

	{ 'a', a_flag }, { 'b', b_flag }, { 'c', c_flag }, { 'd', d_flag }, { 'e', e_flag },
	{ 'f', f_flag }, { 'g', g_flag }, { 'h', h_flag }, { 'i', i_flag }, { 'j', j_flag },
	{ 'k', k_flag }, { 'l', l_flag }, { 'm', m_flag }, { 'n', n_flag }, { 'o', o_flag },
	{ 'p', p_flag }, { 'q', q_flag }, { 'r', r_flag }, { 's', s_flag }, { 't', t_flag },
	{ 'u', u_flag }, { 'v', v_flag }, { 'w', w_flag }, { 'x', x_flag }, { 'y', y_flag },
	{ 'z', z_flag },

	{ 'A', A_flag }, { 'B', B_flag }, { 'C', C_flag }, { 'D', D_flag }, { 'E', E_flag },
	{ 'F', F_flag }, { 'G', G_flag }, { 'H', H_flag }, { 'I', I_flag }, { 'J', J_flag },
	{ 'K', K_flag }, { 'L', L_flag }, { 'M', M_flag }, { 'N', N_flag }, { 'O', O_flag },
	{ 'P', P_flag }, { 'Q', Q_flag }, { 'R', R_flag }, { 'S', S_flag }, { 'T', T_flag },
	{ 'U', U_flag }, { 'V', V_flag }, { 'W', W_flag }, { 'X', X_flag }, { 'Y', Y_flag },
	{ 'Z', Z_flag },

	{ '\0', null_flag }
};

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**  Macro to index straight into the table at the index corresponding
**  to the character.
*/

# define char2flagID_table_SIZE                   (sizeof(char2flagID_table) / sizeof(char_flagID_pair_t))
# define char2flagID_table_LOWER_ALPHABET_OFFSET  (10)
# define char2flagID_table_UPPER_ALPHABET_OFFSET  (36)

# define flagID_index(c)                                                  \
                                                                          \
    (                                                                     \
        ISALNUM(c) ?                                                      \
                                                                          \
            (ISALPHA(c) ?                                                 \
                                                                          \
                (ISLOWER(c) ?                                             \
                    c - 'a' + char2flagID_table_LOWER_ALPHABET_OFFSET :   \
                    c - 'A' + char2flagID_table_UPPER_ALPHABET_OFFSET)    \
                                                                          \
                : c - '0')                                                \
                                                                          \
            : char2flagID_table_SIZE - 1                                  \
    )

# define flagID(c) (char2flagID_table[flagID_index(c)].flag)

/* EXAMPLE USAGE :: `char2flagID_table` and `flagID(c)`:

	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	if (arg && arg[0] == '-')
		while (*(++arg))
			flags.set |= flagID(*arg);

	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	if (arg && arg[0] == '-')
		while (*(++arg))
			for (int i = 0; i < char2flagID_table[i].character; ++i)
				if (*arg == char2flagID_table[i].character)
					flags.set |= char2flagID_table[i].flag;
*/

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

#endif
