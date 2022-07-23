#ifndef LODASH_TYPES_CHECK_TEST_FUNC_ARGS_H
#define LODASH_TYPES_CHECK_TEST_FUNC_ARGS_H

#include <functional>
#include <type_traits>

namespace lodash::types_check {

template <typename T, typename T1>
class test_func_args_1 {
private:
    template <typename U, typename U1>
    static constexpr auto check(int) -> decltype(std::invoke(std::declval<U>(), std::declval<U1>()), std::true_type());

    template <typename, typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T, T1>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T, typename T1>
inline constexpr bool test_func_args_1_v = test_func_args_1<T, T1>::value;

template <typename T, typename T1, typename T2>
class test_func_args_2 {
private:
    template <typename U, typename U1, typename U2>
    static constexpr auto check(int)
            -> decltype(std::invoke(std::declval<U>(), std::declval<U1>(), std::declval<U2>()), std::true_type());

    template <typename, typename, typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T, T1, T2>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T, typename T1, typename T2>
inline constexpr bool test_func_args_2_v = test_func_args_2<T, T1, T2>::value;

}  // namespace lodash::types_check

#endif  // LODASH_TYPES_CHECK_TEST_FUNC_ARGS_H
