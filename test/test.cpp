//
// Created by bantdit on 11/19/18.
//

#include <gtest/gtest.h>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "../src/type_list.h"

::testing::AssertionResult type_list_test() {
    static_assert(easy_mp::type_list<uint8_t, uint16_t, int32_t>::size == 3);

    static_assert(easy_mp::type_list<uint8_t, uint16_t, int32_t>::get_type_index<uint8_t>::value == 0);
    static_assert(easy_mp::type_list<uint8_t, uint16_t, int32_t>::get_type_index<uint16_t>::value == 1);
    static_assert(easy_mp::type_list<uint8_t, uint16_t, int32_t>::get_type_index<int32_t>::value == 2);

    // TODO:: ...

    return ::testing::AssertionSuccess();
}

TEST(TYPE_LIST_TEST, type_list_internals) {
    EXPECT_TRUE(type_list_test());
}
