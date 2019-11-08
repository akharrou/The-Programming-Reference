/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readbits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:50:54 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/08 12:17:53 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readbits.h"

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
		while (buf[cur_idx] && buf[cur_idx] != '1')
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

/* WRAPPER FUNCTIONS FOR SPECIFIC TYPES - - - - - - - - - - - - - - - - - - - */

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
