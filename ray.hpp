#ifndef MATH_RAY_HPP_INCLUDED
#define MATH_RAY_HPP_INCLUDED

#include "vec3.hpp"

namespace math
{

struct plane;

struct ray
{
    vec3 o;
    vec3 n;

    inline ray();
    inline ray( const ray& r );
    inline ray( const vec3& oo, const vec3& nn );    
    inline vec3 lerp( float t ) const;
};

inline float intersect( const ray& ray, const plane& plane );

}

#endif
