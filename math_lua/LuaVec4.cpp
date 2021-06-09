//
// LuaVec4.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LuaVec4.hpp"
#include <math/vec4.ipp>
#include <math/scalar.ipp>
#include <lua.hpp>

using namespace math;

const char* math::VEC4 = "vec4";

namespace math
{

static int vec4_x( lua_State* lua_state );
static int vec4_y( lua_State* lua_state );
static int vec4_z( lua_State* lua_state );
static int vec4_w( lua_State* lua_state );
static int vec4_xyzw( lua_State* lua_state );
static int vec4_srgb( lua_State* lua_state );
static int vec4_zero( lua_State* lua_state );
static int vec4_one( lua_State* lua_state );
static int vec4_add( lua_State* lua_state );
static int vec4_subtract( lua_State* lua_state );
static int vec4_multiply( lua_State* lua_state );
static int vec4_divide( lua_State* lua_state );
static int vec4_unary_minus( lua_State* lua_state );
static int vec4_lerp( lua_State* lua_state );
static int vec4_normalize( lua_State* lua_state );
static int vec4_length( lua_State* lua_state );
static int vec4_dot( lua_State* lua_state );
static int vec4_transparent( lua_State* lua_state );
static int vec4_opaque( lua_State* lua_state );

}

void math::vec4_openlib( lua_State* lua_state )
{
    const luaL_Reg functions [] =
    {
        { "x", &vec4_x },
        { "y", &vec4_y },
        { "z", &vec4_z },
        { "w", &vec4_w },
        { "red", &vec4_x },
        { "green", &vec4_y },
        { "blue", &vec4_z },
        { "alpha", &vec4_w },
        { "xyzw", &vec4_xyzw },
        { "srgb", &vec4_srgb },
        { "zero", &vec4_zero },
        { "one", &vec4_one },
        { "lerp", &vec4_lerp },
        { "normalize", &vec4_normalize },
        { "length", &vec4_length },
        { "dot", &vec4_dot },
        { "transparent", &vec4_transparent },
        { "opaque", &vec4_opaque },
        { nullptr, nullptr }
    };
    
    const luaL_Reg metamethods [] = 
    {
        { "__add", &vec4_add },
        { "__sub", &vec4_subtract },
        { "__mul", &vec4_multiply },
        { "__div", &vec4_divide },
        { "__unm", &vec4_unary_minus },
        { nullptr, nullptr }
    };

    // Create vec4 prototype.
    lua_newtable( lua_state );
    luaL_setfuncs( lua_state, functions, 0 );
    lua_setglobal( lua_state, VEC4 );

    // Create vec4 metatable.
    luaL_newmetatable( lua_state, VEC4 );
    luaL_setfuncs( lua_state, metamethods, 0 );
    lua_getglobal( lua_state, VEC4 );
    lua_setfield( lua_state, -2, "__index" );
    lua_pop( lua_state, 1 );
}

int math::vec4_push( lua_State* lua_state, const math::vec4& vv )
{
    void* v = lua_newuserdata( lua_state, sizeof(vec4) );
    new (v) vec4( vv );
    luaL_setmetatable( lua_state, VEC4 );
    return 1;
}

const vec4& math::vec4_to( lua_State* lua_state, int index )
{
    return *reinterpret_cast<const vec4*>( luaL_checkudata(lua_state, index, VEC4) );
}

const vec4* math::vec4_test( lua_State* lua_state, int index )
{
    return reinterpret_cast<const vec4*>( luaL_testudata(lua_state, index, VEC4) );
}

int math::vec4_x( lua_State* lua_state )
{
    const vec4& v = vec4_to( lua_state, 1 );
    lua_pushnumber( lua_state, v.x );
    return 1;
}

int math::vec4_y( lua_State* lua_state )
{
    const vec4& v = vec4_to( lua_state, 1 );
    lua_pushnumber( lua_state, v.y );
    return 1;
}

int math::vec4_z( lua_State* lua_state )
{
    const vec4& v = vec4_to( lua_state, 1 );
    lua_pushnumber( lua_state, v.z );
    return 1;
}

int math::vec4_w( lua_State* lua_state )
{
    const vec4& v = vec4_to( lua_state, 1 );
    lua_pushnumber( lua_state, v.w );
    return 1;
}

