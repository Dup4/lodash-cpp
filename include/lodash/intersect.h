#ifndef LODASH_INTERSECT_H
#define LODASH_INTERSECT_H

#include <iterator>
#include <type_traits>

#include <iostream>

#include "./type_utility/visit_container.h"

namespace lodash {

template <typename Container, typename F>
inline bool ContainsBy(Container&& c, F&& f) {
    bool ok = false;

    type_utility::VisitContainer(std::forward<Container>(c),
                                 std::forward<F>(f),
                                 [&ok](auto&& r, [[maybe_unused]] auto&& value, [[maybe_unused]] auto&& node_info) {
                                     ok = r;
                                     return type_utility::ReturnInfo{.need_exit = ok};
                                 });

    return ok;
}

template <typename Container, typename T>
inline bool Contains(Container&& c, T&& t) {
    return ContainsBy(std::forward<Container>(c), [&t](auto&& value) {
        return value == t;
    });
}

template <typename Container, typename F>
inline bool EveryBy(Container&& c, F&& f) {
    bool ok = true;

    type_utility::VisitContainer(std::forward<Container>(c),
                                 std::forward<F>(f),
                                 [&ok](auto&& r, [[maybe_unused]] auto&& value, [[maybe_unused]] auto&& node_info) {
                                     ok = r;
                                     return type_utility::ReturnInfo{.need_exit = !ok};
                                 });

    return ok;
}

template <typename Container>
inline bool Every(Container&& c) {
    return EveryBy(std::forward<Container>(c), [](auto&& x) {
        return static_cast<bool>(x);
    });
}

template <typename Container, typename F>
inline bool SomeBy(Container&& c, F&& f) {
    bool ok = false;

    type_utility::VisitContainer(std::forward<Container>(c),
                                 std::forward<F>(f),
                                 [&ok](auto&& r, [[maybe_unused]] auto&& value, [[maybe_unused]] auto&& node_info) {
                                     ok = r;
                                     return type_utility::ReturnInfo{.need_exit = ok};
                                 });

    return ok;
}

template <typename Container>
inline bool Some(Container&& c) {
    return SomeBy(std::forward<Container>(c), [](auto&& x) {
        return static_cast<bool>(x);
    });
}

}  // namespace lodash

#endif  // LODASH_INTERSECT_H
