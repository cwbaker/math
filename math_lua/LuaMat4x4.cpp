//
// LuaMat4x4.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LuaMat4x4.hpp"
#include "LuaQuat.hpp"
#include <math/mat4x4.ipp>
#include <math/quat.ipp>
#include <math/vec4.ipp>
#include <math/scalar.ipp>
#include <lua.hpp>
#include <stddef.h>

using namespace sweet;
using namespace math;

const char* math::MAT4X4 = "mat4x4";

void math::mat4x4_openlib( lua_State* lua_state )
{   
    const luaL_Reg functions[] = 
    {
        { "identity", mat4x4_identity },
        { "inverse", mat4x4_inverse },
        { "transpose", mat4x4_transpose },
        { "rotate", mat4x4_rotate },
        { "translate", mat4x4_translate },
        { "scale", mat4x4_scale },
        { "shear", mat4x4_shear },
        { "add", &mat4x4_add },
        { "subtract", &mat4x4_subtract },
        { "multiply", &mat4x4_multiply },
        { nullptr, nullptr }
    };
    lua_newtable( lua_state );
    luaL_setfuncs( lua_state, functions, 0 );
    lua_setglobal( lua_state, "mat4x4" );

    const luaL_Reg metatable_functions[] =
    {
        { "__add", &mat4x4_add },
        { "__sub", &mat4x4_subtract },
        { "__mul", &mat4x4_multiply }
    };
    luaL_newmetatable( lua_state, MAT4X4 );
    luaL_setfuncs( lua_state, metatable_functions, 0 );
    lua_getglobal( lua_state, "mat4x4" );
    lua_setfield( lua_state, -1, "__index" );
    lua_pop( lua_state, 1 );
}

int math::mat4x4_push( lua_State* lua_state, const math::mat4x4& m )
{
    void* m0 = lua_newuserdata( lua_state, sizeof(mat4x4) );
    new (m0) mat4x4( m );
    luaL_setmetatable( lua_state, MAT4X4 );
    return 1;
}

int math::mat4x4_identity( lua_State* lua_state )
{
    return mat4x4_push( lua_state, math::identity() );
}

int math::mat4x4_add( lua_State* lua_state )
{
    const mat4x4* m0 = reinterpret_cast<const mat4x4*>( luaL_checkudata(lua_state, 1, MAT4X4) );
    const mat4x4* m1 = reinterpret_cast<const mat4x4*>( luaL_checkudata(lua_state, 2, MAT4X4) );
    return mat4x4_push( lua_state, *m0 + *m1 );
}

int math::mat4x4_subtract( lua_State* lua_state )
{
    const mat4x4* m0 = reinterpret_cast<const mat4x4*>( luaL_checkudata(lua_state, 1, MAT4X4) );
    const mat4x4* m1 = reinterpret_cast<const mat4x4*>( luaL_checkudata(lua_state, 2, MAT4X4) );
    return mat4x4_push( lua_state, *m0 - *m1 );
}

int math::mat4x4_multiply( lua_State* lua_state )
{
    const mat4x4* m0 = reinterpret_cast<const mat4x4*>( luaL_checkudata(lua_state, 1, MAT4X4) );
    const mat4x4* m1 = reinterpret_cast<const mat4x4*>( luaL_checkudata(lua_state, 2, MAT4X4) );
    return mat4x4_push( lua_state, *m0 * *m1 );
}

int math::mat4x4_inverse( lua_State* lua_state )
{
    const mat4x4* m0 = reinterpret_cast<const mat4x4*>( luaL_checkudata(lua_state, 1, MAT4X4) );
    return mat4x4_push( lua_state, inverse(*m0) );
}

int math::mat4x4_transpose( lua_State* lua_state )
{
    const mat4x4* m0 = reinterpret_cast<const mat4x4*>( luaL_checkudata(lua_state, 1, MAT4X4) );
    return mat4x4_push( lua_state, transpose(*m0) );
}

int math::mat4x4_rotate( lua_State* lua_state )
{
    const quat* q0 = reinterpret_cast<const quat*>( luaL_checkudata(lua_state, 1, QUAT) );
    return mat4x4_push( lua_state, rotate(*q0) );
}

int math::mat4x4_translate( lua_State* lua_state )
{
    float tx = luaL_checknumber( lua_state, 1 );
    float ty = luaL_checknumber( lua_state, 2 );
    float tz = luaL_checknumber( lua_state, 3 );
    return mat4x4_push( lua_state, translate(tx, ty, tz) );
}

int math::mat4x4_scale( lua_State* lua_state )
{
    float sx = luaL_checknumber( lua_state, 1 );
    float sy = luaL_checknumber( lua_state, 2 );
    float sz = luaL_checknumber( lua_state, 3 );
    return mat4x4_push( lua_state, math::scale(sx, sy, sz) );
}

int math::mat4x4_shear( lua_State* lua_state )
{
    float hx = luaL_checknumber( lua_state, 1 );
    float hy = luaL_checknumber( lua_state, 2 );
    float hz = luaL_checknumber( lua_state, 3 );
    return mat4x4_push( lua_state, shear(hx, hy, hz) );
}
