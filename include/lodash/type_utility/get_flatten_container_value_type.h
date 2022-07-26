#ifndef LODASH_TYPE_UTILITY_GET_FLATTEN_CONTAINER_VALUE_TYPE_H
#define LODASH_TYPE_UTILITY_GET_FLATTEN_CONTAINER_VALUE_TYPE_H

#include "../type_check/is_iterable.h"

namespace lodash::type_utility {

template <typename T>
inline constexpr auto get_flatten_container_value_type() {
    if constexpr (type_check::is_iterable<T>) {
        using value_type = typename std::decay_t<T>::value_type;
        return get_flatten_container_value_type<value_type>();
    } else {
        struct _ {
            using type = T;
        };

        return _{};
    }
}

template <typename T>
using get_flatten_container_value_type_t = typename decltype(get_flatten_container_value_type<T>())::type;

}  // namespace lodash::type_utility

#endif  // LODASH_TYPE_UTILITY_GET_FLATTEN_CONTAINER_VALUE_TYPE_H
