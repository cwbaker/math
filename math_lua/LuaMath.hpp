#ifndef SWEET_MATH_LUAMATH_HPP_INCLUDED
#define SWEET_MATH_LUAMATH_HPP_INCLUDED

namespace sweet
{

namespace lua
{

class Lua;

}
    
namespace math
{

class LuaVec2;
class LuaVec3;
class LuaQuat;

class LuaMath
{
    math::LuaVec2* lua_vec2_;
    math::LuaVec3* lua_vec3_;
    math::LuaQuat* lua_quat_;

public:
    LuaMath( lua::Lua& lua );
    ~LuaMath();
    math::LuaVec2* lua_vec2() const;
    math::LuaVec3* lua_vec3() const;
    math::LuaQuat* lua_quat() const;
};

}

}

#endif
