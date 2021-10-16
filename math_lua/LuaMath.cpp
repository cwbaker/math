//
// LuaMath.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LuaMath.hpp"
#include "LuaVec2.hpp"
#include "LuaVec3.hpp"
#include "LuaVec4.hpp"
#include "LuaQuat.hpp"
#include "LuaMat4x4.hpp"
#include "LuaRay.hpp"
#include "LuaPlane.hpp"
#include <lua.hpp>
#include <stddef.h>

using namespace math;

void math::math_openlibs( lua_State* lua_state )
{
    vec2_openlib( lua_state );
    vec3_openlib( lua_state );
    vec4_openlib( lua_state );
    quat_openlib( lua_state );
    mat4x4_openlib( lua_state );
    ray_openlib( lua_state );
    plane_openlib( lua_state );
}
