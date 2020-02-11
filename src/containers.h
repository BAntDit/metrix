//
// Created by bantdit on 2/9/20.
//

#ifndef EASY_MP_CONTAINERS_H
#define EASY_MP_CONTAINERS_H

namespace easy_mp {
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
}

#endif // EASY_MP_CONTAINERS_H
