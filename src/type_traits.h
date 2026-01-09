//
// Created by anton on 5/27/22.
//

#ifndef METRIX_TYPE_TRAITS_H
#define METRIX_TYPE_TRAITS_H

#include "type_list.h"
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

enum class MethodOverloadingByRefType : uint8_t
{
    None = 0,
    ForLvReference = 1,
    ForRvReference = 2
};

namespace _internal {
template<MethodOverloadingByRefType RefType,
         bool IsConstant,
         bool IsNoExcept,
         bool IsVolatile,
         typename Ret,
         typename Class,
         typename... Args>
struct member_function_details
{
    using return_type = Ret;
    using argument_type_list = type_list<Args...>;
    using class_type = Class;

    constexpr static bool is_constant = IsConstant;
    constexpr static bool is_noexcept = IsNoExcept;
    constexpr static bool is_volatile = IsVolatile;
    constexpr static MethodOverloadingByRefType overloading_by_ref_type = RefType;
};
}

template<typename MemberFunctionPtr>
struct member_function_traits;

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...)>
  : _internal::member_function_details<MethodOverloadingByRefType::None, false, false, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) noexcept>
  : _internal::member_function_details<MethodOverloadingByRefType::None, false, true, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...)&>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForLvReference, false, false, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) & noexcept>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForLvReference, false, true, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) &&>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForRvReference, false, false, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) && noexcept>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForRvReference, false, true, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const>
  : _internal::member_function_details<MethodOverloadingByRefType::None, true, false, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const noexcept>
  : _internal::member_function_details<MethodOverloadingByRefType::None, true, true, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const&>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForLvReference, true, false, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const && noexcept>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForRvReference, true, true, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const & noexcept>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForLvReference, true, true, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const&&>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForLvReference, true, false, false, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) volatile>
  : _internal::member_function_details<MethodOverloadingByRefType::None, false, false, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const volatile>
  : _internal::member_function_details<MethodOverloadingByRefType::None, true, false, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) volatile noexcept>
  : _internal::member_function_details<MethodOverloadingByRefType::None, false, true, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const volatile noexcept>
  : _internal::member_function_details<MethodOverloadingByRefType::None, true, true, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) volatile&>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForLvReference, false, false, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) volatile&&>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForRvReference, false, false, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const volatile&>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForLvReference, true, false, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const volatile & noexcept>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForLvReference, true, true, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) volatile & noexcept>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForLvReference, false, true, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) volatile && noexcept>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForRvReference, false, true, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const volatile && noexcept>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForRvReference, true, true, true, Ret, Class, Args...>
{};

template<typename Ret, class Class, typename... Args>
struct member_function_traits<Ret (Class::*)(Args...) const volatile&&>
  : _internal::
      member_function_details<MethodOverloadingByRefType::ForRvReference, true, false, true, Ret, Class, Args...>
{};

template<typename MemberFunctionPtr>
using member_function_return_type_t = typename member_function_traits<MemberFunctionPtr>::return_type;

template<typename MemberFunctionPtr>
using member_function_argument_type_list_t = typename member_function_traits<MemberFunctionPtr>::argument_type_list;

template<typename MemberFunctionPtr>
using member_function_class_type_t = typename member_function_traits<MemberFunctionPtr>::class_type;

template<typename MemberFunctionPtr>
constexpr bool member_function_is_constant_v = member_function_traits<MemberFunctionPtr>::is_constant;

template<typename MemberFunctionPtr>
constexpr bool member_function_is_noexcept_v = member_function_traits<MemberFunctionPtr>::is_noexcept;

template<typename MemberFunctionPtr>
constexpr bool member_function_is_volatile_v = member_function_traits<MemberFunctionPtr>::is_volatile;

template<typename MemberFunctionPtr>
constexpr MethodOverloadingByRefType member_function_overload_for_ref_v =
  member_function_traits<MemberFunctionPtr>::overloading_by_ref_type;
}

#endif // METRIX_TYPE_TRAITS_H
