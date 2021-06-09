#ifndef MATH_LUAVEC4_HPP_INCLUDED
#define MATH_LUAVEC4_HPP_INCLUDED

struct lua_State;

namespace math
{

struct vec4;
extern const char* VEC4;
void vec4_openlib( lua_State* lua_state );
int vec4_push( lua_State* lua_state, const vec4& vv );
const vec4& vec4_to( lua_State* lua_state, int index );
const vec4* vec4_test( lua_State* lua_state, int index );

}

#endif
