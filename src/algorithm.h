//
// Created by anton on 3/11/23.
//

#ifndef METRIX_ALGORITHM_H
#define METRIX_ALGORITHM_H

#if defined(max)
#undef max
#endif

#if defined(min)
#undef min
#endif

namespace metrix {
template<typename T>
constexpr auto max(T a, T b) -> T
{
    return std::max(a, b);
}

template<typename T, typename... Rest>
constexpr auto max(T a, T b, Rest... rest) -> T
{
    return max(std::max(a, b), rest...);
}

template<typename T>
constexpr auto min(T a, T b) -> T
{
    return std::min(a, b);
}

template<typename T, typename... Rest>
constexpr auto min(T a, T b, Rest... rest) -> T
{
    return min(std::min(a, b), rest...);
}
}

#endif // METRIX_ALGORITHM_H
