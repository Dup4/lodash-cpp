#ifndef LODASH_TYPE_UTILITY_VISIT_CONTAINER_H
#define LODASH_TYPE_UTILITY_VISIT_CONTAINER_H

#include <type_traits>

#include "../types_check/common.h"
#include "../types_check/has_func_args.h"
#include "../types_check/is_map.h"

namespace lodash::type_utility {

struct ReturnInfo {
    bool need_exit{false};
};

inline auto default_visit_handler = []([[maybe_unused]] auto... t) -> ReturnInfo {
    return ReturnInfo{};
};

template <typename Container,
          std::enable_if_t<types_check::is_map<std::decay_t<Container>>, bool> = true,
          typename F,
          typename H>
void VisitContainer(Container&& c, F&& f, H&& h) {
    size_t ix = 0;

    using key_type = typename std::decay_t<Container>::key_type;
    using value_type = typename std::decay_t<Container>::mapped_type;

    auto begin = std::begin(c);
    auto end_it = std::end(c);

    while (begin != end_it) {
        if constexpr (types_check::has_func_args_2<F, decltype(*begin), size_t>) {
            using return_type = std::result_of_t<F(decltype(*begin), size_t)>;
            if constexpr (std::is_void_v<return_type>) {
                f(*begin, ix);
            } else {
                auto res = h(f(*begin, ix));
                if (res.need_exit) {
                    break;
                }
            }
        } else if constexpr (types_check::has_func_args_1<F, decltype(*begin)>) {
            using return_type = std::result_of_t<F(decltype(*begin))>;
            if constexpr (std::is_void_v<return_type>) {
                f(*begin);
            } else {
                auto res = h(f(*begin));
                if (res.need_exit) {
                    break;
                }
            }
        } else {
            if constexpr (types_check::has_func_args_3<F, key_type, value_type&, size_t>) {
                using return_type = std::result_of_t<F(key_type, value_type&, size_t)>;
                if constexpr (std::is_void_v<return_type>) {
                    f(begin->first, begin->second, ix);
                } else {
                    auto res = h(f(begin->first, begin->second, ix));
                    if (res.need_exit) {
                        break;
                    }
                }
            } else if constexpr (types_check::has_func_args_2<F, key_type, value_type&>) {
                using return_type = std::result_of_t<F(key_type, value_type&)>;
                if constexpr (std::is_void_v<return_type>) {
                    f(begin->first, begin->second);
                } else {
                    auto res = h(f(begin->first, begin->second));
                    if (res.need_exit) {
                        break;
                    }
                }
            } else {
                static_assert(types_check::false_v<Container>, "invalid function arguments");
            }
        }

        ++ix;
        ++begin;
    }
}

template <typename Container,
          std::enable_if_t<!types_check::is_map<std::decay_t<Container>>, bool> = true,
          typename F,
          typename H>
void VisitContainer(Container&& c, F&& f, H&& h) {
    size_t ix = 0;

    for (auto&& x : c) {
        if constexpr (types_check::has_func_args_2<F, decltype(x), size_t>) {
            using return_type = std::result_of_t<F(decltype(x), size_t)>;
            if constexpr (std::is_void_v<return_type>) {
                f(x, ix);
            } else {
                auto res = h(f(x, ix));
                if (res.need_exit) {
                    break;
                }
            }
        } else if constexpr (types_check::has_func_args_1<F, decltype(x)>) {
            using return_type = std::result_of_t<F(decltype(x))>;
            if constexpr (std::is_void_v<return_type>) {
                f(x);
            } else {
                auto res = h(f(x));
                if (res.need_exit) {
                    break;
                }
            }
        } else {
            static_assert(types_check::false_v<Container>, "invalid function arguments");
        }

        ++ix;
    }
}

template <typename Container, typename F>
void VisitContainer(Container&& c, F&& f) {
    VisitContainer(std::forward<Container>(c), std::forward<F>(f), default_visit_handler);
}

}  // namespace lodash::type_utility

#endif  // LODASH_TYPE_UTILITY_VISIT_CONTAINER_H
