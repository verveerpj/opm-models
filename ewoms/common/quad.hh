// -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// vi: set et ts=4 sw=4 sts=4:
/*
  Copyright (C) 2008-2012 by Andreas Lauser

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
*/
/*!
 * \file
 *
 * \brief This file provides the infrastructure to use quad-precision
 *        floating point values in the numerical models.
 */
#if !defined EWOMS_QUAD_HH && HAVE_QUAD
#define EWOMS_QUAD_HH

#include <opm/core/utility/ClassName.hpp>

#include <cmath>
#include <string>
#include <limits>
#include <iostream>

extern "C" {
#include <quadmath.h>
}

typedef __float128 quad;

namespace std {

// provide the numeric limits for the quad precision type
template <>
class numeric_limits<quad>
{
public:
    static const bool is_specialized = true;

    static quad min() throw()
    { return FLT128_MIN; }
    static quad max() throw()
    { return FLT128_MAX; }

    // number of bits in mantissa
    static const int digits = FLT128_MANT_DIG;
    // number of decimal digits
    static const int digits10 = FLT128_DIG;
    static const bool is_signed = true;
    static const bool is_integer = false;
    static const bool is_exact = false;
    static const int radix = 0;
    static quad epsilon() throw()
    { return FLT128_EPSILON; }
    static quad round_error() throw()
    { return 0.5; }

    static const int min_exponent = FLT128_MIN_EXP;
    static const int min_exponent10 = FLT128_MIN_10_EXP;
    static const int max_exponent = FLT128_MAX_EXP;
    static const int max_exponent10 = FLT128_MAX_10_EXP;

    static const bool has_infinity = true;
    static const bool has_quiet_NaN = true;
    static const bool has_signaling_NaN = true;
    static const float_denorm_style has_denorm = denorm_present;
    static const bool has_denorm_loss = false;
    static quad infinity() throw()
    {
        return __builtin_huge_valq();
    };
    static quad quiet_NaN() throw()
    { return __builtin_nan(""); }
    static quad signaling_NaN() throw()
    { return __builtin_nans(""); }
    static quad denorm_min() throw()
    { return FLT128_DENORM_MIN; }

    static const bool is_iec559 = true;
    static const bool is_bounded = true;
    static const bool is_modulo = false;

    static const bool traps = std::numeric_limits<double>::traps;
    static const bool tinyness_before
        = std::numeric_limits<double>::tinyness_before;
    static const float_round_style round_style = round_to_nearest;
};

inline std::ostream &operator<<(std::ostream &os, const quad &val)
{ return (os << double(val)); }

inline std::istream &operator>>(std::istream &is, quad &val)
{
    double tmp;
    std::istream &ret = (is >> tmp);
    val = tmp;
    return ret;
}

inline quad abs(quad val)
{ return (val < 0) ? -val : val; }

inline quad floor(quad val)
{ return floorq(val); }

inline quad ceil(quad val)
{ return ceilq(val); }

inline quad max(quad a, quad b)
{ return (a > b) ? a : b; }

inline quad min(quad a, quad b)
{ return (a < b) ? a : b; }

inline quad sqrt(quad val)
{ return sqrtq(val); }

template <class ExpType>
inline quad pow(quad base, ExpType exp)
{ return powq(base, exp); }

inline quad exp(quad val)
{ return expq(val); }

inline quad log(quad val)
{ return logq(val); }

inline quad sin(quad val)
{ return sinq(val); }

inline quad cos(quad val)
{ return cosq(val); }

inline quad tan(quad val)
{ return tanq(val); }

inline quad atan(quad val)
{ return atanq(val); }

inline quad atan2(quad a, quad b)
{ return atan2q(a, b); }

inline bool isfinite(quad val)
{ return !isnanq(val) && !isinfq(val); }

inline bool isnan(quad val)
{ return isnanq(val); }

inline bool isinf(quad val)
{ return isinfq(val); }

} // namespace std

// replace Dune::className by Opm::className since the former does not work
// with __float128
#define DUNE_CLASSNAME_HH
namespace Dune {
template <class T>
std::string className()
{ return Opm::className<T>(); }

template <class T>
std::string className(const T &)
{ return Opm::className<T>(); }
} // namespace Dune

#endif // EWOMS_QUAD_HH
