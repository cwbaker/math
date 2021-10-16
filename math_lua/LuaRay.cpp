//
// LuaRay.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LuaRay.hpp"
#include "LuaPlane.hpp"
#include "LuaVec3.hpp"
#include <math/ray.ipp>
#include <lua.hpp>

using namespace math;

const char* math::RAY = "ray";

namespace math
{

static int ray_origin( lua_State* lua_state );
static int ray_normal( lua_State* lua_state );
static int ray_new( lua_State* lua_state );
static int ray_lerp( lua_State* lua_state );
static int ray_intersect( lua_State* lua_state );

}

void math::ray_openlib( lua_State* lua_state )
{
    const luaL_Reg functions[] = 
    {
        { "origin", &ray_origin },
        { "normal", &ray_normal },
        { "new", &ray_new },
        { "lerp", &ray_lerp },
        { "intersect", &ray_intersect },
        { nullptr, nullptr }
    };
    
    // Create ray prototype.
    lua_newtable( lua_state );
    luaL_setfuncs( lua_state, functions, 0 );
    lua_setglobal( lua_state, RAY );

    // Create ray metatable.
    luaL_newmetatable( lua_state, RAY );
    lua_getglobal( lua_state, RAY );
    lua_setfield( lua_state, -2, "__index" );
    lua_pop( lua_state, 1 );
}

int math::ray_push( lua_State* lua_state, const math::ray& rr )
{
    void* r = lua_newuserdata( lua_state, sizeof(ray) );
    new (r) ray( rr );
    luaL_setmetatable( lua_state, RAY );
    return 1;
}

const ray& math::ray_to( lua_State* lua_state, int index )
{
    return *reinterpret_cast<const ray*>( luaL_checkudata(lua_state, index, RAY) );
}

const ray* math::ray_test( lua_State* lua_state, int index )
{
    return reinterpret_cast<const ray*>( luaL_testudata(lua_state, index, RAY) );
}

int math::ray_origin( lua_State* lua_state )
{
    const ray& r = ray_to( lua_state, 1 ) ;
    return vec3_push( lua_state, r.o );
}

int math::ray_normal( lua_State* lua_state )
{
    const ray& r = ray_to( lua_state, 1 ) ;
    return vec3_push( lua_state, r.n );
}

int math::ray_new( lua_State* lua_state )
{
    const vec3& o = vec3_to( lua_state, 1 );
    const vec3& n = vec3_to( lua_state, 2 );
    return ray_push( lua_state, ray(o, n) );
}

int math::ray_lerp( lua_State* lua_state )
{
    const ray& r = ray_to( lua_state, 1 );
    float t = float( luaL_checknumber(lua_state, 2) );
    return vec3_push( lua_state, r.lerp(t) );
}

int math::ray_intersect( lua_State* lua_state )
{
    const ray& r = ray_to( lua_state, 1 );
    const plane& p = plane_to( lua_state, 2 );
    float t = intersect( r, p );
    if ( t != INFINITY )
    {
        lua_pushnumber( lua_state, t );
        return 1;
    }
    return 0;
}
