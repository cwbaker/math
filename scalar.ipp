//
// scalar.ipp
// Copyright (c) 2010 - 2011 Charles Baker.  All rights reserved.
//

#ifndef SWEET_MATH_SCALAR_IPP_INCLUDED
#define SWEET_MATH_SCALAR_IPP_INCLUDED

#include <sweet/assert/assert.hpp>

namespace sweet
{

namespace math
{

/**
*/
inline float clamp( float x, float minimum, float maximum )
{
    return x < minimum ? minimum
         : x > maximum ? maximum
         : x
         ;
}

inline float lerp( float x, float y, float t )
{
    SWEET_ASSERT( t >= 0.0f && t <= 1.0f );
    return x + (y - x) * t;
}

inline float sign( float x )
{
    return x >= 0.0f ? 1.0f : -1.0f;
}

}

}

#endif