#ifndef LODASH_SLICE_H
#define LODASH_SLICE_H

#include <iterator>
#include <type_traits>

#include <iostream>

#include "./type_utility/get_result_type.h"
#include "./type_utility/push_back_to_container.h"
#include "./type_utility/visit_container.h"

namespace lodash {

template <typename R, typename Container, typename F>
inline auto Map(Container&& c, F&& f) {
    auto res = R();

    type_utility::VisitContainer(std::forward<Container>(c),
                                 std::forward<F>(f),
                                 [&res](auto&& r, [[maybe_unused]] auto&& value, [[maybe_unused]] auto&& node_info) {
                                     type_utility::PushBackToContainer(res, r);
                                     return type_utility::ReturnInfo{};
                                 });

    return res;
}

template <typename Container, typename F>
inline auto Map(Container&& c, F&& f) {
    using r = type_utility::get_result_type_t<Container, F>;
    return Map<std::vector<r>>(std::forward<Container>(c), std::forward<F>(f));
}

template <typename Container, typename F>
inline auto Filter(Container&& c, F&& f) {
    auto res = std::decay_t<Container>();

    type_utility::VisitContainer(std::forward<Container>(c),
                                 std::forward<F>(f),
                                 [&res](auto&& r, auto&& value, [[maybe_unused]] auto&& node_info) {
                                     if (r) {
                                         type_utility::PushBackToContainer(res, value);
                                     }

                                     return type_utility::ReturnInfo{};
                                 });

    return res;
}

template <typename Container, typename F>
inline void ForEach(Container&& c, F&& f) {
    type_utility::VisitContainer(std::forward<Container>(c), std::forward<F>(f));
}

template <typename Container, typename F>
inline size_t CountBy(Container&& c, F&& f) {
    size_t count = 0;

    type_utility::VisitContainer(std::forward<Container>(c),
                                 std::forward<F>(f),
                                 [&count](auto&& r, [[maybe_unused]] auto&& value, [[maybe_unused]] auto&& node_info) {
                                     if (r) {
                                         ++count;
                                     }

                                     return type_utility::ReturnInfo{};
                                 });

    return count;
}

template <typename Container, typename T>
inline size_t Count(Container&& c, T&& t) {
    return CountBy(std::forward<Container>(c), [t](auto&& x) {
        return x == t;
    });
}

template <typename Container>
inline auto Compact(Container&& c) {
    using value_type = typename std::decay_t<Container>::value_type;
    auto zero = value_type();

    return Filter(std::forward<Container>(c), [zero](auto&& x) {
        return x != zero;
    });
}

}  // namespace lodash

#endif  // LODASH_SLICE_H
