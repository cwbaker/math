//
// LuaPlane.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LuaPlane.hpp"
#include "LuaPlane.hpp"
#include "LuaVec3.hpp"
#include <math/plane.ipp>
#include <lua.hpp>

using namespace math;

const char* math::PLANE = "plane";

namespace math
{

static int plane_origin( lua_State* lua_state );
static int plane_normal( lua_State* lua_state );
static int plane_distance( lua_State* lua_state );
static int plane_new( lua_State* lua_state );

}

void math::plane_openlib( lua_State* lua_state )
{
    const luaL_Reg functions[] = 
    {
        { "origin", &plane_origin },
        { "normal", &plane_normal },
        { "distance", &plane_distance },
        { "new", &plane_new },
        { nullptr, nullptr }
    };
    
    // Create plane prototype.
    lua_newtable( lua_state );
    luaL_setfuncs( lua_state, functions, 0 );
    lua_setglobal( lua_state, PLANE );

    // Create plane metatable.
    luaL_newmetatable( lua_state, PLANE );
    lua_getglobal( lua_state, PLANE );
    lua_setfield( lua_state, -2, "__index" );
    lua_pop( lua_state, 1 );
}

int math::plane_push( lua_State* lua_state, const math::plane& pp )
{
    void* p = lua_newuserdata( lua_state, sizeof(plane) );
    new (p) plane( pp );
    luaL_setmetatable( lua_state, PLANE );
    return 1;
}

const plane& math::plane_to( lua_State* lua_state, int index )
{
    return *reinterpret_cast<const plane*>( luaL_checkudata(lua_state, index, PLANE) );
}

const plane* math::plane_test( lua_State* lua_state, int index )
{
    return reinterpret_cast<const plane*>( luaL_testudata(lua_state, index, PLANE) );
}

int math::plane_origin( lua_State* lua_state )
{
    const plane& p = plane_to( lua_state, 1 ) ;
    return vec3_push( lua_state, p.p );
}

int math::plane_normal( lua_State* lua_state )
{
    const plane& p = plane_to( lua_state, 1 ) ;
    return vec3_push( lua_state, p.n );
}

int math::plane_distance( lua_State* lua_state )
{
    const plane& p = plane_to( lua_state, 1 ) ;
    lua_pushnumber( lua_state, p.d );
    return 1;
}

int math::plane_new( lua_State* lua_state )
{
    const vec3& o = vec3_to( lua_state, 1 );
    const vec3& n = vec3_to( lua_state, 2 );
    float d = float( luaL_checknumber(lua_state, 3) );
    return plane_push( lua_state, plane(o, n, d) );
}
