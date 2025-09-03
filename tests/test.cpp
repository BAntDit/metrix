//
// Created by bantdit on 11/19/18.
//

#include <cstdint>
#include <gtest/gtest.h>
#include <list>
#include <type_traits>

#include "../src/algorithm.h"
#include "../src/containers.h"
#include "../src/enum.h"
#include "../src/type_list.h"
#include "../src/type_traits.h"

::testing::AssertionResult type_list_test()
{
    static_assert(metrix::type_list<uint8_t, uint16_t, int32_t>::size == 3);

    static_assert(metrix::type_list<uint8_t, uint16_t, int32_t>::get_type_index<uint8_t>::value == 0);
    static_assert(metrix::type_list<uint8_t, uint16_t, int32_t>::get_type_index<uint16_t>::value == 1);
    static_assert(metrix::type_list<uint8_t, uint16_t, int32_t>::get_type_index<int32_t>::value == 2);

    static_assert(metrix::type_list<uint8_t, uint16_t, int32_t>::has_type<uint8_t>::value);
    static_assert(metrix::type_list<uint8_t, uint16_t, int32_t>::has_type<uint16_t>::value);
    static_assert(metrix::type_list<uint8_t, uint16_t, int32_t>::has_type<int32_t>::value);

    static_assert(metrix::type_list<uint8_t, uint16_t, int32_t>::has_type<int64_t>::value == false);

    static_assert(
      std::is_same_v<typename metrix::type_list<uint8_t, uint16_t, int8_t, int16_t>::get_type<1>::type, uint16_t>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_head_tail()
{
    static_assert(std::is_same_v<typename metrix::head<metrix::type_list<uint8_t, uint16_t, int32_t>>::type,
                                 metrix::type_list<uint8_t>>);

    static_assert(std::is_same_v<typename metrix::tail<metrix::type_list<uint8_t, uint16_t, int32_t>>::type,
                                 metrix::type_list<uint16_t, int32_t>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_concat()
{
    static_assert(
      std::is_same_v<typename metrix::concat<metrix::type_list<uint8_t, uint16_t>, metrix::type_list<int32_t>>::type,
                     metrix::type_list<uint8_t, uint16_t, int32_t>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_cart_prod()
{
    static_assert(
      std::is_same_v<
        typename metrix::cartesian_product<metrix::type_list<uint8_t>, metrix::type_list<uint16_t, int32_t>>::type,
        metrix::type_list<metrix::type_pair<uint8_t, uint16_t>, metrix::type_pair<uint8_t, int32_t>>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_zip()
{
    static_assert(std::is_same_v<typename metrix::zip<metrix::type_list<uint8_t, int8_t, int16_t>,
                                                      metrix::type_list<int32_t, uint16_t, int64_t>>::type,
                                 metrix::type_list<metrix::type_pair<uint8_t, int32_t>,
                                                   metrix::type_pair<int8_t, uint16_t>,
                                                   metrix::type_pair<int16_t, int64_t>>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_subtract()
{
    static_assert(std::is_same_v<typename metrix::subtract<metrix::type_list<uint8_t, int8_t, int16_t, int64_t>,
                                                           metrix::type_list<int8_t, int16_t>>::type,
                                 metrix::type_list<uint8_t, int64_t>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_inner_join()
{
    static_assert(
      std::is_same_v<typename metrix::inner_join<metrix::type_list<uint8_t, int8_t, uint16_t, uint32_t>,
                                                 metrix::type_list<uint64_t, int8_t, uint32_t, int16_t>>::type,
                     metrix::type_list<int8_t, uint32_t>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_outer_join()
{
    static_assert(
      std::is_same_v<typename metrix::outer_join<metrix::type_list<uint8_t, int8_t, uint16_t, uint32_t>,
                                                 metrix::type_list<uint64_t, int8_t, uint32_t, int16_t>>::type,
                     metrix::type_list<uint8_t, uint16_t, uint64_t, int16_t>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_left_outer_join()
{
    static_assert(
      std::is_same_v<typename metrix::left_outer_join<metrix::type_list<uint8_t, int8_t, uint16_t, uint32_t>,
                                                      metrix::type_list<uint64_t, int8_t, uint32_t, int16_t>>::type,
                     metrix::type_list<uint8_t, uint16_t>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_right_outer_join()
{
    static_assert(
      std::is_same_v<typename metrix::right_outer_join<metrix::type_list<uint8_t, int8_t, uint16_t, uint32_t>,
                                                       metrix::type_list<uint64_t, int8_t, uint32_t, int16_t>>::type,
                     metrix::type_list<uint64_t, int16_t>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_template_specialization()
{
    static_assert(std::is_same<typename metrix::type_list<uint16_t, uint32_t>::specialization_t<std::tuple>,
                               std::tuple<uint16_t, uint32_t>>::value);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_flatten()
{
    static_assert(std::is_same<typename metrix::flatten<metrix::type_list<>>::type, metrix::type_list<>>::value);

    static_assert(std::is_same<typename metrix::flatten<metrix::type_list<metrix::type_list<uint16_t, uint32_t>>>::type,
                               metrix::type_list<uint16_t, uint32_t>>::value);

    static_assert(
      std::is_same<
        typename metrix::flatten<metrix::type_list<metrix::type_list<uint16_t>, metrix::type_list<uint32_t>>>::type,
        metrix::type_list<uint16_t, uint32_t>>::value);

    static_assert(std::is_same<typename metrix::flatten<metrix::type_list<metrix::type_list<uint16_t>,
                                                                          metrix::type_list<uint32_t>,
                                                                          metrix::type_list<uint8_t, uint16_t>>>::type,
                               metrix::type_list<uint16_t, uint32_t, uint8_t, uint16_t>>::value);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_list_distinct()
{
    static_assert(std::is_same<typename metrix::distinct<metrix::type_list<std::integral_constant<uint32_t, 1>,
                                                                           std::integral_constant<uint32_t, 1>,
                                                                           std::integral_constant<uint32_t, 2>,
                                                                           std::integral_constant<uint32_t, 3>>>::type,
                               metrix::type_list<std::integral_constant<uint32_t, 1>,
                                                 std::integral_constant<uint32_t, 2>,
                                                 std::integral_constant<uint32_t, 3>>>::value);

    static_assert(std::is_same<typename metrix::distinct<metrix::type_list<std::integral_constant<uint32_t, 1>>>::type,
                               metrix::type_list<std::integral_constant<uint32_t, 1>>>::value);

    static_assert(std::is_same<typename metrix::distinct<metrix::type_list<>>::type, metrix::type_list<>>::value);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult enum_value_cast()
{
    enum class TestEnum : uint32_t
    {
        TEST_VAL_1 = 0,
        TEST_VAL_2 = 1
    };

    static_assert(metrix::value_cast(TestEnum::TEST_VAL_2) == 1);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult containers_is_iterable()
{
    static_assert(metrix::is_iterable_v<std::vector<int>>);
    static_assert(!metrix::is_iterable_v<std::pair<int, int>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult containers_is_contiguous()
{
    static_assert(metrix::is_contiguous_v<std::vector<int>>);
    static_assert(!metrix::is_contiguous_v<std::list<int>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult to_variant()
{
    static_assert(
      std::is_same_v<std::variant<uint16_t, float>, metrix::to_variant_t<metrix::type_list<uint16_t, float>>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult array_list()
{
    static_assert(std::is_same_v<metrix::type_list<std::array<uint16_t, 1>, std::array<uint16_t, 2>>,
                                 metrix::array_list_t<uint16_t, 2>>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult type_traits_is_specialization_of()
{
    static_assert(metrix::is_specialization_of_v<std::variant<uint32_t, float>, std::variant>);
    static_assert(!metrix::is_specialization_of_v<std::variant<uint32_t, float>, std::tuple>);

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult algorithm_max()
{
    static_assert(metrix::max(3, 8, 6) == 8);
    return ::testing::AssertionSuccess();
}

::testing::AssertionResult algorithm_min()
{
    static_assert(metrix::min(3, 8, 6) == 3);
    return ::testing::AssertionSuccess();
}

TEST(ARRAY_LIST, array_list_test)
{
    EXPECT_TRUE(array_list());
}

TEST(TYPE_LIST_TO_VARIANT, type_list_to_variant)
{
    EXPECT_TRUE(to_variant());
}

TEST(TYPE_LIST_TEST, type_list_internals)
{
    EXPECT_TRUE(type_list_test());
}

TEST(HEAD_TAIL_TEST, type_list_head_tail_test)
{
    EXPECT_TRUE(type_list_head_tail());
}

TEST(CONCAT_TEST, type_list_concat_test)
{
    EXPECT_TRUE(type_list_concat());
}

TEST(CART_PROD_TEST, type_list_cart_prod_test)
{
    EXPECT_TRUE(type_list_cart_prod());
}

TEST(ZIP_TEST, type_list_zip_test)
{
    EXPECT_TRUE(type_list_zip());
}

TEST(SUBTRACT_TEST, type_list_subtract_test)
{
    EXPECT_TRUE(type_list_subtract());
}

TEST(INNER_JOIN_TEST, type_list_inner_join_test)
{
    EXPECT_TRUE(type_list_inner_join());
}

TEST(OUTER_JOIN, type_list_outer_join_test)
{
    EXPECT_TRUE(type_list_outer_join());
}

TEST(LEFT_OUTER_JOIN, type_list_left_outer_join_test)
{
    EXPECT_TRUE(type_list_left_outer_join());
}

TEST(RIGHT_OUTER_JOIN, type_list_right_outer_join_test)
{
    EXPECT_TRUE(type_list_right_outer_join());
}

TEST(TEMPLATE_SPECIALIZAATION, type_list_template_specialization_test)
{
    EXPECT_TRUE(type_list_template_specialization());
}

TEST(FLATTEN, type_list_flatten_test)
{
    EXPECT_TRUE(type_list_flatten());
}

TEST(DISTINCT, type_list_distinct_test)
{
    EXPECT_TRUE(type_list_distinct());
}

TEST(IS_ITERABLE, containers_is_iterable_test)
{
    EXPECT_TRUE(containers_is_iterable());
}

TEST(IS_CONTIGUOUS, containers_is_contiguous_test)
{
    EXPECT_TRUE(containers_is_contiguous());
}

TEST(IS_SPECIALIZATION_OF, type_traits_is_specialization_of_test)
{
    EXPECT_TRUE(type_traits_is_specialization_of());
}

struct TestStruct
{
    auto testMemberFunction(uint16_t a, uint32_t b) -> uint32_t { return a + b; }
};

TEST(MEMBER_FUNCTION_TRAITS, member_function_traits_test)
{
    auto memberFunctionTest =
      std::is_same_v<uint32_t, metrix::member_function_return_type_t<decltype(&TestStruct::testMemberFunction)>>;

    auto classTypeTest =
      std::is_same_v<TestStruct, metrix::member_function_class_type_t<decltype(&TestStruct::testMemberFunction)>>;

    auto argumentTypesTest =
      std::is_same_v<metrix::type_list<uint16_t, uint32_t>,
                     metrix::member_function_argument_type_list_t<decltype(&TestStruct::testMemberFunction)>>;

    EXPECT_TRUE(memberFunctionTest);
    EXPECT_TRUE(classTypeTest);
    EXPECT_TRUE(argumentTypesTest);
}

TEST(ALGORITHM_MAX, algorithm_max_test)
{
    EXPECT_TRUE(algorithm_max());
}

TEST(ALGORITHM_MIN, algorithm_min_test)
{
    EXPECT_TRUE(algorithm_min());
}
