#ifndef MATH_PLANE_HPP_INCLUDED
#define MATH_PLANE_HPP_INCLUDED

namespace math
{

struct plane
{
    vec3 p;
    vec3 n;
    float d;
    inline plane( const vec3& pp, const vec3& nn, float dd );
};

}

#endif
