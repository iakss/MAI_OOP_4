#pragma once

#include <type_traits>

namespace lib::concepts {

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

} // namespace lib::concepts
