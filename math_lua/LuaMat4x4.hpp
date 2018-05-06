#ifndef SWEET_MATH_LUAMAT4X4_HPP_INCLUDED
#define SWEET_MATH_LUAMAT4X4_HPP_INCLUDED

struct lua_State;

namespace sweet
{

namespace math
{

struct mat4x4;

extern const char* MAT4X4;
void mat4x4_openlib( lua_State* lua_state );
int mat4x4_push( lua_State* lua_state, const math::mat4x4& m );
int mat4x4_identity( lua_State* lua_state );
int mat4x4_add( lua_State* lua_state );
int mat4x4_subtract( lua_State* lua_state );
int mat4x4_multiply( lua_State* lua_state );
int mat4x4_inverse( lua_State* lua_state );
int mat4x4_transpose( lua_State* lua_state );
int mat4x4_rotate( lua_State* lua_state );
int mat4x4_translate( lua_State* lua_state );
int mat4x4_scale( lua_State* lua_state );
int mat4x4_shear( lua_State* lua_state );

}

}

#endif
