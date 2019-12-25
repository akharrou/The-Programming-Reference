/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEEE_754_types_test.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:41:37 by akharrou          #+#    #+#             */
/*   Updated: 2019/11/14 12:05:14 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IEEE_754_TYPES1_H
# define IEEE_754_TYPES1_H

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
**  | +zero       |   0  |  all 0s  |  all 0s  |
**  |------------------------------------------|
**  | -zero       |   1  |  all 0s  |  all 0s  |
**  |------------------------------------------|
**  | +inf        |   0  |  all 1s  |  all 0s  |
**  |------------------------------------------|
**  | -inf        |   1  |  all 1s  |  all 0s  |
**  |------------------------------------------|
**  | nan -- QNaN |   /  |  all 1s  | 1X...XX  |
**  |------------------------------------------|
**  | nan -- SNaN |   /  |  all 1s  | 00...01  |
**  |             |      |          |     .    |
**  |             |      |          |     .    |
**  |             |      |          | 01...11  |
**  |------------------------------------------|
**  | +subnormal  |   0  |  all 0s  |   != 0   |
**  |------------------------------------------|
**  | -subnormal  |   1  |  all 0s  |   != 0   |
**  |------------------------------------------|
**  | +normal     |   0  |  all 0s  |  all 0s  |
**  |------------------------------------------|
**  | -normal     |   1  |  all 0s  |  all 0s  |
**   ------------------------------------------
*/

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
** Standard IEEE 754 Floating-point Generator
*/

# define glue(a, b) a ## b
# define DEFINE glue(#, define)

# define define_IEEE_754_T_MANTISSA_BITS(Nbits, MANTISSA_BITS) DEFINE IEEE_754_BINARY ## Nbits ## _MANTISSA_BITS (MANTISSA_BITS)
# define define_IEEE_754_T_EXPLICIT_BITS(Nbits, EXPLICIT_BITS) DEFINE IEEE_754_BINARY ## Nbits ## _EXPLICIT_BITS (EXPLICIT_BITS)
# define define_IEEE_754_T_EXPONENT_BITS(Nbits, EXPONENT_BITS) DEFINE IEEE_754_BINARY ## Nbits ## _EXPONENT_BITS (EXPONENT_BITS)
# define define_IEEE_754_T_SIGN_BITS(Nbits, SIGN_BITS)         DEFINE IEEE_754_BINARY ## Nbits ## _SIGN_BITS     (SIGN_BITS)

# define define_IEEE_754_T_BIAS(Nbits)                         DEFINE IEEE_754_BINARY ## Nbits ## _BIAS         ((1UL << (IEEE_754_BINARY ## Nbits ## _EXPONENT_BITS - 1)) - 1) /* 2^{exponent_bits - 1} - 1 */
# define define_IEEE_754_T_EXPONENT_MAX(Nbits)                 DEFINE IEEE_754_BINARY ## Nbits ## _EXPONENT_MAX ((1UL << IEEE_754_BINARY ## Nbits ## _EXPONENT_BITS) - 1)       /* 2^{exponent_bits} - 1     */
# define define_IEEE_754_T_IMPLICIT_BIT(Nbits)                 DEFINE IEEE_754_BINARY ## Nbits ## _IMPLICIT_BIT ((1UL << IEEE_754_BINARY ## Nbits ## _MANTISSA_BITS))           /* 2^{mantissa_bits}         */

# define define_IEEE_754_T_SUBNORMALS(Nbits)                   DEFINE IEEE_754_BINARY ## Nbits ## _SUBNORMALS(exponent, mantissa) ((exponent == 0) && (mantissa != 0))
# define define_IEEE_754_T_ZERO(Nbits)                         DEFINE IEEE_754_BINARY ## Nbits ## _ZERO(exponent, mantissa)       ((exponent == 0) && (mantissa == 0))
# define define_IEEE_754_T_INF(Nbits)                          DEFINE IEEE_754_BINARY ## Nbits ## _INF(exponent, mantissa)        ((exponent == IEEE_754_BINARY ## Nbits ## _EXPONENT_MAX) && (mantissa == 0))
# define define_IEEE_754_T_NAN(Nbits)                          DEFINE IEEE_754_BINARY ## Nbits ## _NAN(exponent, mantissa)        ((exponent == IEEE_754_BINARY ## Nbits ## _EXPONENT_MAX) && (mantissa != 0))

// # define define_IEEE_754_T_INTEGER_BIT(Nbits)                                                                          \
//                                                                                                                        \
//     # if (IEEE_754_BINARY ## Nbits ## _EXPLICIT_BITS)                                                                  \
//     DEFINE IEEE_754_BINARY ## Nbits ## _INTEGER_BIT __int32_t   exponent : IEEE_754_BINARY ## Nbits ## _EXPONENT_BITS; \
//     # else                                                                                                             \
//     DEFINE IEEE_754_BINARY ## Nbits ## _INTEGER_BIT                                                                    \
//     # endif


