#ifndef LODASH_INTERSECT_H
#define LODASH_INTERSECT_H

#include <iterator>
#include <set>
#include <type_traits>

#include "./type_utility/push_back_to_container.h"
#include "./type_utility/visit_container.h"

namespace lodash {

// Contains returns true if an element is present in a collection.
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

// ContainsBy returns true if predicate function return true.
template <typename Container, typename T>
inline bool Contains(Container&& c, T&& t) {
    return ContainsBy(std::forward<Container>(c), [&t](auto&& value) {
        return value == t;
    });
}

// EveryBy returns true if the predicate returns true for all of the elements in the collection or if the collection is
// empty.
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

// Every returns true if all elements of a subset are contained into a collection or if the subset is empty.
template <typename Container>
inline bool Every(Container&& c) {
    return EveryBy(std::forward<Container>(c), [](auto&& x) {
        return static_cast<bool>(x);
    });
}

// SomeBy returns true if the predicate returns true for any of the elements in the collection.
// If the collection is empty SomeBy returns false.
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

// Some returns true if at least 1 element of a subset is contained into a collection.
// If the subset is empty Some returns false.
template <typename Container>
inline bool Some(Container&& c) {
    return SomeBy(std::forward<Container>(c), [](auto&& x) {
        return static_cast<bool>(x);
    });
}

// NoneBy returns true if the predicate returns true for none of the elements in the collection or if the collection is
// empty.
template <typename Container, typename F>
inline bool NoneBy(Container&& c, F&& f) {
    bool ok = true;

    type_utility::VisitContainer(std::forward<Container>(c),
                                 std::forward<F>(f),
                                 [&ok](auto&& r, [[maybe_unused]] auto&& value, [[maybe_unused]] auto&& node_info) {
                                     ok = !r;
                                     return type_utility::ReturnInfo{.need_exit = !ok};
                                 });

    return ok;
}

// None returns true if no element of a subset are contained into a collection or if the subset is empty.
template <typename Container>
inline bool None(Container&& c) {
    return NoneBy(std::forward<Container>(c), [](auto&& x) {
        return static_cast<bool>(x);
    });
}

// Intersect returns the intersection between two collections.
template <typename Container>
inline auto Intersect(Container&& c1, Container&& c2) {
    using value_type = typename std::decay_t<Container>::value_type;

    auto res = std::decay_t<Container>();
    auto se = std::set<value_type>();

    for (auto&& v : c1) {
        se.insert(v);
    }

    for (auto&& v : c2) {
        if (se.count(v)) {
            type_utility::PushBackToContainer(res, v);
            se.erase(v);
        }
    }

    return res;
}

// Union returns all distinct elements from both collections.
// result returns will not change the order of elements relatively.
template <typename Container>
inline auto Union(Container&& c1, Container&& c2) {
    using value_type = typename std::decay_t<Container>::value_type;

    auto res = std::decay_t<Container>();
    auto se = std::set<value_type>();

    for (auto&& v : c1) {
        se.insert(v);
    }

    for (auto&& v : c2) {
        se.insert(v);
    }

    for (auto&& v : se) {
        type_utility::PushBackToContainer(res, v);
    }

    return res;
}

}  // namespace lodash

#endif  // LODASH_INTERSECT_H
