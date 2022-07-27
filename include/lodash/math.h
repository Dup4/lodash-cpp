#ifndef LODASH_MATH_H
#define LODASH_MATH_H

#include <type_traits>

namespace lodash {

// Clamp clamps number within the inclusive lower and upper bounds.
template <typename T>
inline auto Clamp(T&& t, T&& lower, T&& upper) {
    if (t < lower) {
        return lower;
    }

    if (t > upper) {
        return upper;
    }

    return t;
}

// Summarizes the values in a collection.
template <typename Container>
inline auto Sum(Container&& c) {
    auto res = typename std::decay_t<Container>::value_type();

    for (auto&& v : c) {
        res += v;
    }

    return res;
}

// Summarizes the values in a collection by a custom function.
template <typename Container, typename F>
inline auto SumBy(Container&& c, F&& f) {
    auto res = typename std::decay_t<Container>::value_type();

    for (auto&& v : c) {
        res += f(v);
    }

    return res;
}

}  // namespace lodash

#endif  // LODASH_MATH_H
