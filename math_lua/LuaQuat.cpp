//
// LuaQuat.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LuaQuat.hpp"
#include "LuaVec3.hpp"
#include <math/quat.ipp>
#include <math/scalar.ipp>
#include <lua.hpp>
#include <stddef.h>

using namespace math;

const char* math::QUAT = "quat";

namespace math
{

static int quat_x( lua_State* lua_state );
static int quat_y( lua_State* lua_state );
static int quat_z( lua_State* lua_state );
static int quat_w( lua_State* lua_state );
static int quat_xyzw( lua_State* lua_state );
static int quat_identity( lua_State* lua_state );
static int quat_axis_angle( lua_State* lua_state );
static int quat_add( lua_State* lua_state );
static int quat_multiply( lua_State* lua_state );
static int quat_scale( lua_State* lua_state );
static int quat_slerp( lua_State* lua_state );
static int quat_normalize( lua_State* lua_state );
static int quat_dot( lua_State* lua_state );

}

void math::quat_openlib( lua_State* lua_state )
{
    const luaL_Reg functions[] = 
    {
        { "x", &quat_x },
        { "y", &quat_y },
        { "z", &quat_z },
        { "w", &quat_w },
        { "xyzw", &quat_xyzw },
        { "identity", &quat_identity },
        { "axis_angle", &quat_axis_angle },
        { "scale", &quat_scale },
        { "slerp", &quat_slerp },
        { "normalize", &quat_normalize },
        { "dot", &quat_dot },
        { "add", &quat_add },
        { "multiply", &quat_multiply },
        { nullptr, nullptr }
    };

    const luaL_Reg metatable_functions[] =
    {
        { "__add", &quat_add },
        { "__mul", &quat_multiply }
    };

    // Create the quat prototype.
    lua_newtable( lua_state );
    luaL_setfuncs( lua_state, functions, 0 );
    lua_setglobal( lua_state, QUAT );

    // Create the quat metatable.
    luaL_newmetatable( lua_state, QUAT );
    luaL_setfuncs( lua_state, metatable_functions, 0 );
    lua_getglobal( lua_state, QUAT );
    lua_setfield( lua_state, -2, "__index" );
    lua_pop( lua_state, 1 );
}

int math::quat_push( lua_State* lua_state, const math::quat& q )
{
    void* q0 = lua_newuserdata( lua_state, sizeof(math::quat) );
    new (q0) quat( q );
    luaL_setmetatable( lua_state, QUAT );
    return 1;
}

const math::quat& math::quat_to( lua_State* lua_state, int index )
{
    return *reinterpret_cast<const quat*>( luaL_checkudata(lua_state, index, QUAT) );
}

const math::quat* math::quat_test( lua_State* lua_state, int index )
{
    return reinterpret_cast<const quat*>( luaL_testudata(lua_state, index, QUAT) );
}

int math::quat_x( lua_State* lua_state )
{
    const quat& q = quat_to( lua_state, 1 );
    lua_pushnumber( lua_state, q.x );
    return 1;
}

int math::quat_y( lua_State* lua_state )
{
    const quat& q = quat_to( lua_state, 1 ) ;
    lua_pushnumber( lua_state, q.y );
    return 1;
}

int math::quat_z( lua_State* lua_state )
{
    const quat& q = quat_to( lua_state, 1 );
    lua_pushnumber( lua_state, q.z );
    return 1;
}

int math::quat_w( lua_State* lua_state )
{
    const quat& q = quat_to( lua_state, 1 );
    lua_pushnumber( lua_state, q.w );
    return 1;
}

int math::quat_xyzw( lua_State* lua_state )
{
    float x = float( luaL_optnumber(lua_state, 1, 0.0f) );
    float y = float( luaL_optnumber(lua_state, 2, 0.0f) );
    float z = float( luaL_optnumber(lua_state, 3, 0.0f) );
    float w = float( luaL_optnumber(lua_state, 4, 1.0f) );
    return quat_push( lua_state, math::quat(x, y, z, w) );
}

int math::quat_identity( lua_State* lua_state )
{
    return quat_push( lua_state, quat(0.0f, 0.0f, 0.0f, 1.0f) );
}

int math::quat_axis_angle( lua_State* lua_state )
{
    const vec3& axis = vec3_to( lua_state, 1 );
    float angle = float( luaL_checknumber(lua_state, 2) );
    return quat_push( lua_state, quat(axis, angle) );
}

int math::quat_add( lua_State* lua_state )
{
    const math::quat& q0 = quat_to( lua_state, 1 );
    const math::quat& q1 = quat_to( lua_state, 2 );
    return quat_push( lua_state, q0 + q1 );
}

int math::quat_multiply( lua_State* lua_state )
{
    const math::quat& q0 = quat_to( lua_state, 1 );
    const math::quat& q1 = quat_to( lua_state, 2 );
    return quat_push( lua_state, q0 * q1 );
}

int math::quat_scale( lua_State* lua_state )
{
    float scalar = float( luaL_checknumber(lua_state, 1) );
    const math::quat& q0 = quat_to( lua_state, 2 );
    return quat_push( lua_state, scalar * q0 );
}

int math::quat_slerp( lua_State* lua_state )
{
    const math::quat& q0 = quat_to( lua_state, 1 );
    const math::quat& q1 = quat_to( lua_state, 2 );
    float t = float( luaL_checknumber(lua_state, 3) );
    return quat_push( lua_state, slerp(q0, q1, clamp(t, 0.0f, 1.0f)) );
}

int math::quat_normalize( lua_State* lua_state )
{
    const quat& q0 = quat_to( lua_state, 1 );
    return quat_push( lua_state, normalize(q0) );
}

int math::quat_dot( lua_State* lua_state )
{
    const math::quat& q0 = quat_to( lua_state, 1 );
    const math::quat& q1 = quat_to( lua_state, 2 );
    lua_pushnumber( lua_state, dot(q0, q1) );
    return 1;
}
