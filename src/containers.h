//
// Created by bantdit on 2/9/20.
//

#ifndef METRIX_CONTAINERS_H
#define METRIX_CONTAINERS_H

#include "type_list.h"

namespace metrix {
namespace _internal {
template<typename T, typename MaxSize>
struct _array_list;

template<typename T, size_t... idx>
struct _array_list<T, std::index_sequence<idx...>>
{
    using type = type_list<std::array<T, idx + 1>...>;
};
}

template<typename T, typename = void>
struct is_iterable : std::false_type
{};

template<typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>>
  : std::true_type
{};

template<typename T>
inline constexpr bool is_iterable_v = is_iterable<T>::value;

template<typename T, typename = void>
struct is_contiguous : std::false_type
{};

template<typename T>
struct is_contiguous<T, std::void_t<decltype(std::declval<T>().data())>> : std::true_type
{};

template<typename T>
inline constexpr bool is_contiguous_v = is_contiguous<T>::value;

template<typename T, size_t Size>
struct array_list
{
    using type = typename _internal::_array_list<T, std::make_index_sequence<Size>>::type;
};

template<typename T, size_t Size>
using array_list_t = typename array_list<T, Size>::type;
}

#endif // METRIX_CONTAINERS_H