int math::vec4_xyzw( lua_State* lua_state )
{
    float x = luaL_optnumber( lua_state, 1, 0.0f );
    float y = luaL_optnumber( lua_state, 2, 0.0f );
    float z = luaL_optnumber( lua_state, 3, 0.0f );
    float w = luaL_optnumber( lua_state, 4, 0.0f );
    return vec4_push( lua_state, vec4(x, y, z, w) );
}

int math::vec4_srgb( lua_State* lua_state )
{
    const vec4* rgba = vec4_test( lua_state, 1 );
    if ( rgba )
    {
        return vec4_push( lua_state, srgb(*rgba) );
    }

    float red = luaL_optnumber( lua_state, 1, static_cast<lua_Number>(1.0f) );
    float green = luaL_optnumber( lua_state, 2, static_cast<lua_Number>(1.0f) );
    float blue = luaL_optnumber( lua_state, 3, static_cast<lua_Number>(1.0f) );
    float alpha = luaL_optnumber( lua_state, 4, static_cast<lua_Number>(1.0f) );
    return vec4_push( lua_state, srgb(vec4(red, green, blue, alpha)) );
}

int math::vec4_zero( lua_State* lua_state )
{
    return vec4_push( lua_state, vec4(0.0f) );
}

int math::vec4_one( lua_State* lua_state )
{
    return vec4_push( lua_state, vec4(1.0f) );
}

int math::vec4_add( lua_State* lua_state )
{
    const vec4& v0 = vec4_to( lua_state, 1 );
    const vec4& v1 = vec4_to( lua_state, 2 );
    return vec4_push( lua_state, v0 + v1 );
}

int math::vec4_subtract( lua_State* lua_state )
{
    const vec4& v0 = vec4_to( lua_state, 1 );
    const vec4& v1 = vec4_to( lua_state, 2 );
    return vec4_push( lua_state, v0 - v1 );
}

int math::vec4_multiply( lua_State* lua_state )
{
    const vec4* v0 = vec4_test( lua_state, 1 );
    const vec4* v1 = vec4_test( lua_state, 2 );
    if ( v0 && v1 )
    {
        return vec4_push( lua_state, *v0 * *v1 );
    }
    else if ( v1 )
    {
        float scalar = luaL_checknumber( lua_state, 1 );
        return vec4_push( lua_state, scalar * *v1 );
    }
    else if ( v0 )
    {
        float scalar = luaL_checknumber( lua_state, 2 );
        return vec4_push( lua_state, scalar * *v0 );
    }
    return luaL_error( lua_state, "invalid arguments to vec4 multiply (expecting vec4 or number)" );
}

int math::vec4_divide( lua_State* lua_state )
{
    const vec4& v0 = vec4_to( lua_state, 1 );
    float scalar = luaL_checknumber( lua_state, 2 );
    return vec4_push( lua_state, v0 / scalar );
}

int math::vec4_unary_minus( lua_State* lua_state )
{
    const vec4& v = vec4_to( lua_state, 1 );
    return vec4_push( lua_state, -v );
}

int math::vec4_lerp( lua_State* lua_state )
{
    const vec4& v0 = vec4_to( lua_state, 1 );
    const vec4& v1 = vec4_to( lua_state, 2 );
    float t = clamp( luaL_checknumber(lua_state, 3), 0.0f, 1.0f );
    return vec4_push( lua_state, lerp(v0, v1, t) );
}

int math::vec4_normalize( lua_State* lua_state )
{
    const vec4& v0 = vec4_to( lua_state, 1 );
    return vec4_push( lua_state, normalize(v0) );
}

int math::vec4_length( lua_State* lua_state )
{
    const vec4& v = vec4_to( lua_state, 1 );
    return vec4_push( lua_state, length(v) );
}

int math::vec4_dot( lua_State* lua_state )
{
    const vec4& v0 = vec4_to( lua_state, 1 );
    const vec4& v1 = vec4_to( lua_state, 2 );
    return vec4_push( lua_state, dot(v0, v1) );
}

int math::vec4_transparent( lua_State* lua_state )
{
    const vec4& color = vec4_to( lua_state, 1 );
    float alpha = luaL_optnumber( lua_state, 2, 0.0f );
    return vec4_push( lua_state, vec4(color.x, color.y, color.z, alpha) );
}

int math::vec4_opaque( lua_State* lua_state )
{
    const vec4& color = vec4_to( lua_state, 1 );
    float alpha = luaL_optnumber( lua_state, 2, 1.0f );
    return vec4_push( lua_state, vec4(color.x, color.y, color.z, alpha) );
}
