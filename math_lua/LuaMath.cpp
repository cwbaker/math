//
// LuaMath.cpp
// Copyright (c) 2013 Charles Baker.  All rights reserved.
//

#include "LuaMath.hpp"
#include "LuaVec2.hpp"
#include "LuaVec3.hpp"
#include "LuaQuat.hpp"
#include <stddef.h>

using namespace sweet;
using namespace sweet::math;

LuaMath::LuaMath( lua::Lua& lua )
: lua_vec2_( NULL ),
  lua_vec3_( NULL ),
  lua_quat_( NULL )
{
    lua_vec2_ = new math::LuaVec2( lua );
    lua_vec3_ = new math::LuaVec3( lua );
    lua_quat_ = new math::LuaQuat( lua );
}

LuaMath::~LuaMath()
{
    delete lua_quat_;
    delete lua_vec3_;
    delete lua_vec2_;
}

math::LuaVec2* LuaMath::lua_vec2() const
{
    return lua_vec2_;
}

math::LuaVec3* LuaMath::lua_vec3() const
{
    return lua_vec3_;
}

math::LuaQuat* LuaMath::lua_quat() const
{
    return lua_quat_;
}

