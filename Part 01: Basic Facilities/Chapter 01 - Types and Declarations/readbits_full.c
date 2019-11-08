/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readbits_full.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:54:49 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/08 12:43:44 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**    NAME
**         readbits_T -- stringify underlying memory representation
**
**    SYNOPSIS
**         #include <libft.h>
**
**         char * readbits_integral( void *integral, size_t size, int oflags );
**
**         char * readbits_IEEE_754_float( IEEE_754_float data , int oflag );
**         char * readbits_IEEE_754_double( IEEE_754_double data , int oflag );
**         char * readbits_IEEE_754_ldouble( IEEE_754_ldouble data , int oflag );
**
**         char * readbits_8bit( __int8_t data , int oflags );
**         char * readbits_16bit( __int16_t data , int oflags );
**         char * readbits_32bit( __int32_t data , int oflags );
**         char * readbits_64bit( __int64_t data , int oflags );
**         char * readbits_128bit( __int128_t data , int oflags );
**
**         char * readbits_char( char data , int oflags );
**         char * readbits_short( short data , int oflags );
**         char * readbits_int( int data , int oflags );
**         char * readbits_long( long data , int oflags );
**         char * readbits_llong( long long data , int oflags );
**
**         char * readbits_float( float data , int oflags );
**         char * readbits_double( double data , int oflags );
**         char * readbits_ldouble( long double data , int oflags );
**
**    PARAMETERS
**
**         T data                lvalue or rvalue of type T.
**
**         int oflags            The oflag argument may indicate the
**                               spacing of bytes, the endianness desired
**                               and whether or not to truncate
**                               insignificant trailing 0s.
**
**                               Default is unspaced and big endian
**                               representation.
**
**                               The flags specified for the oflag
**                               argument are formed by or'ing the
**                               following values:
**
**                               O_DEFAULT          not spaced & in big
**                                                  endianness
**
**                               O_SPACED           bytes or major sections
**                                                  are spaced
**
**                               O_TRUNCATE         truncate insignificant
**                                                  0's at the end
**
**                               O_LITTLE_ENDIAN    little-endian representation
**                               O_BIG_ENDIAN       big-endian representation
**
**    DESCRIPTION
**         Allocates a null terminated string equivalent to the number of bits
**         that form the underlying memory representation for the given type T.
**         Then proceeds to filling the string with all the bits that represent
**         the value (of type T).
**
**    RETURN VALUES
**         Returns a the memory representation as a null-terminated string.
*/

/* HEADERS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "IEEE_754_types.h"

/* MACROS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

# ifndef BIT
#  define BIT(i) (1L << i)
# endif

/* PROTOTYPES - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

char	*readbits_integral         ( void *integral, size_t size, int oflags );

char	*readbits_IEEE_754_float   ( IEEE_754_float   data , int oflag );
char	*readbits_IEEE_754_double  ( IEEE_754_double  data , int oflag );
char	*readbits_IEEE_754_ldouble ( IEEE_754_ldouble data , int oflag );

char	*readbits_8bit             ( __int8_t    data , int oflags );
char	*readbits_16bit            ( __int16_t   data , int oflags );
char	*readbits_32bit            ( __int32_t   data , int oflags );
char	*readbits_64bit            ( __int64_t   data , int oflags );
char	*readbits_128bit           ( __int128_t  data , int oflags );

char	*readbits_char             ( char        data , int oflags );
char	*readbits_short            ( short       data , int oflags );
char	*readbits_int              ( int         data , int oflags );
char	*readbits_long             ( long        data , int oflags );
char	*readbits_llong            ( long long   data , int oflags );

char	*readbits_float            ( float       data , int oflags );
char	*readbits_double           ( double      data , int oflags );
char	*readbits_ldouble          ( long double data , int oflags );

/* ENUMS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

enum e_readbits_function_suite_flags
{
	O_DEFAULT,
	O_SPACED        = (1 << 0),
	O_TRUNCATE      = (1 << 1),
	O_LITTLE_ENDIAN = (1 << 2),
	O_BIG_ENDIAN    = (1 << 3)
};


/* UTILITY FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

char	*ft_strrev(char *str)
{
	int	i;
	int	j;
	char	tmp;

	j = 0;
	while (str[j])
		++j;
	i = -1;
	while (--j > ++i)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
	return (str);
}

/* GENERALIZED GENERIC FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - */

