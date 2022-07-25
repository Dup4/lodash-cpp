#ifndef LODASH_TYPE_UTILITY_GET_RESULT_TYPE_H
#define LODASH_TYPE_UTILITY_GET_RESULT_TYPE_H

#include <iterator>
#include <type_traits>
#include <vector>

#include "../types_check/common.h"
#include "../types_check/has_func_args.h"
#include "../types_check/is_map.h"

namespace lodash::type_utility {

template <typename Container, typename F>
inline constexpr auto get_result_type() {
    if constexpr (!types_check::is_map<std::decay_t<Container>>) {
        using value_type = typename std::decay_t<Container>::value_type;

        if constexpr (types_check::has_func_args_2<F, value_type&, size_t>) {
            using return_type = std::result_of_t<F(value_type&, size_t)>;
            struct _ {
                using type = return_type;
            };

            return _{};
        } else if constexpr (types_check::has_func_args_1<F, value_type&>) {
            using return_type = std::result_of_t<F(value_type&)>;
            struct _ {
                using type = return_type;
            };

            return _{};
        } else {
            static_assert(types_check::false_v<Container>, "invalid function arguments");
        }
    } else {
        using key_type = typename std::decay_t<Container>::key_type;
        using mapped_type = typename std::decay_t<Container>::mapped_type;
        using value_type = typename std::decay_t<Container>::value_type;

        if constexpr (types_check::has_func_args_3<F, key_type, mapped_type&, size_t>) {
            using return_type = std::result_of_t<F(key_type, mapped_type&, size_t)>;
            struct _ {
                using type = return_type;
            };

            return _{};
        } else if constexpr (types_check::has_func_args_2<F, key_type, mapped_type&>) {
            using return_type = std::result_of_t<F(key_type, mapped_type&)>;
            struct _ {
                using type = return_type;
            };

            return _{};
        } else if constexpr (types_check::has_func_args_2<F, value_type&, size_t>) {
            using return_type = std::result_of_t<F(value_type&, size_t)>;
            struct _ {
                using type = return_type;
            };

            return _{};
        } else if constexpr (types_check::has_func_args_1<F, value_type&>) {
            using return_type = std::result_of_t<F(value_type&)>;
            struct _ {
                using type = return_type;
            };

            return _{};
        } else {
            static_assert(types_check::false_v<Container>, "invalid function arguments");
        }
    }
}

template <typename Container, typename F>
using get_result_type_t = typename decltype(get_result_type<Container, F>())::type;

}  // namespace lodash::type_utility

#endif  // LODASH_TYPE_UTILITY_GET_RESULT_TYPE_H
