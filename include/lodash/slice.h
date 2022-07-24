#ifndef LODASH_SLICE_H
#define LODASH_SLICE_H

#include <iterator>
#include <type_traits>

#include <iostream>

#include "./types_check/common.h"
#include "./types_check/has_func_args.h"
#include "./types_check/is_map.h"

namespace lodash {

// template <typename Container, typename F>
// auto Map(Container&& c, F&& f) {
//     using return_type = std::result_of_t<F(T)>;

//     for (auto&& x : t) {
//         f(x);
//     }

//     return t;
// }

template <typename Container, std::enable_if_t<types_check::is_map<std::decay_t<Container>>, bool> = true, typename F>
void ForEach(Container&& c, F&& f) {
    size_t ix = 0;

    using key_type = typename std::decay_t<Container>::key_type;
    using value_type = typename std::decay_t<Container>::mapped_type;

    auto begin = std::begin(c);
    auto end_it = std::end(c);

    while (begin != end_it) {
        if constexpr (types_check::has_func_args_2<F, decltype(*begin), size_t>) {
            f(*begin, ix);
        } else if constexpr (types_check::has_func_args_1<F, decltype(*begin)>) {
            f(*begin);
        } else {
            if constexpr (types_check::has_func_args_3<F, key_type, value_type&, size_t>) {
                f(begin->first, begin->second, ix);
            } else if constexpr (types_check::has_func_args_2<F, key_type, value_type&>) {
                f(begin->first, begin->second);
            } else {
                static_assert(types_check::false_v<Container>, "ForEach: invalid function arguments");
            }
        }

        ++ix;
        ++begin;
    }
}

template <typename Container, std::enable_if_t<!types_check::is_map<std::decay_t<Container>>, bool> = true, typename F>
void ForEach(Container&& c, F&& f) {
    size_t ix = 0;

    for (auto&& x : c) {
        if constexpr (types_check::has_func_args_2<F, decltype(x), size_t>) {
            f(x, ix);
        } else if constexpr (types_check::has_func_args_1<F, decltype(x)>) {
            f(x);
        } else {
            static_assert(types_check::false_v<Container>, "ForEach: invalid function arguments");
        }

        ++ix;
    }
}

}  // namespace lodash

#endif  // LODASH_SLICE_H
