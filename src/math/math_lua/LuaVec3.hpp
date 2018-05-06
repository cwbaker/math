#ifndef SWEET_MATH_LUAVEC3_HPP_INCLUDED
#define SWEET_MATH_LUAVEC3_HPP_INCLUDED

struct lua_State;

namespace sweet
{

namespace math
{

struct vec3;

extern const char* VEC3;
void vec3_openlib( lua_State* lua_state );
int vec3_push( lua_State* lua_state, const math::vec3& vv );
int vec3_x( lua_State* lua_state );
int vec3_y( lua_State* lua_state );
int vec3_z( lua_State* lua_state );
int vec3_xyz( lua_State* lua_state );
int vec3_zero( lua_State* lua_state );
int vec3_one( lua_State* lua_state );
int vec3_add( lua_State* lua_state );
int vec3_subtract( lua_State* lua_state );
int vec3_multiply( lua_State* lua_state );
int vec3_divide( lua_State* lua_state );
int vec3_unary_minus( lua_State* lua_state );
int vec3_lerp( lua_State* lua_state );
int vec3_normalize( lua_State* lua_state );
int vec3_length( lua_State* lua_state );
int vec3_dot( lua_State* lua_state );
int vec3_cross( lua_State* lua_state );
int vec3_rgb_from_hsv( lua_State* lua_state );
int vec3_rgb_from_hsl( lua_State* lua_state );

}

}

#endif
