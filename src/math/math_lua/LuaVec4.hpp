#ifndef SWEET_MATH_LUAVEC4_HPP_INCLUDED
#define SWEET_MATH_LUAVEC4_HPP_INCLUDED

struct lua_State;

namespace sweet
{

namespace math
{

struct vec4;
extern const char* VEC4;
void vec4_openlib( lua_State* lua_state );
int vec4_push( lua_State* lua_state, const math::vec4& vv );
int vec4_x( lua_State* lua_state );
int vec4_y( lua_State* lua_state );
int vec4_z( lua_State* lua_state );
int vec4_w( lua_State* lua_state );
int vec4_xyzw( lua_State* lua_state );
int vec4_srgb( lua_State* lua_state );
int vec4_zero( lua_State* lua_state );
int vec4_one( lua_State* lua_state );
int vec4_add( lua_State* lua_state );
int vec4_subtract( lua_State* lua_state );
int vec4_multiply( lua_State* lua_state );
int vec4_divide( lua_State* lua_state );
int vec4_unary_minus( lua_State* lua_state );
int vec4_lerp( lua_State* lua_state );
int vec4_normalize( lua_State* lua_state );
int vec4_length( lua_State* lua_state );
int vec4_dot( lua_State* lua_state );
int vec4_transparent( lua_State* lua_state );
int vec4_opaque( lua_State* lua_state );

}

}

#endif
