#ifndef SWEET_MATH_LUAPLANE_HPP_INCLUDED
#define SWEET_MATH_LUAPLANE_HPP_INCLUDED

struct lua_State;

namespace math
{

struct plane;
extern const char* PLANE;
void plane_openlib( lua_State* lua_state );
int plane_push( lua_State* lua_state, const plane& vv );
const plane& plane_to( lua_State* lua_state, int index );
const plane* plane_test( lua_State* lua_state, int index );

}

#endif
