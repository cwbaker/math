#ifndef SWEET_MATH_LUAQUAT_HPP_INCLUDED
#define SWEET_MATH_LUAQUAT_HPP_INCLUDED

struct lua_State;

namespace sweet
{

namespace math
{

struct quat;

extern const char* QUAT;
void quat_openlib( lua_State* lua_state );
int quat_push( lua_State* lua_state, const math::quat& q );
int quat_x( lua_State* lua_state );
int quat_y( lua_State* lua_state );
int quat_z( lua_State* lua_state );
int quat_w( lua_State* lua_state );
int quat_xyzw( lua_State* lua_state );
int quat_identity( lua_State* lua_state );
int quat_axis_angle( lua_State* lua_state );
int quat_add( lua_State* lua_state );
int quat_multiply( lua_State* lua_state );
int quat_scale( lua_State* lua_state );
int quat_slerp( lua_State* lua_state );
int quat_normalize( lua_State* lua_state );
int quat_dot( lua_State* lua_state );

}

}

#endif
