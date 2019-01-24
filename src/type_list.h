//
// Created by bantdit on 11/5/18.
//

#ifndef EASY_MP_TYPE_LIST_H
#define EASY_MP_TYPE_LIST_H

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace easy_mp {
namespace _internal {
template<typename T, typename... Ts>
struct get_type_index;

template<typename T, typename... Ts>
struct get_type_index<T, T, Ts...> : std::integral_constant<size_t, 0>
{};

template<typename T, typename Head, typename... Ts>
struct get_type_index<T, Head, Ts...> : std::integral_constant<size_t, 1 + get_type_index<T, Ts...>::value>
{};

template<typename T, typename... Ts>
struct has_type;

template<typename T, typename... Ts>
struct has_type<T, T, Ts...> : std::true_type
{};

template<typename T, typename Head, typename... Ts>
struct has_type<T, Head, Ts...> : has_type<T, Ts...>
{};

template<typename T>
struct has_type<T> : std::false_type
{};

template<typename Index, typename... Ts>
struct get_type;

template<typename Head, typename... Ts>
struct get_type<std::integral_constant<size_t, 0>, Head, Ts...>
{
    using type = Head;
};

template<size_t index, typename Head, typename... Ts>
struct get_type<std::integral_constant<size_t, index>, Head, Ts...>
  : get_type<std::integral_constant<size_t, index - 1>, Ts...>
{};
}

template<typename... Ts>
struct type_list
{
    static constexpr size_t size = sizeof...(Ts);

    template<template<typename...> typename templ>
    using specialization_t = templ<Ts...>;

    template<typename T>
    struct get_type_index : _internal::get_type_index<T, Ts...>
    {};

    template<typename T>
    struct has_type : _internal::has_type<T, Ts...>
    {};

    template<size_t index>
    struct get_type : _internal::get_type<std::integral_constant<size_t, index>, Ts...>
    {
        static_assert(index < sizeof...(Ts));
    };
};

template<typename TypeList>
struct tail;

template<typename T, typename... Ts>
struct tail<type_list<T, Ts...>>
{
    using type = type_list<Ts...>;
};

template<>
struct tail<type_list<>>
{
    using type = type_list<>;
};

template<typename TypeList>
struct head;

template<typename T, typename... Ts>
struct head<type_list<T, Ts...>>
{
    using type = type_list<T>;
};

template<>
struct head<type_list<>>
{
    using type = type_list<>;
};

template<typename T1, typename T2>
struct type_pair
{
    using type1 = T1;
    using type2 = T2;
};

template<typename... Ts>
struct concat;

template<typename... Ts, typename... Us>
struct concat<type_list<Ts...>, type_list<Us...>>
{
    using type = type_list<Ts..., Us...>;
};

template<typename T, typename U>
struct cartesian_product;

template<typename... Us>
struct cartesian_product<type_list<>, type_list<Us...>>
{
    using type = type_list<>;
};

template<typename Head, typename... Ts, typename... Us>
struct cartesian_product<type_list<Head, Ts...>, type_list<Us...>>
{
    using type = typename concat<type_list<type_pair<Head, Us>...>,
                                 typename cartesian_product<type_list<Ts...>, type_list<Us...>>::type>::type;
};

template<typename T, typename U>
struct zip;

template<typename... Us>
struct zip<type_list<>, type_list<Us...>>
{
    using type = type_list<>;
};

template<typename HeadT, typename... Ts, typename HeadU, typename... Us>
struct zip<type_list<HeadT, Ts...>, type_list<HeadU, Us...>>
{
    using type =
      typename concat<type_list<type_pair<HeadT, HeadU>>, typename zip<type_list<Ts...>, type_list<Us...>>::type>::type;
};

template<typename... TypeLists>
struct flatten;

template<>
struct flatten<type_list<>>
{
    using type = type_list<>;
};

template<typename... Ts>
struct flatten<type_list<type_list<Ts...>>>
{
    using type = type_list<Ts...>;
};

template<typename... Ts, typename... Us, typename... Rest>
struct flatten<type_list<type_list<Ts...>, type_list<Us...>, Rest...>>
{
    using type = typename concat<type_list<Ts..., Us...>, typename flatten<type_list<Rest...>>::type>::type;
};

template<typename T, typename U>
struct subtract;

template<>
struct subtract<type_list<>, type_list<>>
{
    using type = type_list<>;
};

template<typename Subtrahend>
struct subtract<type_list<>, Subtrahend>
{
    using type = type_list<>;
};

template<typename... Minuends>
struct subtract<type_list<Minuends...>, type_list<>>
{
    using type = type_list<Minuends...>;
};

template<typename Subtrahend, typename... Minuends>
struct subtract<type_list<Subtrahend, Minuends...>, type_list<Subtrahend>>
{
    using type = type_list<Minuends...>;
};

template<typename Subtrahend, typename MinuendHead, typename... Minuends>
struct subtract<type_list<MinuendHead, Minuends...>, type_list<Subtrahend>>
{
    using type = typename concat<type_list<MinuendHead>,
                                 typename subtract<type_list<Minuends...>, type_list<Subtrahend>>::type>::type;
};

template<typename SubtrahendHead, typename... Subtrahends, typename... Minuends>
struct subtract<type_list<Minuends...>, type_list<SubtrahendHead, Subtrahends...>>
{
    using type = typename subtract<typename subtract<type_list<Minuends...>, type_list<SubtrahendHead>>::type,
                                   type_list<Subtrahends...>>::type;
};

template<typename T, typename U>
struct inner_join;

template<>
struct inner_join<type_list<>, type_list<>>
{
    using type = type_list<>;
};

template<typename T, typename U>
struct inner_join<type_list<T>, type_list<U>>
{
    using type = type_list<>;
};

template<typename T>
struct inner_join<type_list<T>, type_list<T>>
{
    using type = type_list<T>;
};

template<typename... Ts>
struct inner_join<type_list<>, type_list<Ts...>>
{
    using type = type_list<>;
};

template<typename... Ts>
struct inner_join<type_list<Ts...>, type_list<>>
{
    using type = type_list<>;
};

template<typename HeadT, typename... Ts, typename HeadU, typename... Us>
struct inner_join<type_list<HeadT, Ts...>, type_list<HeadU, Us...>>
{
    using type = typename concat<typename concat<typename inner_join<type_list<HeadT>, type_list<HeadU>>::type,
                                                 typename inner_join<type_list<HeadT>, type_list<Us...>>::type>::type,
                                 typename inner_join<type_list<Ts...>, type_list<HeadU, Us...>>::type>::type;
};

template<typename T, typename U>
struct outer_join;

template<typename... Ts, typename... Us>
struct outer_join<type_list<Ts...>, type_list<Us...>>
{
private:
    using _intersect = typename inner_join<type_list<Ts...>, type_list<Us...>>::type;

public:
    using type = typename concat<typename subtract<type_list<Ts...>, _intersect>::type,
                                 typename subtract<type_list<Us...>, _intersect>::type>::type;
};

template<typename T, typename U>
struct left_outer_join;

template<typename... Ts, typename... Us>
struct left_outer_join<type_list<Ts...>, type_list<Us...>>
{
private:
    using _intersect = typename inner_join<type_list<Ts...>, type_list<Us...>>::type;

public:
    using type = typename subtract<type_list<Ts...>, _intersect>::type;
};

template<typename T, typename U>
struct right_outer_join;

template<typename... Ts, typename... Us>
struct right_outer_join<type_list<Ts...>, type_list<Us...>>
{
private:
    using _intersect = typename inner_join<type_list<Ts...>, type_list<Us...>>::type;

public:
    using type = typename subtract<type_list<Us...>, _intersect>::type;
};
}

#endif // EASY_MP_TYPE_LIST_H
