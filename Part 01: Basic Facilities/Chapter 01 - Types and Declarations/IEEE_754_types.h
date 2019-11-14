/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEEE_754_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:41:37 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/13 21:45:03 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IEEE_754_TYPES_H
# define IEEE_754_TYPES_H

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
**  Header(s).
*/

# include <stdint.h>

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
**  Macro(s).
*/

# define IS_BIG_ENDIAN (0)

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
**  IEEE 754 Standard Floating-Point Cases Summary
**
**                 ----------------------------
**                | sign | exponent | mantissa |
**   ------------------------------------------|
**  | +normal     |   0  |  all 0s  |  all 0s  |
**  |------------------------------------------|
**  | -normal     |   1  |  all 0s  |  all 0s  |
**  |------------------------------------------|
**  | +subnormal  |   0  |  all 0s  |   != 0   |
**  |------------------------------------------|
**  | -subnormal  |   1  |  all 0s  |   != 0   |
**  |------------------------------------------|
**  | +zero       |   0  |  all 0s  |  all 0s  |
**  | -zero       |   1  |  all 0s  |  all 0s  |
**  |------------------------------------------|
**  | +inf        |   0  |  all 1s  |  all 0s  |
**  | -inf        |   1  |  all 1s  |  all 0s  |
**  |------------------------------------------|
**  | nan -- QNaN |   /  |  all 1s  | 1X...XX  |
**  |------------------------------------------|
**  | nan -- SNaN |   /  |  all 1s  | 00...01  |
**  |             |      |          |     .    |
**  |             |      |          |     .    |
**  |             |      |          | 01...11  |
**   ------------------------------------------
*/

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
**  Single Precision (float)  --  Standard IEEE 754 Floating-point Specification
*/

# define IEEE_754_FLOAT_MANTISSA_BITS (23)
# define IEEE_754_FLOAT_EXPONENT_BITS (8)
# define IEEE_754_FLOAT_SIGN_BITS     (1)

# define IEEE_754_FLOAT_BIAS          ((1L << (IEEE_754_FLOAT_EXPONENT_BITS - 1)) - 1)  /* 2^{exponent_bits - 1} - 1 ; 127 */
# define IEEE_754_FLOAT_EXPONENT_MAX  ((1L << IEEE_754_FLOAT_EXPONENT_BITS) - 1)        /* 2^{exponent_bits} - 1     ; 255 */
# define IEEE_754_FLOAT_IMPLICIT_BIT  ((1UL << IEEE_754_FLOAT_MANTISSA_BITS))           /* 2^{mantissa_bits}         ; 8388607 */

# define IEEE_754_FLOAT_SUBNORMALS(exponent, mantissa) ((exponent == 0) && (mantissa != 0))
# define IEEE_754_FLOAT_ZERO(exponent, mantissa)       ((exponent == 0) && (mantissa == 0))
# define IEEE_754_FLOAT_INF(exponent, mantissa)        ((exponent == IEEE_754_FLOAT_EXPONENT_MAX) && (mantissa == 0))
# define IEEE_754_FLOAT_NAN(exponent, mantissa)        ((exponent == IEEE_754_FLOAT_EXPONENT_MAX) && (mantissa != 0))

# if (IS_BIG_ENDIAN == 1)
	typedef union {
		float value;
		struct {
			__int8_t   sign     : IEEE_754_FLOAT_SIGN_BITS;
			__int16_t  exponent : IEEE_754_FLOAT_EXPONENT_BITS;
			__uint32_t mantissa : IEEE_754_FLOAT_MANTISSA_BITS;
		};
	} IEEE_754_float;
# else
	typedef union {
		float value;
		struct {
			__uint32_t mantissa : IEEE_754_FLOAT_MANTISSA_BITS;
			__int16_t  exponent : IEEE_754_FLOAT_EXPONENT_BITS;
			__int8_t   sign     : IEEE_754_FLOAT_SIGN_BITS;
		};
	} IEEE_754_float;
# endif

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
**  Double Precision (double) --  Standard IEEE 754 Floating-point Specification
*/

# define IEEE_754_DOUBLE_MANTISSA_BITS (52)
# define IEEE_754_DOUBLE_EXPONENT_BITS (11)
# define IEEE_754_DOUBLE_SIGN_BITS     (1)

