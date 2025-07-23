//
// Created by bantdit on 1/28/19.
//

#ifndef METRIX_ENUM_H
#define METRIX_ENUM_H

#include <type_traits>
#include <limits>

namespace metrix {
namespace _internal {
template<typename T>
concept EnumConcept = std::is_enum_v<T>;
}

template<_internal::EnumConcept E>
constexpr auto value_cast(E e) -> std::underlying_type_t<E>
{
    return static_cast<std::underlying_type_t<E>>(e);
}

template<_internal::EnumConcept EnumType>
struct enum_bits
{
    using type_t = std::underlying_type_t<EnumType>;
    type_t value;

    template<typename... EnumItems>
    constexpr enum_bits(EnumItems... enumItems)
        requires(std::is_same_v<decltype(enumItems), EnumType> && ...)
      : value{ 0 }
    {
        if constexpr (sizeof...(enumItems) > 0) {
            value = (value_cast(enumItems) | ...);
        }
    }

    template<typename... EnumItems>
    constexpr auto test(EnumItems... enumItems) const -> bool
        requires(std::is_same_v<decltype(enumItems), EnumType> && ...)
    {
        return (value & (value_cast(enumItems) | ...));
    }

    template<typename... EnumItems>
    constexpr void set(EnumItems... enumItems)
        requires(std::is_same_v<decltype(enumItems), EnumType> && ...)
    {
        if constexpr (sizeof...(enumItems) > 0) {
            value = (value_cast(enumItems) | ... | (value));
        } else {
            value = std::numeric_limits<type_t>::max();
        }
    }

    template<typename... EnumItems>
    constexpr void reset(EnumItems... enumItems)
        requires(std::is_same_v<decltype(enumItems), EnumType> && ...)
    {
        if constexpr (sizeof...(enumItems) > 0) {
            value = ((~value_cast(enumItems)) & ... & (value));
        } else {
            value = 0;
        }
    }

    constexpr operator type_t() const { return value; }

    template<typename T>
    constexpr auto cast_to() const -> T requires std::is_convertible_v<type_t, T>
    {
        return static_cast<T>(value);
    }

    template<typename T>
    constexpr auto operator==(T rhs) const -> bool requires std::is_convertible_v<T, type_t>
    {
        return value == static_cast<type_t>(rhs);
    }

    template<typename T>
    constexpr auto operator!=(T rhs) const -> bool requires std::is_convertible_v<T, type_t>
    {
        return value != static_cast<type_t>(rhs);
    }
};
}

#endif // METRIX_ENUM_H
