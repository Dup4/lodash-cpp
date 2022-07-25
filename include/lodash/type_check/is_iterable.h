#ifndef LODASH_TYPES_CHECK_IS_ITERABLE_H
#define LODASH_TYPES_CHECK_IS_ITERABLE_H

#include <type_traits>

namespace lodash::type_check {

template <typename, typename = void>
constexpr bool is_iterable{};

template <typename T>
constexpr bool is_iterable<T, std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())> > =
        true;

}  // namespace lodash::type_check

#endif  // LODASH_TYPES_CHECK_IS_ITERABLE_H