char	*readbits_integral(void *integral, size_t size, int oflags)
{
	char	*buf;
	size_t	bufsize;
	size_t	cur_idx;
	ssize_t	i;

	bufsize = ((oflags & O_SPACED) ? size - 1 : 0) + size * CHAR_BIT + 1;
	cur_idx = bufsize;
	if (!(buf = malloc(bufsize)))
		return (NULL);
	buf[--cur_idx] = '\0';
	while (cur_idx)
	{
		i = 0;
		while (i < CHAR_BIT)
			buf[--cur_idx] = *(char *)integral & BIT(i++) ? '1' : '0';
		++integral;
		if ((oflags & O_SPACED) && cur_idx)
			buf[--cur_idx] = ' ';
	}
	if (oflags & O_TRUNCATE)
	{
		while (buf[cur_idx] != '1')
			++cur_idx;
		cur_idx -= (cur_idx == bufsize - 1);
		memmove(buf, &(buf[cur_idx]), bufsize - cur_idx);
	}
	if (oflags & O_LITTLE_ENDIAN)
		ft_strrev(buf);
	return (buf);
}

# define make_readbits_floating_type(T, BIT_LEN, MANTISSA_LEN, EXPONENT_LEN)  \
                                                                              \
    char *readbits_##T( T flt, int oflags )                                   \
    {                                                                         \
        char   *buf;                                                          \
        size_t bufsize;                                                       \
        size_t i;                                                             \
                                                                              \
        bufsize = (BIT_LEN) + ((oflags & O_SPACED) ? 2 : 0) + 1;              \
        if (!(buf = malloc(bufsize)))                                         \
            return (NULL);                                                    \
        buf[--bufsize] = '\0';                                                \
        i = 0;                                                                \
        while (i < MANTISSA_LEN)                                              \
            buf[--bufsize] = flt.mantissa & BIT(i++) ? '1' : '0';             \
        if (oflags & O_SPACED)                                                \
            buf[--bufsize] = ' ';                                             \
        i = 0;                                                                \
        while (i < EXPONENT_LEN)                                              \
            buf[--bufsize] = flt.exponent & BIT(i++) ? '1' : '0';             \
        if (oflags & O_SPACED)                                                \
            buf[--bufsize] = ' ';                                             \
        buf[--bufsize] = flt.sign ? '1' : '0';                                \
        if (oflags & O_LITTLE_ENDIAN)                                         \
            ft_strrev(buf);                                                   \
        return (buf);                                                         \
    }

