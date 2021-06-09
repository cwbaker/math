//
// LuaVec2.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LuaVec2.hpp"
#include <math/vec2.ipp>
#include <math/scalar.ipp>
#include <lua.hpp>

using namespace math;

const char* math::VEC2 = "vec2";

namespace math
{

static int vec2_x( lua_State* lua_state );
static int vec2_y( lua_State* lua_state );
static int vec2_xy( lua_State* lua_state );
static int vec2_zero( lua_State* lua_state );
static int vec2_one( lua_State* lua_state );
static int vec2_add( lua_State* lua_state );
static int vec2_subtract( lua_State* lua_state );
static int vec2_multiply( lua_State* lua_state );
static int vec2_divide( lua_State* lua_state );
static int vec2_unary_minus( lua_State* lua_state );
static int vec2_lerp( lua_State* lua_state );
static int vec2_normalize( lua_State* lua_state );
static int vec2_length( lua_State* lua_state );

}

void math::vec2_openlib( lua_State* lua_state )
{
    const luaL_Reg functions[] = 
    {
        { "x", &vec2_x },
        { "y", &vec2_y },
        { "xy", &vec2_xy },
        { "zero", &vec2_zero },
        { "one", &vec2_one },
        { "lerp", &vec2_lerp },
        { "normalize", &vec2_normalize },
        { "length", &vec2_length },
        { "add", &vec2_add },
        { "subtract", &vec2_subtract },
        { "multiply", &vec2_multiply },
        { "divide", &vec2_divide },
        { nullptr, nullptr }
    };
    
    const luaL_Reg metatable_functions[] =
    {
        { "__add", &vec2_add },
        { "__sub", &vec2_subtract },
        { "__mul", &vec2_multiply },
        { "__div", &vec2_divide },
        { "__unm", &vec2_unary_minus },
        { nullptr, nullptr }
    };

    // Create vec2 prototype.
    lua_newtable( lua_state );
    luaL_setfuncs( lua_state, functions, 0 );
    lua_setglobal( lua_state, VEC2 );

    // Create vec2 metatable.
    luaL_newmetatable( lua_state, VEC2 );
    luaL_setfuncs( lua_state, metatable_functions, 0 );
    lua_getglobal( lua_state, VEC2 );
    lua_setfield( lua_state, -2, "__index" );
    lua_pop( lua_state, 1 );
}

int math::vec2_push( lua_State* lua_state, const math::vec2& vv )
{
    void* v = lua_newuserdata( lua_state, sizeof(vec2) );
    new (v) vec2( vv );
    luaL_setmetatable( lua_state, VEC2 );
    return 1;
}

const vec2& math::vec2_to( lua_State* lua_state, int index )
{
    return *reinterpret_cast<const vec2*>( luaL_checkudata(lua_state, index, VEC2) );
}

const vec2* math::vec2_test( lua_State* lua_state, int index )
{
    return reinterpret_cast<const vec2*>( luaL_testudata(lua_state, index, VEC2) );
}

int math::vec2_x( lua_State* lua_state )
{
    const vec2& v = vec2_to( lua_state, 1 ) ;
    lua_pushnumber( lua_state, v.x );
    return 1;
}

int math::vec2_y( lua_State* lua_state )
{
    const vec2& v = vec2_to( lua_state, 1 ) ;
    lua_pushnumber( lua_state, v.y );
    return 1;
}

int math::vec2_xy( lua_State* lua_state )
{
    float x = luaL_optnumber( lua_state, 1, 0.0f );
    float y = luaL_optnumber( lua_state, 2, 0.0f );
    return vec2_push( lua_state, vec2(x, y) );
}

int math::vec2_zero( lua_State* lua_state )
{
    return vec2_push( lua_state, vec2(0.0f) );
}

int math::vec2_one( lua_State* lua_state )
{
    return vec2_push( lua_state, vec2(1.0f) );
}

int math::vec2_add( lua_State* lua_state )
{
    const vec2& v0 = vec2_to( lua_state, 1 );
    const vec2& v1 = vec2_to( lua_state, 2 );
    return vec2_push( lua_state, v0 + v1 );
}

int math::vec2_subtract( lua_State* lua_state )
{
    const vec2& v0 = vec2_to( lua_state, 1 );
    const vec2& v1 = vec2_to( lua_state, 2 );
    return vec2_push( lua_state, v0 - v1 );
}

int math::vec2_multiply( lua_State* lua_state )
{
    const vec2* v0 = vec2_test( lua_state, 1 );
    const vec2* v1 = vec2_test( lua_state, 2 );
    if ( v0 && v1 )
    {
        return vec2_push( lua_state, *v0 * *v1 );        
    }
    else if ( v1 )
    {
        float scalar = luaL_checknumber( lua_state, 1 );
        return vec2_push( lua_state, scalar * *v0 );
    }
    else if ( v0 )
    {
        float scalar = luaL_checknumber( lua_state, 2 );
        return vec2_push( lua_state, *v0 * scalar );
    }
    return luaL_error( lua_state, "invalid arguments to vec2 multiply (expecting vec2 or number)" );
}

int math::vec2_divide( lua_State* lua_state )
{
    const vec2& v0 = vec2_to( lua_state, 1 );
    float scalar = luaL_checknumber( lua_state, 2 );
    return vec2_push( lua_state, v0 / scalar );
}

int math::vec2_unary_minus( lua_State* lua_state )
{
    const vec2& v0 = vec2_to( lua_state, 1 );
    return vec2_push( lua_state, -v0 );
}

int math::vec2_lerp( lua_State* lua_state )
{
    const vec2& v0 = vec2_to( lua_state, 1 );
    const vec2& v1 = vec2_to( lua_state, 2 );
    float t = clamp( luaL_checknumber(lua_state, 3), 0.0f, 1.0f );
    return vec2_push( lua_state, lerp(v0, v1, t) );
}

int math::vec2_normalize( lua_State* lua_state )
{
    const vec2& v = vec2_to( lua_state, 1 );
    return vec2_push( lua_state, normalize(v) );
}

int math::vec2_length( lua_State* lua_state )
{
    const vec2& v = vec2_to( lua_state, 1 );
    return vec2_push( lua_state, length(v) );
}
