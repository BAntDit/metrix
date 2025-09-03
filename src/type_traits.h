//
// Created by anton on 5/27/22.
//

#ifndef METRIX_TYPE_TRAITS_H
#define METRIX_TYPE_TRAITS_H

#include <type_traits>
#include "type_list.h"

namespace metrix {
template<typename T, template<typename...> typename Primary>
struct is_specialization_of : std::false_type
{};

template<template<typename...> typename Primary, typename... Args>
struct is_specialization_of<Primary<Args...>, Primary> : std::true_type
{};

template<typename T, template<typename...> typename Primary>
inline constexpr bool is_specialization_of_v = is_specialization_of<T, Primary>::value;

template<typename MemberFunctionPtr>
struct member_function_traits;

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...)>
{
	using return_type = Ret;
	using argument_type_list = type_list<Args...>;
	using class_type = Class;
};

template<typename MemberFunctionPtr>
using member_function_return_type_t = typename member_function_traits<MemberFunctionPtr>::return_type; 

template<typename MemberFunctionPtr>
using member_function_argument_type_list_t = typename member_function_traits<MemberFunctionPtr>::argument_type_list; 

template<typename MemberFunctionPtr>
using member_function_class_type_t = typename member_function_traits<MemberFunctionPtr>::class_type; 
}

#endif // METRIX_TYPE_TRAITS_H
