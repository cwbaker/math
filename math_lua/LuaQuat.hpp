#ifndef MATH_LUAQUAT_HPP_INCLUDED
#define MATH_LUAQUAT_HPP_INCLUDED

struct lua_State;

namespace math
{

struct quat;
extern const char* QUAT;
void quat_openlib( lua_State* lua_state );
int quat_push( lua_State* lua_state, const quat& q );
const quat& quat_to( lua_State* lua_state, int index );
const quat* quat_test( lua_State* lua_state, int index );

}

#endif