# if (IS_BIG_ENDIAN == 1)
#  define define_IEEE_754_T(T, floating_point_T)                                \
                                                                                \
    typedef union {                                                             \
        floating_point_T value;                                                 \
        struct {                                                                \
            __int8_t    sign     : IEEE_754_BINARY ## Nbits ## _SIGN_BITS;      \
            __int32_t   exponent : IEEE_754_BINARY ## Nbits ## _EXPONENT_BITS;  \
            /* IEEE_754_BINARY ## Nbits ## _INTEGER_BIT                            \ */ \
            __uint128_t mantissa : IEEE_754_BINARY ## Nbits ## _MANTISSA_BITS;  \
        };                                                                      \
    } IEEE_754_binary ## Nbits;
# else
#  define define_IEEE_754_T(floating_point_T, Nbits)                            \
                                                                                \
    typedef union {                                                             \
        floating_point_T value;                                                 \
        struct {                                                                \
            __uint128_t mantissa : IEEE_754_BINARY ## Nbits ## _MANTISSA_BITS;  \
            /* IEEE_754_BINARY ## Nbits ## _INTEGER_BIT                            \ */ \
            __int32_t   exponent : IEEE_754_BINARY ## Nbits ## _EXPONENT_BITS;  \
            __int8_t    sign     : IEEE_754_BINARY ## Nbits ## _SIGN_BITS;      \
        };                                                                      \
    } IEEE_754_binary ## Nbits;
# endif

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
** Generate a Standard IEEE 754 Floating-point Type
*/

# define make_IEEE_754_floating_point_type(floating_point_type, T_BITS, MANT, EXPLICIT, EXPONENT, SIGN) \
                                                                                                        \
    define_IEEE_754_T_MANTISSA_BITS(T_BITS, MANT)                                                       \
    define_IEEE_754_T_EXPLICIT_BITS(T_BITS, EXPLICIT)                                                   \
    define_IEEE_754_T_EXPONENT_BITS(T_BITS, EXPONENT)                                                   \
    define_IEEE_754_T_SIGN_BITS(T_BITS, SIGN)                                                           \
                                                                                                        \
    define_IEEE_754_T_BIAS(T_BITS)                                                                      \
    define_IEEE_754_T_EXPONENT_MAX(T_BITS)                                                              \
    define_IEEE_754_T_IMPLICIT_BIT(T_BITS)                                                              \
                                                                                                        \
    define_IEEE_754_T_SUBNORMALS(T_BITS)                                                                \
    define_IEEE_754_T_ZERO(T_BITS)                                                                      \
    define_IEEE_754_T_INF(T_BITS)                                                                       \
    define_IEEE_754_T_NAN(T_BITS)                                                                       \
                                                                                                        \
    define_IEEE_754_T(T_BITS, floating_point_type)                                                      \


/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
** Standard IEEE 754 Floating-point Single Precision (binary32) Type
**
** The following macro expands-to/generates:
**      The specification details macro'ed and the IEEE_754_binary32 union type.
*/

make_IEEE_754_floating_point_type(           \
                                             \
    /* Floating Point Type : */ float,       \
    /*  Total width (bits) : */ 32,          \
    /*       Fraction bits : */ 23,          \
    /*        Integer bits : */ 0,           \
    /*       Exponent bits : */ 8,           \
    /*           Sign bits : */ 1            \
)

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
** Standard IEEE 754 Floating-point Double Precision (binary64) Type
**
** The following macro expands-to/generates:
**      The specification details macro'ed and the IEEE_754_binary64 union type.
*/

make_IEEE_754_floating_point_type(           \
                                             \
    /* Floating Point Type : */ double,      \
    /*  Total width (bits) : */ 32,          \
    /*       Fraction bits : */ 23,          \
    /*        Integer bits : */ 0,           \
    /*       Exponent bits : */ 8,           \
    /*           Sign bits : */ 1            \
)

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
** Standard IEEE 754 Floating-point Extended Precision (binary80) Type
**
** The following macro expands-to/generates:
**      The specification details macro'ed and the IEEE_754_binary80 union type.
*/

# define ldouble long double

make_IEEE_754_floating_point_type(           \
                                             \
    /* Floating Point Type : */ ldouble,     \
    /*  Total width (bits) : */ 80,          \
    /*       Fraction bits : */ 63,          \
    /*        Integer bits : */ 1,           \
    /*       Exponent bits : */ 15,          \
    /*           Sign bits : */ 1            \
)

# undef ldouble

/*
** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
** Standard IEEE 754 Floating-point Quadruple Precision (binary128 Type8)
**
** The following macro expands-to/generates:
**      The specification details macro'ed and the IEEE_754_binary128 union type.
*/

make_IEEE_754_floating_point_type(           \
                                             \
    /* Floating Point Type : */ __float128,  \
    /*  Total width (bits) : */ 128,         \
    /*       Fraction bits : */ 112,         \
    /*        Integer bits : */ 0,           \
    /*       Exponent bits : */ 15,          \
    /*           Sign bits : */ 1            \
)

# undef DEFINE
# undef glue

#endif /* IEEE_754_TYPES1_H */
