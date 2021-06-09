//
// LuaVec3.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LuaVec3.hpp"
#include <math/vec3.ipp>
#include <math/scalar.ipp>
#include <lua.hpp>

using namespace math;

const char* math::VEC3 = "vec3";

namespace math
{

static int vec3_x( lua_State* lua_state );
static int vec3_y( lua_State* lua_state );
static int vec3_z( lua_State* lua_state );
static int vec3_xyz( lua_State* lua_state );
static int vec3_zero( lua_State* lua_state );
static int vec3_one( lua_State* lua_state );
static int vec3_add( lua_State* lua_state );
static int vec3_subtract( lua_State* lua_state );
static int vec3_multiply( lua_State* lua_state );
static int vec3_divide( lua_State* lua_state );
static int vec3_unary_minus( lua_State* lua_state );
static int vec3_lerp( lua_State* lua_state );
static int vec3_normalize( lua_State* lua_state );
static int vec3_length( lua_State* lua_state );
static int vec3_dot( lua_State* lua_state );
static int vec3_cross( lua_State* lua_state );
static int vec3_floor( lua_State* lua_state );
static int vec3_rgb_from_hsv( lua_State* lua_state );
static int vec3_rgb_from_hsl( lua_State* lua_state );

}

void math::vec3_openlib( lua_State* lua_state )
{
    const luaL_Reg functions [] = 
    {
        { "x", &vec3_x },
        { "y", &vec3_y },
        { "z", &vec3_z },
        { "xyz", &vec3_xyz },
        { "zero", &vec3_zero },
        { "one", &vec3_one },
        { "lerp", &vec3_lerp },
        { "normalize", &vec3_normalize },
        { "length", &vec3_length },
        { "dot", &vec3_dot },
        { "cross", &vec3_cross },
        { "floor", &vec3_floor },
        { "rgb_from_hsv", &vec3_rgb_from_hsv },
        { "rgb_from_hsl", &vec3_rgb_from_hsl },
        { "add", &vec3_add },
        { "subtract", &vec3_subtract },
        { "multiply", &vec3_multiply },
        { "divide", &vec3_divide },
        { nullptr, nullptr }
    };

    const luaL_Reg metamethods [] =
    {
        { "__add", &vec3_add },
        { "__sub", &vec3_subtract },
        { "__mul", &vec3_multiply },
        { "__div", &vec3_divide },
        { "__unm", &vec3_unary_minus }
    };

    // Create the vec3 prototype.
    lua_newtable( lua_state );
    luaL_setfuncs( lua_state, functions, 0 );
    lua_setglobal( lua_state, VEC3 );

    // Create the vec3 metatable.
    luaL_newmetatable( lua_state, VEC3 );
    luaL_setfuncs( lua_state, metamethods, 0 );
    lua_getglobal( lua_state, VEC3 );
    lua_setfield( lua_state, -2, "__index" );
    lua_pop( lua_state, 1 );
}

int math::vec3_push( lua_State* lua_state, const math::vec3& vv )
{
    void* v = lua_newuserdata( lua_state, sizeof(vec3) );
    new (v) vec3( vv );
    luaL_setmetatable( lua_state, VEC3 );
    return 1;
}

const vec3& math::vec3_to( lua_State* lua_state, int index )
{
    return *reinterpret_cast<const vec3*>( luaL_checkudata(lua_state, index, VEC3) );
}

const vec3* math::vec3_test( lua_State* lua_state, int index )
{
    return reinterpret_cast<const vec3*>( luaL_testudata(lua_state, index, VEC3) );
}

int math::vec3_x( lua_State* lua_state )
{
    const vec3& v = vec3_to( lua_state, 1 );
    lua_pushnumber( lua_state, v.x );
    return 1;
}

int math::vec3_y( lua_State* lua_state )
{
    const vec3& v = vec3_to( lua_state, 1 );
    lua_pushnumber( lua_state, v.y );
    return 1;
}

int math::vec3_z( lua_State* lua_state )
{
    const vec3& v = vec3_to( lua_state, 1 );
    lua_pushnumber( lua_state, v.z );
    return 1;
}