# define IEEE_754_DOUBLE_BIAS          ((1L << (IEEE_754_DOUBLE_EXPONENT_BITS - 1)) - 1)  /* 2^{exponent_bits - 1} - 1 ; 1023 */
# define IEEE_754_DOUBLE_EXPONENT_MAX  ((1L << IEEE_754_DOUBLE_EXPONENT_BITS) - 1)        /* 2^{exponent_bits} - 1     ; 2047 */
# define IEEE_754_DOUBLE_IMPLICIT_BIT  ((1UL << IEEE_754_DOUBLE_MANTISSA_BITS))           /* 2^{mantissa_bits}         ; 4503599627370496 */

# define IEEE_754_DOUBLE_SUBNORMALS(exponent, mantissa) ((exponent == 0) && (mantissa != 0))
# define IEEE_754_DOUBLE_ZERO(exponent, mantissa)       ((exponent == 0) && (mantissa == 0))
# define IEEE_754_DOUBLE_INF(exponent, mantissa)        ((exponent == IEEE_754_DOUBLE_EXPONENT_MAX) && (mantissa == 0))
# define IEEE_754_DOUBLE_NAN(exponent, mantissa)        ((exponent == IEEE_754_DOUBLE_EXPONENT_MAX) && (mantissa != 0))

# if (IS_BIG_ENDIAN == 1)
	typedef union {
		double value;
		struct {
			__int8_t   sign     : IEEE_754_DOUBLE_SIGN_BITS;
			__int16_t  exponent : IEEE_754_DOUBLE_EXPONENT_BITS;
			__uint64_t mantissa : IEEE_754_DOUBLE_MANTISSA_BITS;
		};
	} IEEE_754_double;
# else
	typedef union {
		double value;
		struct {
			__uint64_t mantissa : IEEE_754_DOUBLE_MANTISSA_BITS;
			__int16_t  exponent : IEEE_754_DOUBLE_EXPONENT_BITS;
			__int8_t   sign     : IEEE_754_DOUBLE_SIGN_BITS;
		};
	} IEEE_754_double;
# endif

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
**  Extended Precision (long double)  --  Standard IEEE 754 Floating-point Specification
*/

# define IEEE_754_LDOUBLE_MANTISSA_BITS (63)
# define IEEE_754_LDOUBLE_EXPLICIT_BITS (1)
# define IEEE_754_LDOUBLE_EXPONENT_BITS (15)
# define IEEE_754_LDOUBLE_SIGN_BITS     (1)

# define IEEE_754_LDOUBLE_BIAS          ((1L << (IEEE_754_LDOUBLE_EXPONENT_BITS - 1)) - 1)  /* 2^{exponent_bits - 1} - 1 ; 16383 */
# define IEEE_754_LDOUBLE_EXPONENT_MAX  ((1L << IEEE_754_LDOUBLE_EXPONENT_BITS) - 1)        /* 2^{exponent_bits} - 1     ; 32767 */
# define IEEE_754_LDOUBLE_IMPLICIT_BIT  ((1UL << IEEE_754_LDOUBLE_MANTISSA_BITS))

# define IEEE_754_LDOUBLE_SUBNORMALS(exponent, mantissa) ((exponent == 0) && (mantissa != 0))
# define IEEE_754_LDOUBLE_ZERO(exponent, mantissa)       ((exponent == 0) && (mantissa == 0))
# define IEEE_754_LDOUBLE_INF(exponent, mantissa)        ((exponent == IEEE_754_LDOUBLE_EXPONENT_MAX) && (mantissa == 0))
# define IEEE_754_LDOUBLE_NAN(exponent, mantissa)        ((exponent == IEEE_754_LDOUBLE_EXPONENT_MAX) && (mantissa != 0))

# if (IS_BIG_ENDIAN == 1)
	typedef union {
		long double value;
		struct {
			__int8_t   sign     : IEEE_754_LDOUBLE_SIGN_BITS;
			__int16_t  exponent : IEEE_754_LDOUBLE_EXPONENT_BITS;
			__int16_t  explict  : IEEE_754_LDOUBLE_EXPLICIT_BITS;
			__uint64_t mantissa : IEEE_754_LDOUBLE_MANTISSA_BITS;
		};
	} IEEE_754_ldouble;
# else
	typedef union {
		long double value;
		struct {
			__uint64_t mantissa : IEEE_754_LDOUBLE_MANTISSA_BITS;
			__int16_t  explict  : IEEE_754_LDOUBLE_EXPLICIT_BITS;
			__int16_t  exponent : IEEE_754_LDOUBLE_EXPONENT_BITS;
			__int8_t   sign     : IEEE_754_LDOUBLE_SIGN_BITS;
		};
	} IEEE_754_ldouble;
# endif

#endif /* IEEE_754_TYPES_H */
