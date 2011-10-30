//
// scalar.ipp
// Copyright (c) 2010 - 2011 Charles Baker.  All rights reserved.
//

#ifndef SWEET_MATH_SCALAR_IPP_INCLUDED
#define SWEET_MATH_SCALAR_IPP_INCLUDED

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

inline float sign( float x )
{
    return x >= 0.0f ? 1.0f : -1.0f;
}

}

}

#endif