/* SPECIFIC FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

make_readbits_floating_type( IEEE_754_float   ,  sizeof(float) * CHAR_BIT , IEEE_754_FLOAT_MANTISSA_BITS   , IEEE_754_FLOAT_EXPONENT_BITS   )
make_readbits_floating_type( IEEE_754_double  , sizeof(double) * CHAR_BIT , IEEE_754_DOUBLE_MANTISSA_BITS  , IEEE_754_DOUBLE_EXPONENT_BITS  )
make_readbits_floating_type( IEEE_754_ldouble ,             10 * CHAR_BIT , IEEE_754_LDOUBLE_MANTISSA_BITS , IEEE_754_LDOUBLE_EXPONENT_BITS )

char	*readbits_float   ( float       data , int oflags ) { return ( readbits_IEEE_754_float   ( (IEEE_754_float)   { data }, oflags ) ); }
char	*readbits_double  ( double      data , int oflags ) { return ( readbits_IEEE_754_double  ( (IEEE_754_double)  { data }, oflags ) ); }
char	*readbits_ldouble ( long double data , int oflags ) { return ( readbits_IEEE_754_ldouble ( (IEEE_754_ldouble) { data }, oflags ) ); }

char	*readbits_8bit    ( __int8_t    data , int oflags ) { return ( readbits_integral ( &data, sizeof( __int8_t   ) , oflags ) ); }
char	*readbits_16bit   ( __int16_t   data , int oflags ) { return ( readbits_integral ( &data, sizeof( __int16_t  ) , oflags ) ); }
char	*readbits_32bit   ( __int32_t   data , int oflags ) { return ( readbits_integral ( &data, sizeof( __int32_t  ) , oflags ) ); }
char	*readbits_64bit   ( __int64_t   data , int oflags ) { return ( readbits_integral ( &data, sizeof( __int64_t  ) , oflags ) ); }
char	*readbits_128bit  ( __int128_t  data , int oflags ) { return ( readbits_integral ( &data, sizeof( __int128_t ) , oflags ) ); }

char	*readbits_char    ( char        data , int oflags ) { return ( readbits_integral ( &data, sizeof( char       ) , oflags ) ); }
char	*readbits_short   ( short       data , int oflags ) { return ( readbits_integral ( &data, sizeof( short      ) , oflags ) ); }
char	*readbits_int     ( int         data , int oflags ) { return ( readbits_integral ( &data, sizeof( int        ) , oflags ) ); }
char	*readbits_long    ( long        data , int oflags ) { return ( readbits_integral ( &data, sizeof( long       ) , oflags ) ); }
char	*readbits_llong   ( long long   data , int oflags ) { return ( readbits_integral ( &data, sizeof( long long  ) , oflags ) ); }


/* TEST MAIN - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int main(void)
{

	/* ------------------------------------------------------------------------------------------------------------------ */

	printf("char:    %s\n", readbits_char    (99     , O_SPACED /* | O_TRUNCATED | O_LITTLE_ENDIAN | O_BIG_ENDIAN */ ) );
	printf("short:   %s\n", readbits_short   (999    , O_SPACED /* | O_TRUNCATED | O_LITTLE_ENDIAN | O_BIG_ENDIAN */ ) );
	printf("int:     %s\n", readbits_int     (9999   , O_SPACED /* | O_TRUNCATED | O_LITTLE_ENDIAN | O_BIG_ENDIAN */ ) );
	printf("long:    %s\n", readbits_long    (99999  , O_SPACED /* | O_TRUNCATED | O_LITTLE_ENDIAN | O_BIG_ENDIAN */ ) );
	printf("llong:   %s\n", readbits_llong   (999999 , O_SPACED /* | O_TRUNCATED | O_LITTLE_ENDIAN | O_BIG_ENDIAN */ ) );
	printf("\n");

	printf("float:   %s\n", readbits_float    ( 6.25, O_SPACED /* | O_LITTLE_ENDIAN | O_BIG_ENDIAN */ ) );
	printf("double:  %s\n", readbits_double   (-6.25, O_SPACED /* | O_LITTLE_ENDIAN | O_BIG_ENDIAN */ ) );
	printf("ldouble: %s\n", readbits_ldouble  ( 6.25, O_SPACED /* | O_LITTLE_ENDIAN | O_BIG_ENDIAN */ ) );

	/* ------------------------------------------------------------------------------------------------------------------ */

    return (0);
}

/* Output:
char:    01100011
short:   00000011 11100111
int:     00000000 00000000 00100111 00001111
long:    00000000 00000000 00000000 00000000 00000000 00000001 10000110 10011111
llong:   00000000 00000000 00000000 00000000 00000000 00001111 01000010 00111111

float:   0 01000000 10010000000000000000000
double:  1 10000000001 1001000000000000000000000000000000000000000000000000
ldouble: 0 100000000000001 1100100000000000000000000000000000000000000000000000000000000000
*/

/*
 * Compiled with: clang -std=c11
 *
 * Compiler:
 * Apple LLVM version 9.1.0 (clang-902.0.39.1)
 * Target: x86_64-apple-darwin17.4.0
 * Thread model: posix
 * */
