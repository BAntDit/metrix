//
// Created by bantdit on 1/28/19.
//

#ifndef METRIX_ENUM_H
#define METRIX_ENUM_H

#include <type_traits>

namespace metrix {
template<typename E>
constexpr auto value_cast(E e) -> std::underlying_type_t<E>
{
    return static_cast<std::underlying_type_t<E>>(e);
}
}

#endif // METRIX_ENUM_H
