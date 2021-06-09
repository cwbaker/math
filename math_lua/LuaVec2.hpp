#ifndef SWEET_MATH_LUAVEC2_HPP_INCLUDED
#define SWEET_MATH_LUAVEC2_HPP_INCLUDED

struct lua_State;

namespace math
{

struct vec2;
extern const char* VEC2;
void vec2_openlib( lua_State* lua_state );
int vec2_push( lua_State* lua_state, const vec2& vv );
const vec2& vec2_to( lua_State* lua_state, int index );
const vec2* vec2_test( lua_State* lua_state, int index );

}

#endif
