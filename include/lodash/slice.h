#ifndef LODASH_SLICE_H
#define LODASH_SLICE_H

#include <iterator>
#include <type_traits>

#include "./types_check/test_func_args.h"

namespace lodash {

// template <typename Container, typename F>
// auto Map(Container&& c, F&& f) {
//     using return_type = std::result_of_t<F(T)>;

//     for (auto&& x : t) {
//         f(x);
//     }

//     return t;
// }

template <typename Container, typename F>
void ForEach(Container&& c, F&& f) {
    size_t ix = 0;

    for (auto&& x : c) {
        if constexpr (types_check::test_func_args_2_v<F, decltype(x), size_t>) {
            f(x, ix);
        } else if constexpr (types_check::test_func_args_1_v<F, decltype(x)>) {
            f(x);
        }

        ++ix;
    }
}

}  // namespace lodash

#endif  // LODASH_SLICE_H
