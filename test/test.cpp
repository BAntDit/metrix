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

    static_assert(easy_mp::type_list<uint8_t, uint16_t, int32_t>::has_type<uint8_t>::value);
    static_assert(easy_mp::type_list<uint8_t, uint16_t, int32_t>::has_type<uint16_t>::value);
    static_assert(easy_mp::type_list<uint8_t, uint16_t, int32_t>::has_type<int32_t>::value);

    static_assert(easy_mp::type_list<uint8_t, uint16_t, int32_t>::has_type<int64_t>::value == false);

    static_assert(std::is_same_v<
        typename easy_mp::type_list<uint8_t, uint16_t, int8_t, int16_t>::get_type<1>::type,
        uint16_t>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_head_tail() {
    static_assert(std::is_same_v<
            typename easy_mp::head<easy_mp::type_list<uint8_t, uint16_t, int32_t>>::type,
            easy_mp::type_list<uint8_t>>);

    static_assert(std::is_same_v<
            typename easy_mp::tail<easy_mp::type_list<uint8_t, uint16_t, int32_t>>::type,
            easy_mp::type_list<uint16_t, int32_t>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_concat() {
    static_assert(std::is_same_v<
            typename easy_mp::concat<easy_mp::type_list<uint8_t, uint16_t>, easy_mp::type_list<int32_t>>::type,
            easy_mp::type_list<uint8_t, uint16_t, int32_t>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_cart_prod() {
    static_assert(std::is_same_v<
        typename easy_mp::cartesian_product<easy_mp::type_list<uint8_t>, easy_mp::type_list<uint16_t, int32_t >>::type,
        easy_mp::type_list<easy_mp::type_pair<uint8_t, uint16_t>, easy_mp::type_pair<uint8_t, int32_t>>
    >);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_zip() {
    static_assert(std::is_same_v<
        typename easy_mp::zip<
            easy_mp::type_list<uint8_t, int8_t, int16_t>,
            easy_mp::type_list<int32_t, uint16_t, int64_t>>::type,
        easy_mp::type_list<
            easy_mp::type_pair<uint8_t, int32_t>,
            easy_mp::type_pair<int8_t, uint16_t>,
            easy_mp::type_pair<int16_t, int64_t>
        >
    >);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_subtract() {
    static_assert(std::is_same_v<
        typename easy_mp::subtract<
            easy_mp::type_list<uint8_t, int8_t, int16_t, int64_t>,
            easy_mp::type_list<int8_t, int16_t>>::type,
        easy_mp::type_list<uint8_t, int64_t>
    >);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_inner_join() {
    static_assert(std::is_same_v<
        typename easy_mp::inner_join<
            easy_mp::type_list<uint8_t, int8_t, uint16_t, uint32_t>,
            easy_mp::type_list<uint64_t, int8_t, uint32_t, int16_t>
        >::type,
        easy_mp::type_list<int8_t, uint32_t>
    >);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_outer_join() {
    static_assert(std::is_same_v<
        typename easy_mp::outer_join<
            easy_mp::type_list<uint8_t, int8_t, uint16_t, uint32_t>,
            easy_mp::type_list<uint64_t, int8_t, uint32_t, int16_t>
        >::type,
        easy_mp::type_list<uint8_t, uint16_t, uint64_t, int16_t>
    >);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_left_outer_join() {
    static_assert(std::is_same_v<
        typename easy_mp::left_outer_join<
            easy_mp::type_list<uint8_t, int8_t, uint16_t, uint32_t>,
            easy_mp::type_list<uint64_t, int8_t, uint32_t, int16_t>
        >::type,
        easy_mp::type_list<uint8_t, uint16_t>
    >);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_right_outer_join() {
    static_assert(std::is_same_v<
            typename easy_mp::right_outer_join<
                    easy_mp::type_list<uint8_t, int8_t, uint16_t, uint32_t>,
                    easy_mp::type_list<uint64_t, int8_t, uint32_t, int16_t>
            >::type,
            easy_mp::type_list<uint64_t, int16_t>
    >);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_template_specialization() {
    static_assert(std::is_same<
        typename easy_mp::type_list<uint16_t, uint32_t>::specialization_t<std::tuple>,
            std::tuple<uint16_t, uint32_t>>::value);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_flatten() {
    static_assert(std::is_same<typename easy_mp::flatten<easy_mp::type_list<>>::type, easy_mp::type_list<>>::value);

    static_assert(std::is_same<
            typename easy_mp::flatten<easy_mp::type_list<easy_mp::type_list<uint16_t, uint32_t>>>::type,
            easy_mp::type_list<uint16_t, uint32_t>>::value);

    static_assert(std::is_same<
            typename easy_mp::flatten<
                    easy_mp::type_list<easy_mp::type_list<uint16_t>, easy_mp::type_list<uint32_t>>>::type,
            easy_mp::type_list<uint16_t, uint32_t>>::value);

    static_assert(std::is_same<
            typename easy_mp::flatten<
                    easy_mp::type_list<easy_mp::type_list<uint16_t>,
                    easy_mp::type_list<uint32_t>,
                    easy_mp::type_list<uint8_t, uint16_t>>>::type,
            easy_mp::type_list<uint16_t, uint32_t, uint8_t, uint16_t>>::value);

    return ::testing::AssertionSuccess();
}

TEST(TYPE_LIST_TEST, type_list_internals) {
    EXPECT_TRUE(type_list_test());
}

TEST(HEAD_TAIL_TEST, type_list_head_tail_test) {
    EXPECT_TRUE(type_list_head_tail());
}

TEST(CONCAT_TEST, type_list_concat_test) {
    EXPECT_TRUE(type_list_concat());
}

TEST(CART_PROD_TEST, type_list_cart_prod_test) {
    EXPECT_TRUE(type_list_cart_prod());
}

TEST(ZIP_TEST, type_list_zip_test) {
    EXPECT_TRUE(type_list_zip());
}

TEST(SUBTRACT_TEST, type_list_subtract_test) {
    EXPECT_TRUE(type_list_subtract());
}

TEST(INNER_JOIN_TEST, type_list_inner_join_test) {
    EXPECT_TRUE(type_list_inner_join());
}

TEST(OUTER_JOIN, type_list_outer_join_test) {
    EXPECT_TRUE(type_list_outer_join());
}

TEST(LEFT_OUTER_JOIN, type_list_left_outer_join_test) {
    EXPECT_TRUE(type_list_left_outer_join());
}

TEST(RIGHT_OUTER_JOIN, type_list_right_outer_join_test) {
    EXPECT_TRUE(type_list_right_outer_join());
}

TEST(TEMPLATE_SPECIALIZAATION, type_list_template_specialization_test) {
    EXPECT_TRUE(type_list_template_specialization());
}

TEST(FLATTEN, type_list_flatten_test) {
    EXPECT_TRUE(type_list_flatten());
}
