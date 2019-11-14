/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats_to_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 23:07:44 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/13 21:49:16 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**    NAME
**         ftoa_base, dtoa_base, ldtoa_base -- convert floating-point type
**                                             values to strings
**
**    SYNOPSIS
**         #include <libft.h>
**
**         char *
**         ftoa_base(float data, char *base, int width, int precision);
**
**         char *
**         dtoa_base(double data, char *base, int width, int precision);
**
**         char *
**         ldtoa_base(long double data, char *base, int width, int precision);
**
**    PARAMETERS
**
**         T data              Floating-point value (lvalue or rvalue).
**
**         char *base          Desired base in which to represent
**                             the value.
**
**         int width           Minimum total width desired.
**
**         int precision       Precision desired; if a negative
**                             value is passed, the precision will
**                             default to 6.
**
**    DESCRIPTION
**         Converts a floating-point value to a string. In addition the
**         value is converted to the given `base` and brought-to to the
**         given `precision`. The minimum length of the string shall be
**         `width`; if the string representation of the value is smaller
**         than `width`, the string is prepended with '0's.
**
**    RETURN VALUES
**         Returns a null-terminated string representing the floating-point
**         value ; or NULL on error.
*/

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**  Header(s).
*/

#include "./../../Libft/Includes/stdlib_42.h"
#include "./../../Libft/Includes/string_42.h"
#include "./../../Libft/Includes/macros_42.h"
#include "./../../Libft/Includes/bigint.h"

#include "IEEE_754_types.h"

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Function Template -- Floating-Point Value to String.
*/

