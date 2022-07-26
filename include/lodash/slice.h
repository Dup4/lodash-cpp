#ifndef LODASH_SLICE_H
#define LODASH_SLICE_H

#include <iterator>
#include <set>
#include <type_traits>

#include "./type_check/is_iterable.h"
#include "./type_utility/get_flatten_container_value_type.h"
#include "./type_utility/get_result_type.h"
#include "./type_utility/push_back_to_container.h"
#include "./type_utility/reduce_handler.h"
#include "./type_utility/visit_container.h"

namespace lodash {

// Map manipulates a slice and transforms it to a slice of another type.
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

// Reduce reduces collection to a value which is the accumulated result of running each element in collection
// through accumulator, where each successive invocation is supplied the return value of the previous.
template <typename Container, typename F, typename T>
inline auto Reduce(Container&& c, F&& f, T&& init) {
    auto h = type_utility::ReduceHandler(std::forward<F>(f), std::forward<T>(init));
    type_utility::VisitContainer(std::forward<Container>(c), h);
    return h.GetRes();
}

// Filter iterates over elements of collection, returning an container of all elements predicate returns truthy for.
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

// Reject is the opposite of Filter, this method returns the elements of collection that predicate does not return
// truthy for.
template <typename Container, typename F>
inline auto Reject(Container&& c, F&& f) {
    auto res = std::decay_t<Container>();

    type_utility::VisitContainer(std::forward<Container>(c),
                                 std::forward<F>(f),
                                 [&res](auto&& r, auto&& value, [[maybe_unused]] auto&& node_info) {
                                     if (!r) {
                                         type_utility::PushBackToContainer(res, value);
                                     }

                                     return type_utility::ReturnInfo{};
                                 });

    return res;
}

// ForEach iterates over elements of collection and invokes iteratee for each element.
template <typename Container, typename F>
inline void ForEach(Container&& c, F&& f) {
    type_utility::VisitContainer(std::forward<Container>(c), std::forward<F>(f));
}

// Flatten returns an container a single level deep.
template <typename Container>
inline auto Flatten(Container&& c) {
    auto res = std::vector<type_utility::get_flatten_container_value_type_t<Container>>();

    for (auto&& v : c) {
        if constexpr (type_check::is_iterable<std::decay_t<decltype(v)>>) {
            auto v_res = Flatten(v);
            res.insert(res.end(), v_res.begin(), v_res.end());
        } else {
            type_utility::PushBackToContainer(res, v);
        }
    }

    return res;
}

// Times invokes the iteratee n times, returning an array of the results of each invocation.
// The iteratee is invoked with index as argument.
template <typename F>
inline auto Times(size_t count, F&& f) {
    using result_type = std::result_of_t<F(size_t)>;
    auto res = std::vector<result_type>();

    for (size_t i = 0; i < count; i++) {
        type_utility::PushBackToContainer(res, f(i));
    }

    return res;
}

// Uniq returns a duplicate-free version of an array, in which only the first occurrence of each element is kept.
// The order of result values is determined by the order they occur in the array.
template <typename Container>
inline auto Uniq(Container&& c) {
    using value_type = typename std::decay_t<Container>::value_type;
    auto res = std::decay_t<Container>();
    auto se = std::set<value_type>();

    for (auto&& v : c) {
        if (se.find(v) == se.end()) {
            se.insert(v);
            type_utility::PushBackToContainer(res, v);
        }
    }

    return res;
}

// UniqBy returns a duplicate-free version of an array, in which only the first occurrence of each element is kept.
// The order of result values is determined by the order they occur in the array. It accepts `iteratee` which is
// invoked for each element in array to generate the criterion by which uniqueness is computed.
template <typename Container, typename F>
inline auto UniqBy(Container&& c, F&& f) {
    using result_type = type_utility::get_result_type_t<Container, F>;
    auto res = std::decay_t<Container>();
    auto se = std::set<result_type>();

    type_utility::VisitContainer(
            std::forward<Container>(c),
            std::forward<F>(f),
            [&se, &res](auto&& r, [[maybe_unused]] auto&& value, [[maybe_unused]] auto&& node_info) {
                if (se.find(r) == se.end()) {
                    se.insert(r);
                    type_utility::PushBackToContainer(res, value);
                }

                return type_utility::ReturnInfo{};
            });

    return res;
}

// CountBy counts the number of elements in the collection for which predicate is true.
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

// Count counts the number of elements in the collection that compare equal to value.
template <typename Container, typename T>
inline size_t Count(Container&& c, T&& t) {
    return CountBy(std::forward<Container>(c), [t](auto&& x) {
        return x == t;
    });
}

// Replace returns a copy of the slice with the first n non-overlapping instances of old replaced by new.
template <typename Container, typename T>
inline auto Replace(Container&& c, T&& old_element, T&& new_element, size_t n = -1) {
    auto res = std::decay_t<Container>();

    for (auto&& v : c) {
        if (v == old_element && n != 0) {
            type_utility::PushBackToContainer(res, new_element);
            --n;
        } else {
            type_utility::PushBackToContainer(res, v);
        }
    }

    return res;
}

// ReplaceAll returns a copy of the slice with all non-overlapping instances of old replaced by new.
template <typename Container, typename T>
inline auto ReplaceAll(Container&& c, T&& old_element, T&& new_element) {
    return Replace(std::forward<Container>(c), std::forward<T>(old_element), std::forward<T>(new_element), -1);
}

// Compact returns a slice of all non-zero elements.
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
