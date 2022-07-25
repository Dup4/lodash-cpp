#ifndef LODASH_TYPE_UTILITY_VISIT_CONTAINER_H
#define LODASH_TYPE_UTILITY_VISIT_CONTAINER_H

#include <type_traits>

#include "../type_check/common.h"
#include "../type_check/has_func_args.h"
#include "../type_check/is_map.h"

namespace lodash::type_utility {

struct NodeInfo {
    size_t ix;
    bool is_first;
    bool is_last;
};

struct ReturnInfo {
    bool need_exit{false};
};

inline auto default_visit_handler = []([[maybe_unused]] auto... t) -> ReturnInfo {
    return ReturnInfo{};
};

template <typename Container,
          std::enable_if_t<type_check::is_map<std::decay_t<Container>>, bool> = true,
          typename F,
          typename H>
inline void VisitContainer(Container&& c, F&& f, H&& h) {
    size_t ix = 0;

    using key_type = typename std::decay_t<Container>::key_type;
    using mapped_type = typename std::decay_t<Container>::mapped_type;
    using value_type = typename std::decay_t<Container>::value_type;

    auto begin = std::begin(c);
    auto end_it = std::end(c);

    while (begin != end_it) {
        auto node_info = NodeInfo{ix, begin == std::begin(c), begin == std::prev(end_it)};
        if constexpr (type_check::has_func_args_2<F, value_type&, size_t>) {
            using return_type = std::result_of_t<F(value_type&, size_t)>;
            if constexpr (std::is_void_v<return_type>) {
                f(*begin, ix);
            } else {
                auto res = h(f(*begin, ix), *begin, node_info);
                if (res.need_exit) {
                    break;
                }
            }
        } else if constexpr (type_check::has_func_args_1<F, value_type&>) {
            using return_type = std::result_of_t<F(value_type&)>;
            if constexpr (std::is_void_v<return_type>) {
                f(*begin);
            } else {
                auto res = h(f(*begin), *begin, node_info);
                if (res.need_exit) {
                    break;
                }
            }
        } else {
            if constexpr (type_check::has_func_args_3<F, key_type, mapped_type&, size_t>) {
                using return_type = std::result_of_t<F(key_type, mapped_type&, size_t)>;
                if constexpr (std::is_void_v<return_type>) {
                    f(begin->first, begin->second, ix);
                } else {
                    auto res = h(f(begin->first, begin->second, ix), *begin, node_info);
                    if (res.need_exit) {
                        break;
                    }
                }
            } else if constexpr (type_check::has_func_args_2<F, key_type, mapped_type&>) {
                using return_type = std::result_of_t<F(key_type, mapped_type&)>;
                if constexpr (std::is_void_v<return_type>) {
                    f(begin->first, begin->second);
                } else {
                    auto res = h(f(begin->first, begin->second), *begin, node_info);
                    if (res.need_exit) {
                        break;
                    }
                }
            } else {
                static_assert(type_check::false_v<Container>, "invalid function arguments");
            }
        }

        ++ix;
        ++begin;
    }
}

template <typename Container,
          std::enable_if_t<!type_check::is_map<std::decay_t<Container>>, bool> = true,
          typename F,
          typename H>
inline void VisitContainer(Container&& c, F&& f, H&& h) {
    size_t ix = 0;

    using value_type = typename std::decay_t<Container>::value_type;

    auto begin = std::begin(c);
    auto end_it = std::end(c);

    while (begin != end_it) {
        auto node_info = NodeInfo{ix, begin == std::begin(c), begin == std::prev(end_it)};
        if constexpr (type_check::has_func_args_2<F, value_type&, size_t>) {
            using return_type = std::result_of_t<F(value_type&, size_t)>;
            if constexpr (std::is_void_v<return_type>) {
                f(*begin, ix);
            } else {
                auto res = h(f(*begin, ix), *begin, node_info);
                if (res.need_exit) {
                    break;
                }
            }
        } else if constexpr (type_check::has_func_args_1<F, value_type&>) {
            using return_type = std::result_of_t<F(value_type&)>;
            if constexpr (std::is_void_v<return_type>) {
                f(*begin);
            } else {
                auto res = h(f(*begin), *begin, node_info);
                if (res.need_exit) {
                    break;
                }
            }
        } else {
            static_assert(type_check::false_v<Container>, "invalid function arguments");
        }

        ++ix;
        ++begin;
    }
}

template <typename Container, typename F>
inline void VisitContainer(Container&& c, F&& f) {
    VisitContainer(std::forward<Container>(c), std::forward<F>(f), default_visit_handler);
}

}  // namespace lodash::type_utility

#endif  // LODASH_TYPE_UTILITY_VISIT_CONTAINER_H
