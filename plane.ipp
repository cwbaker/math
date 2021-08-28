#ifndef MATH_PLANE_IPP_INCLUDED
#define MATH_PLANE_IPP_INCLUDED

//
// plane.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "plane.hpp"

namespace math
{
    
inline plane::plane( const vec3& pp, const vec3& nn, float dd )
: p( pp )
, n( nn )
, d( dd )
{
}

}

#endif
