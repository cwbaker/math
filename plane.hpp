#ifndef MATH_PLANE_HPP_INCLUDED
#define MATH_PLANE_HPP_INCLUDED

#include "vec3.hpp"

namespace math
{

struct plane
{
    vec3 p;
    vec3 n;
    float d;

    inline plane();
    inline plane( const plane& p );
    inline plane( const vec3& pp, const vec3& nn, float dd );
};

}

#endif
