#ifndef SWEET_MATH_LUARAY_HPP_INCLUDED
#define SWEET_MATH_LUARAY_HPP_INCLUDED

struct lua_State;

namespace math
{

struct ray;
extern const char* RAY;
void ray_openlib( lua_State* lua_state );
int ray_push( lua_State* lua_state, const ray& vv );
const ray& ray_to( lua_State* lua_state, int index );
const ray* ray_test( lua_State* lua_state, int index );

}

#endif
