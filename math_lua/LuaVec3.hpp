#ifndef MATH_LUAVEC3_HPP_INCLUDED
#define MATH_LUAVEC3_HPP_INCLUDED

struct lua_State;

namespace math
{

struct vec3;
extern const char* VEC3;
void vec3_openlib( lua_State* lua_state );
int vec3_push( lua_State* lua_state, const vec3& vv );
const vec3& vec3_to( lua_State* lua_state, int index );
const vec3* vec3_test( lua_State* lua_state, int index );

}

#endif
