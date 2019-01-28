//
// Created by bantdit on 1/28/19.
//

#ifndef EASY_MP_ENUM_H
#define EASY_MP_ENUM_H

#include <type_traits>

namespace easy_mp {
template<typename E>
constexpr auto value_cast(E e) -> std::underlying_type_t<E>
{
    return static_cast<std::underlying_type_t<E>>(e);
}
}

#endif // EASY_MP_ENUM_H
