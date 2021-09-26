//
// LuaMat4x4.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LuaMat4x4.hpp"
#include "LuaQuat.hpp"
#include "LuaVec3.hpp"
#include <math/mat4x4.ipp>
#include <math/quat.ipp>
#include <math/vec4.ipp>
#include <math/scalar.ipp>
#include <lua.hpp>
#include <stddef.h>

using namespace math;

const char* math::MAT4X4 = "mat4x4";

namespace math
{

static int mat4x4_element( lua_State* lua_state );
static int mat4x4_identity( lua_State* lua_state );
static int mat4x4_add( lua_State* lua_state );
static int mat4x4_subtract( lua_State* lua_state );
static int mat4x4_multiply( lua_State* lua_state );
static int mat4x4_inverse( lua_State* lua_state );
static int mat4x4_transpose( lua_State* lua_state );
static int mat4x4_rotate( lua_State* lua_state );
static int mat4x4_translate( lua_State* lua_state );
static int mat4x4_scale( lua_State* lua_state );
static int mat4x4_shear( lua_State* lua_state );
static int mat4x4_look_at( lua_State* lua_state );
static int mat4x4_orthogonal( lua_State* lua_state );
static int mat4x4_perspective( lua_State* lua_state );
static int mat4x4_perspective_fovy( lua_State* lua_state );
static int mat4x4_vulkan_perspective_fovy( lua_State* lua_state );
static int mat4x4_vulkan_perspective( lua_State* lua_state );

}

void math::mat4x4_openlib( lua_State* lua_state )
{   
    const luaL_Reg functions[] = 
    {
        { "element", mat4x4_element },
        { "identity", mat4x4_identity },
        { "inverse", mat4x4_inverse },
        { "transpose", mat4x4_transpose },
        { "rotate", mat4x4_rotate },
        { "translate", mat4x4_translate },
        { "scale", mat4x4_scale },
        { "shear", mat4x4_shear },
        { "look_at", mat4x4_look_at },
        { "orthogonal", &mat4x4_orthogonal },
        { "perspective", &mat4x4_perspective },
        { "perspective_fovy", &mat4x4_perspective_fovy },
        { "vulkan_perspective_fovy", &mat4x4_vulkan_perspective_fovy },
        { "vulkan_perspective", &mat4x4_vulkan_perspective },
        { "add", &mat4x4_add },
        { "subtract", &mat4x4_subtract },
        { "multiply", &mat4x4_multiply },
        { nullptr, nullptr }
    };

    const luaL_Reg metamethods[] =
    {
        { "__add", &mat4x4_add },
        { "__sub", &mat4x4_subtract },
        { "__mul", &mat4x4_multiply },
        { nullptr, nullptr }
    };

    // Create the mat4x4 prototype.
    lua_newtable( lua_state );
    luaL_setfuncs( lua_state, functions, 0 );
    lua_setglobal( lua_state, "mat4x4" );

    // Create the mat4x4 metatable.
    luaL_newmetatable( lua_state, MAT4X4 );
    luaL_setfuncs( lua_state, metamethods, 0 );
    lua_getglobal( lua_state, "mat4x4" );
    lua_setfield( lua_state, -2, "__index" );
    lua_pop( lua_state, 1 );
}

int math::mat4x4_push( lua_State* lua_state, const math::mat4x4& m )
{
    void* m0 = lua_newuserdata( lua_state, sizeof(mat4x4) );
    new (m0) mat4x4( m );
    luaL_setmetatable( lua_state, MAT4X4 );
    return 1;
}

const math::mat4x4& math::mat4x4_to( lua_State* lua_state, int index )
{
    return *reinterpret_cast<const mat4x4*>( luaL_checkudata(lua_state, index, MAT4X4) );
}

const math::mat4x4* math::mat4x4_test( lua_State* lua_state, int index )
{
    return reinterpret_cast<const mat4x4*>( luaL_testudata(lua_state, index, MAT4X4) );
}

int math::mat4x4_element( lua_State* lua_state )
{
    const int MATRIX = 1;
    const int ELEMENT = 2;
    const math::mat4x4& m0 = mat4x4_to( lua_state, MATRIX );
    const lua_Integer element = luaL_checkinteger( lua_state, ELEMENT );
    luaL_argcheck( lua_state, element >= 1 && element <= 16, ELEMENT, "element outside [1, 16]" );
    lua_pushnumber( lua_state, m0.m[element - 1] );
    return 1;
}

int math::mat4x4_identity( lua_State* lua_state )
{
    return mat4x4_push( lua_state, math::identity() );
}

int math::mat4x4_add( lua_State* lua_state )
{
    const mat4x4& m0 = mat4x4_to( lua_state, 1 );
    const mat4x4& m1 = mat4x4_to( lua_state, 2 );
    return mat4x4_push( lua_state, m0 + m1 );
}

int math::mat4x4_subtract( lua_State* lua_state )
{
    const mat4x4& m0 = mat4x4_to( lua_state, 1 );
    const mat4x4& m1 = mat4x4_to( lua_state, 2 );
    return mat4x4_push( lua_state, m0 - m1 );
}

