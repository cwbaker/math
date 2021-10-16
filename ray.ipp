#ifndef MATH_RAY_IPP_INCLUDED
#define MATH_RAY_IPP_INCLUDED

#include "ray.hpp"
#include "plane.hpp"
#include "constants.hpp"
#include "vec3.ipp"
#include <cmath>

namespace math
{

inline ray::ray()
{
}

inline ray::ray( const ray& r )
: o( r.o )
, n( r.n )
{    
}

inline ray::ray( const vec3& oo, const vec3& nn )
: o( oo )
, n( nn )
{
}

inline vec3 ray::lerp( float t ) const
{
    return o + t * n;    
}

inline float intersect( const ray& ray, const plane& plane )
{
    float theta = dot( ray.n, plane.n );
    if ( fabsf(theta) > EPSILON )
    {
        return plane.d - dot( ray.o, plane.n ) / theta;
    }
    return INFINITY;
}

}

#endif
