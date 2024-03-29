//
// scalar.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#ifndef SWEET_MATH_SCALAR_IPP_INCLUDED
#define SWEET_MATH_SCALAR_IPP_INCLUDED

#include "constants.hpp"
#include <assert.h>
#include <math.h>

namespace math
{

inline float clamp( float x, float minimum, float maximum )
{
    return x < minimum ? minimum
        : x > maximum ? maximum
        : x
    ;
}

inline float lerp( float x, float y, float t )
{
    assert( t >= 0.0f && t <= 1.0f );
    return x + (y - x) * t;
}

inline float smooth( float t )
{
    assert( t >= 0.0f && t <= 1.0f );
    return (1.0f - cosf(t * float(PI))) / 2.0f;
}

inline float sign( float x )
{
    return x >= 0.0f ? 1.0f : -1.0f;
}

inline float round( float x )
{
    return floorf( x + 0.5f );
}

inline float radians( float degrees )
{
    return degrees * float(PI) / 180.0f;
}

inline float degrees( float radians )
{
    return radians * 180.0f / float(PI);
}

}

#endif
