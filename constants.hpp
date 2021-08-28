#pragma once

#include <cmath>
#include <limits>

namespace math
{

inline const float PI = 3.14159265358979f;
inline const float EPSILON = std::numeric_limits<float>::epsilon();

// INFINITY is defined as a macro in the math.h and cmath headers so using it
// as an identifier here breaks badly.  The cmath header is included from this
// file so that INFINITY is available albeit not as a constant in the math
// namespace.
// inline const float INFINITY = std::numeric_limits<float>::infinity();

}
