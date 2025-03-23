//
// Created by anton on 5/27/22.
//

#ifndef METRIX_TYPE_TRAITS_H
#define METRIX_TYPE_TRAITS_H

#include <type_traits>

namespace metrix {
template<typename T, template<typename...> typename Primary>
struct is_specialization_of : std::false_type
{};

template<template<typename...> typename Primary, typename... Args>
struct is_specialization_of<Primary<Args...>, Primary> : std::true_type
{};

template<typename T, template<typename...> typename Primary>
inline constexpr bool is_specialization_of_v = is_specialization_of<T, Primary>::value;
}

#endif // METRIX_TYPE_TRAITS_H
