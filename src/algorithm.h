//
// Created by anton on 3/11/23.
//

#ifndef EASY_MP_ALGORITHM_H
#define EASY_MP_ALGORITHM_H

namespace easy_mp
{
template<typename T>
constexpr auto max(T a, T b) -> T { return std::max(a, b); }

template<typename T, typename... Rest>
constexpr auto max(T a, T b, Rest... rest) -> T
{
    return max(std::max(a, b), rest...);
}

template<typename T>
constexpr auto min(T a, T b) -> T { return std::min(a, b); }

template<typename T, typename... Rest>
constexpr auto min(T a, T b, Rest... rest) -> T
{
    return min(std::min(a, b), rest...);
}
}

#endif // EASY_MP_ALGORITHM_H