#define make_Ttoa_base(abrv_T, floating_point_T, IEEE_754_T, allcaps_IEEE_754_T)                        \
                                                                                                        \
    char * abrv_T##toa_base(floating_point_T data, char *base, int width, int precision)                \
    {                                                                                                   \
        IEEE_754_T flt;                                                                                 \
        t_bigint result;                                                                                \
                                                                                                        \
        /* Extract Bits Representing the Floating-point Value with the Union Type */                    \
        flt.value = data;                                                                               \
                                                                                                        \
        /* Case #1: Zero */                                                                             \
        if allcaps_IEEE_754_T##_ZERO(flt.exponent, flt.mantissa)                                        \
        {                                                                                               \
            result = ft_strdup("0");                                                                    \
        }                                                                                               \
                                                                                                        \
        /* Case #2: Infinity */                                                                         \
        else if allcaps_IEEE_754_T##_INF(flt.exponent, flt.mantissa)                                    \
        {                                                                                               \
            return (flt.sign ? ft_strdup("-inf") : ft_strdup("+inf"));                                  \
        }                                                                                               \
                                                                                                        \
        /* Case #3: NaN */                                                                              \
        else if allcaps_IEEE_754_T##_NAN(flt.exponent, flt.mantissa)                                    \
        {                                                                                               \
            /* This can be simplified to just return "nan" */                                           \
            return (flt.mantissa & (1L << (allcaps_IEEE_754_T##_MANTISSA_BITS - 1)) ?                   \
                ft_strdup("QNaN") : ft_strdup("SNaN"));                                                 \
        }                                                                                               \
                                                                                                        \
        /* Case #4: Denormalized (Subnormal) */                                                         \
        else if allcaps_IEEE_754_T##_SUBNORMALS(flt.exponent, flt.mantissa)                             \
        {                                                                                               \
            flt.exponent = - allcaps_IEEE_754_T##_BIAS + 1;                                             \
        }                                                                                               \
                                                                                                        \
        /* Case #5: Normalized (Normal) */                                                              \
        else                                                                                            \
        {                                                                                               \
            flt.exponent = flt.exponent - allcaps_IEEE_754_T##_BIAS;                                    \
        }                                                                                               \
                                                                                                        \
        /* Convert the Mantissa into the `bigint` Type and */                                           \
        /* or `|` the implicit bit with the mantissa if */                                              \
        /* we are dealing with a Normalized Real */                                                     \
        result =                                                                                        \
            allcaps_IEEE_754_T##_SUBNORMALS(flt.exponent, flt.mantissa) ?                               \
                ft_utoa_base( flt.mantissa | 0                                 , DECIMAL_BASE, 0) :     \
                ft_utoa_base( flt.mantissa | allcaps_IEEE_754_T##_IMPLICIT_BIT , DECIMAL_BASE, 0);      \
                                                                                                        \
        /* Add number of times we must shift (to the right) the mantissa bits */                        \
        /* in order to correct the representation; (see 2nd comment below for */                        \
        /* detailed explanation */                                                                      \
        int32_t exp = flt.exponent - allcaps_IEEE_754_T##_MANTISSA_BITS;                                \
                                                                                                        \
        /* Shift Mantissa Bits to Correct Positions & Multiply/Divide with 2^{ exp } */                 \
        if (exp > 0)                                                                                    \
            while (exp-- > 0)                                                                           \
                result = bigint_mulfre(result, 2, base, 1);                                             \
        else                                                                                            \
            while (exp++ < 0)                                                                           \
                result = bigint_divfre(result, 2, base, 1);                                             \
                                                                                                        \
        /* Round to desired Precision */                                                                \
        result = bigint_roundfre(result, base, ((precision >= 0) ? precision : 6), 1);                  \
                                                                                                        \
        /* Pad to desired Total Width */                                                                \
        result = ft_strprepend(result, ft_padding(flt.sign + width - ft_strlen(result), '0'), 1, 1);    \
                                                                                                        \
        /* Prepend Sign (if needed) */                                                                  \
        if (flt.sign)                                                                                   \
            result = ft_strprepend(result, "-", 1, 0);                                                  \
                                                                                                        \
        return (result);                                                                                \
    }

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** The following macros expand-to/generate the source code for the functions
** specified above.
*/

/* Expands to `ftoa_base`:
Convert `float` data type values to strings. */
make_Ttoa_base( f , float , IEEE_754_float , IEEE_754_FLOAT )

/* Expands to `dtoa_base`:
Convert `double` data type values to strings. */
make_Ttoa_base( d , double , IEEE_754_double , IEEE_754_DOUBLE )

/* Expands to `ldtoa_base`:
Convert `long double` data type values to strings. */
#define ldouble long double
make_Ttoa_base( ld , ldouble , IEEE_754_ldouble , IEEE_754_LDOUBLE )
#undef ldouble

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**

  COMMENT:

    The bits of the floating point type can be extracted with the
    help of a union that combines the floating point type and a
    bitfeild that is made to correctly have the floating point type
    bits land on them as they share the same memory space.

    See "IEEE_754_types.h".

    Note that the endianness will effect the order of the bit sections
    of the floating point types; this is handled in the header, just
    make sure to turn the `IS_BIG_ENDIAN` macro on (1) or off (0) based
    on the machine's endianness.

  COMMENT:

    In the process, we have to correct the position of the mantissa
    bits. We do this by shifting all the bits to the right until the
    first mantissa bit is placed at the column that represents 2^-1;
    that would mean shifting all the bits as many times as there are
    mantissa bits.

    We must do this because the computer, when extracting the bits
    from the floating-point type into the integer type, interprets
    the bits in the context of the integer type, where each bit is
    in a column that represents a power of two, going from 0, upward:

                <-- ... 2^5, 2^4, 2^3, 2^2, 2^1, 2^0

    Now we cannot shift the bits in the integer type, as that would
    cause us to lose the bits past the column representing 2^0, and we
    certainly can't store it again in a floating-point type, AND there
    is no type that has an encoding where each bit is in a column
    representing 2^-1, 2^-2, 2^-3, ... so you have to create a custom
    type that can do that encoding.

    Once the type is implemented, we can go ahead and convert the mantissa
    held in the integer into that custom type and shift the value by
    the amount of mantissa bits there; this can be done by multiplying the
    number by 2^{-mantissa_bits}; or incrementally dividing the number
    by 2 as many as 'mantissa_bits' times.

    The exponent might be positive so the "correction right shifts" might
    cancel out with the positive exponent, so we subtract from the exponent
    the "correction shifts" before any calculation to save us some computation.

**
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
**

  EXAMPLE -- the `double` function expands to:

    char * dtoa_base(double data, char *base, int width, int precision)
    {
        IEEE_754_double flt;
        t_bigint result;
        int32_t exp;

        flt.value = data;

        if IEEE_754_DOUBLE_ZERO(flt.exponent, flt.mantissa)
        {
            result = ft_strdup("0");
        }

        else if IEEE_754_DOUBLE_INF(flt.exponent, flt.mantissa)
        {
            return (flt.sign ? ft_strdup("-inf") : ft_strdup("+inf"));
        }

        else if IEEE_754_DOUBLE_NAN(flt.exponent, flt.mantissa)
        {
            return (flt.mantissa & (1L << (IEEE_754_DOUBLE_MANTISSA_BITS - 1)) ?
                ft_strdup("QNaN") : ft_strdup("SNaN"));
        }

        else if IEEE_754_DOUBLE_SUBNORMALS(flt.exponent, flt.mantissa)
        {
            flt.exponent = -IEEE_754_DOUBLE_BIAS + 1;
        }

        else
        {
            flt.exponent = flt.exponent - IEEE_754_DOUBLE_BIAS;
        }

        result =
            IEEE_754_DOUBLE_SUBNORMALS(flt.exponent, flt.mantissa) ?
                ft_utoa_base( flt.mantissa | 0                            , DECIMAL_BASE, 0) :
                ft_utoa_base( flt.mantissa | IEEE_754_DOUBLE_IMPLICIT_BIT , DECIMAL_BASE, 0);

        exp = flt.exponent - IEEE_754_DOUBLE_MANTISSA_BITS;

        if (exp > 0)
            while (exp-- > 0)
                result = bigint_mulfre(result, 2, base, 1);
        else
            while (exp++ < 0)
                result = bigint_divfre(result, 2, base, 1);

        result = bigint_roundfre(result, base, ((precision >= 0) ? precision : 6), 1);

        result = ft_strprepend(result, ft_padding(flt.sign + width - ft_strlen(result), '0'), 1, 1);

        if (flt.sign)
            result = ft_strprepend(result, "-", 1, 0);

        return (result);
    }

*/
