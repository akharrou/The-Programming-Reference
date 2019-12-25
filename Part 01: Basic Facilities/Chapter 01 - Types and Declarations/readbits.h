/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readbits.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:54:49 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/08 12:06:17 by akharrou         ###   ########.fr       */
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
**         char * readbits_8bit( int8_t data , int oflags );
**         char * readbits_16bit( int16_t data , int oflags );
**         char * readbits_32bit( int32_t data , int oflags );
**         char * readbits_64bit( int64_t data , int oflags );
**         char * readbits_128bit( int128_t data , int oflags );
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

#ifndef READBITS_H
# define READBITS_H

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

char	*readbits_8bit             ( int8_t      data , int oflags );
char	*readbits_16bit            ( int16_t     data , int oflags );
char	*readbits_32bit            ( int32_t     data , int oflags );
char	*readbits_64bit            ( int64_t     data , int oflags );
// char	*readbits_128bit           ( int128_t    data , int oflags );

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

#endif /* READBITS_H */