int math::vec3_xyz( lua_State* lua_state )
{
    float x = luaL_optnumber( lua_state, 1, 0.0f );
    float y = luaL_optnumber( lua_state, 2, 0.0f );
    float z = luaL_optnumber( lua_state, 3, 0.0f );
    return vec3_push( lua_state, vec3(x, y, z) );
}

int math::vec3_zero( lua_State* lua_state )
{
    return vec3_push( lua_state, vec3(0.0f, 0.0f, 0.0f) );
}

int math::vec3_one( lua_State* lua_state )
{
    return vec3_push( lua_state, vec3(1.0f, 1.0f, 1.0f) );
}

int math::vec3_add( lua_State* lua_state )
{
    const vec3& v0 = vec3_to( lua_state, 1 );
    const vec3& v1 = vec3_to( lua_state, 2 );
    return vec3_push( lua_state, v0 + v1 );
}

int math::vec3_subtract( lua_State* lua_state )
{
    const vec3& v0 = vec3_to( lua_state, 1 );
    const vec3& v1 = vec3_to( lua_state, 2 );
    return vec3_push( lua_state, v0 - v1 );
}

int math::vec3_multiply( lua_State* lua_state )
{
    const vec3* v0 = vec3_test( lua_state, 1 );
    const vec3* v1 = vec3_test( lua_state, 2 );
    if ( v0 && v1 )
    {
        return vec3_push( lua_state, *v0 * *v1 );
    }
    else if ( v1 )
    {
        float scalar = luaL_checknumber( lua_state, 1 );
        return vec3_push( lua_state, scalar * *v1 );
    }
    else if ( v0 )
    {
        float scalar = luaL_checknumber( lua_state, 2 );
        return vec3_push( lua_state, scalar * *v0 );
    }
    return luaL_error( lua_state, "invalid arguments to vec3 multiply (expecting vec3 or number)" );
}

int math::vec3_divide( lua_State* lua_state )
{
    const vec3& v0 = vec3_to( lua_state, 1 );
    float scalar = luaL_checknumber( lua_state, 2 );
    return vec3_push( lua_state, v0 / scalar );
}

int math::vec3_unary_minus( lua_State* lua_state )
{
    const vec3& v = vec3_to( lua_state, 1 );
    return vec3_push( lua_state, -v );
}

int math::vec3_lerp( lua_State* lua_state )
{
    const vec3& v0 = vec3_to( lua_state, 1 );
    const vec3& v1 = vec3_to( lua_state, 2 );
    float t = clamp( luaL_checknumber(lua_state, 3), 0.0f, 1.0f );
    return vec3_push( lua_state, lerp(v0, v1, t) );
}

int math::vec3_normalize( lua_State* lua_state )
{
    const vec3& v = vec3_to( lua_state, 1 );
    return vec3_push( lua_state, normalize(v) );
}

int math::vec3_length( lua_State* lua_state )
{
    const vec3& v = vec3_to( lua_state, 1 );
    lua_pushnumber( lua_state, length(v) );
    return 1;
}

int math::vec3_dot( lua_State* lua_state )
{
    const vec3& v0 = vec3_to( lua_state, 1 );
    const vec3& v1 = vec3_to( lua_state, 2 );
    lua_pushnumber( lua_state, dot(v0, v1) );
    return 1;  
}

int math::vec3_cross( lua_State* lua_state )
{
    const vec3& v0 = vec3_to( lua_state, 1 );
    const vec3& v1 = vec3_to( lua_state, 2 );
    return vec3_push( lua_state, cross(v0, v1) );
}

int math::vec3_floor( lua_State* lua_state )
{
    const vec3& v = vec3_to( lua_state, 1 );
    return vec3_push( lua_state, vec3(floorf(v.x), floorf(v.y), floorf(v.z)) );
}

int math::vec3_rgb_from_hsv( lua_State* lua_state )
{
    const vec3& hsv = vec3_to( lua_state, 1 );
    return vec3_push( lua_state, rgb_from_hsv(hsv) );
}

int math::vec3_rgb_from_hsl( lua_State* lua_state )
{
    const vec3& hsl = vec3_to( lua_state, 1 );
    return vec3_push( lua_state, rgb_from_hsl(hsl) );
}
