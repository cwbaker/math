#ifndef SWEET_MATH_LUAMATH_HPP_INCLUDED
#define SWEET_MATH_LUAMATH_HPP_INCLUDED

struct lua_State;

namespace sweet
{

namespace math
{

void math_openlibs( lua_State* lua_state );

}

}

#endif
