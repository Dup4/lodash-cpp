#ifndef LODASH_TYPES_CHECK_HAS_FUNC_ARGS_H
#define LODASH_TYPES_CHECK_HAS_FUNC_ARGS_H

#include <functional>
#include <type_traits>

namespace lodash::types_check {

template <typename, typename T1, typename = void>
constexpr bool has_func_args_1{};

template <typename T, typename T1>
constexpr bool has_func_args_1<T, T1, std::void_t<decltype(std::invoke(std::declval<T>(), std::declval<T1>()))>> = true;

template <typename, typename T1, typename T2, typename = void>
constexpr bool has_func_args_2{};

template <typename T, typename T1, typename T2>
constexpr bool
        has_func_args_2<T,
                        T1,
                        T2,
                        std::void_t<decltype(std::invoke(std::declval<T>(), std::declval<T1>(), std::declval<T2>()))>> =
                true;

template <typename, typename T1, typename T2, typename T3, typename = void>
constexpr bool has_func_args_3{};

template <typename T, typename T1, typename T2, typename T3>
constexpr bool
        has_func_args_3<T,
                        T1,
                        T2,
                        T3,
                        std::void_t<decltype(std::invoke(
                                std::declval<T>(), std::declval<T1>(), std::declval<T2>(), std::declval<T3>()))>> =
                true;

template <typename, typename T1, typename T2, typename T3, typename T4, typename = void>
constexpr bool has_func_args_4{};

template <typename T, typename T1, typename T2, typename T3, typename T4>
constexpr bool has_func_args_4<
        T,
        T1,
        T2,
        T3,
        T4,
        std::void_t<decltype(std::invoke(
                std::declval<T>(), std::declval<T1>(), std::declval<T2>(), std::declval<T3>(), std::declval<T4>()))>> =
        true;

}  // namespace lodash::types_check

#endif  // LODASH_TYPES_CHECK_HAS_FUNC_ARGS_H
