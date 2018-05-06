#ifndef SWEET_MATH_LUAVEC2_HPP_INCLUDED
#define SWEET_MATH_LUAVEC2_HPP_INCLUDED

struct lua_State;

namespace sweet
{

namespace math
{

struct vec2;

extern const char* VEC2;
void vec2_openlib( lua_State* lua_state );
int vec2_push( lua_State* lua_state, const math::vec2& vv );
int vec2_x( lua_State* lua_state );
int vec2_y( lua_State* lua_state );
int vec2_xy( lua_State* lua_state );
int vec2_zero( lua_State* lua_state );
int vec2_one( lua_State* lua_state );
int vec2_add( lua_State* lua_state );
int vec2_subtract( lua_State* lua_state );
int vec2_multiply( lua_State* lua_state );
int vec2_divide( lua_State* lua_state );
int vec2_unary_minus( lua_State* lua_state );
int vec2_lerp( lua_State* lua_state );
int vec2_normalize( lua_State* lua_state );
int vec2_length( lua_State* lua_state );

}

}

#endif
