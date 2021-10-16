#ifndef MATH_PLANE_IPP_INCLUDED
#define MATH_PLANE_IPP_INCLUDED

//
// plane.ipp
// Copyright (c) Charles Baker.  All rights reserved.
//

#include "plane.hpp"
#include "vec3.ipp"

namespace math
{

inline plane::plane()
{
}

inline plane::plane( const plane& p )
: p( p.p )
, n( p.n )
, d( p.d )
{    
}
    
inline plane::plane( const vec3& pp, const vec3& nn, float dd )
: p( pp )
, n( nn )
, d( dd )
{
}

}

#endif
