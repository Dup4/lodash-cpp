#ifndef LODASH_TYPES_CHECK_IS_MAP_H
#define LODASH_TYPES_CHECK_IS_MAP_H

#include <type_traits>

namespace lodash::type_check {

template <typename, typename = void>
constexpr bool is_map{};

template <typename T>
constexpr bool is_map<T,
                      std::void_t<typename T::key_type,
                                  typename T::mapped_type,
                                  decltype(std::declval<T&>()[std::declval<const typename T::key_type&>()])> > = true;

}  // namespace lodash::type_check

#endif  // LODASH_TYPES_CHECK_IS_MAP_H