int math::mat4x4_multiply( lua_State* lua_state )
{
    const mat4x4& m0 = mat4x4_to( lua_state, 1 );
    const mat4x4& m1 = mat4x4_to( lua_state, 2 );
    return mat4x4_push( lua_state, m0 * m1 );
}

int math::mat4x4_inverse( lua_State* lua_state )
{
    const mat4x4& m0 = mat4x4_to( lua_state, 1 );
    return mat4x4_push( lua_state, inverse(m0) );
}

int math::mat4x4_transpose( lua_State* lua_state )
{
    const mat4x4& m0 = mat4x4_to( lua_state, 1 );
    return mat4x4_push( lua_state, transpose(m0) );
}

int math::mat4x4_rotate( lua_State* lua_state )
{
    const vec3* axis = vec3_test( lua_state, 1 );
    if ( axis )
    {
        float angle = luaL_checknumber( lua_state, 2 );
        return mat4x4_push( lua_state, rotate(*axis, angle) );
    }
    const quat& q0 = quat_to( lua_state, 1 );
    return mat4x4_push( lua_state, rotate(q0) );
}

int math::mat4x4_translate( lua_State* lua_state )
{
    float tx = float( luaL_checknumber(lua_state, 1) );
    float ty = float( luaL_checknumber(lua_state, 2) );
    float tz = float( luaL_checknumber(lua_state, 3) );
    return mat4x4_push( lua_state, translate(tx, ty, tz) );
}

int math::mat4x4_scale( lua_State* lua_state )
{
    float sx = float( luaL_checknumber(lua_state, 1) );
    float sy = float( luaL_checknumber(lua_state, 2) );
    float sz = float( luaL_checknumber(lua_state, 3) );
    return mat4x4_push( lua_state, math::scale(sx, sy, sz) );
}

int math::mat4x4_shear( lua_State* lua_state )
{
    float hx = float( luaL_checknumber(lua_state, 1) );
    float hy = float( luaL_checknumber(lua_state, 2) );
    float hz = float( luaL_checknumber(lua_state, 3) );
    return mat4x4_push( lua_state, shear(hx, hy, hz) );
}

int math::mat4x4_look_at( lua_State* lua_state )
{
    const vec3& at = vec3_to( lua_state, 1 );
    const vec3& eye = vec3_to( lua_state, 2 );
    const vec3& up = vec3_to( lua_state, 3 );
    mat4x4_push( lua_state, look_at(at, eye, up) );
    return 1;
}

int math::mat4x4_orthogonal( lua_State* lua_state )
{
    float l = float( luaL_checknumber(lua_state, 1) );
    float r = float( luaL_checknumber(lua_state, 2) );
    float b = float( luaL_checknumber(lua_state, 3) );
    float t = float( luaL_checknumber(lua_state, 4) );
    float n = float( luaL_checknumber(lua_state, 5) );
    float f = float( luaL_checknumber(lua_state, 6) );
    mat4x4_push( lua_state, orthogonal(l, r, b, t, n, f) );
    return 1;
}

int math::mat4x4_perspective( lua_State* lua_state )
{
    float l = float( luaL_checknumber(lua_state, 1) );
    float r = float( luaL_checknumber(lua_state, 2) );
    float b = float( luaL_checknumber(lua_state, 3) );
    float t = float( luaL_checknumber(lua_state, 4) );
    float n = float( luaL_checknumber(lua_state, 5) );
    float f = float( luaL_checknumber(lua_state, 6) );
    mat4x4_push( lua_state, perspective(l, r, b, t, n, f) );
    return 1;
}

int math::mat4x4_perspective_fovy( lua_State* lua_state )
{
    float fovy = float( luaL_checknumber(lua_state, 1) );
    float aspect = float( luaL_checknumber(lua_state, 2) );
    float n = float( luaL_checknumber(lua_state, 3) );
    float f = float( luaL_checknumber(lua_state, 4) );
    mat4x4_push( lua_state, perspective(fovy, aspect, n, f) );
    return 1;
}

int math::mat4x4_vulkan_perspective_fovy( lua_State* lua_state )
{
    float fovy = float( luaL_checknumber(lua_state, 1) );
    float aspect = float( luaL_checknumber(lua_state, 2) );
    float n = float( luaL_checknumber(lua_state, 3) );
    float f = float( luaL_checknumber(lua_state, 4) );
    mat4x4_push( lua_state, vulkan_perspective(fovy, aspect, n, f) );
    return 1;
}

int math::mat4x4_vulkan_perspective( lua_State* lua_state )
{
    float l = float( luaL_checknumber(lua_state, 1) );
    float r = float( luaL_checknumber(lua_state, 2) );
    float b = float( luaL_checknumber(lua_state, 3) );
    float t = float( luaL_checknumber(lua_state, 4) );
    float n = float( luaL_checknumber(lua_state, 5) );
    float f = float( luaL_checknumber(lua_state, 6) );
    mat4x4_push( lua_state, vulkan_perspective(l, r, b, t, n, f) );
    return 1;
}
