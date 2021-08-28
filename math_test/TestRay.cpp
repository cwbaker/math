//
// TestIntersect.cpp
// Copyright (c) Charles Baker.  All rights reserved
//

#include <UnitTest++/UnitTest++.h>
#include <math/intersect.ipp>
#include <math/ray.ipp>
#include <math/plane.ipp>
#include <math/constants.hpp>

using std::numeric_limits;
using namespace math;

SUITE( Ray )
{
    TEST( ValidRayPlaneIntersect )
    {
        ray ray( vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f) );
        plane plane( vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) );
        float t = intersect( ray, plane );
        CHECK( t != INFINITY );
        CHECK_CLOSE( length(intersect.position(ray) - vec3(0.0f, 0.0f, 0.0f), 0.0f, EPSILON );
    }    

    TEST( InvalidRayPlaneIntersect )
    {
        ray ray( vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) );
        plane plane( vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) );
        float t = intersect( ray, plane );
        CHECK( t == INFINITY );
    }    
}
