#ifndef MATH_LUAMAT4X4_HPP_INCLUDED
#define MATH_LUAMAT4X4_HPP_INCLUDED

struct lua_State;

namespace math
{

struct mat4x4;
extern const char* MAT4X4;
void mat4x4_openlib( lua_State* lua_state );
int mat4x4_push( lua_State* lua_state, const mat4x4& m );
const mat4x4& mat4x4_to( lua_State* lua_state, int index );
const mat4x4* mat4x4_test( lua_State* lua_state, int index );

}

#endif
