#ifndef LODASH_MATH_H
#define LODASH_MATH_H

#include <type_traits>
#include <vector>

namespace lodash {

// Range creates an array of numbers (positive and/or negative) with given length.
template <typename T = int32_t>
inline auto Range(T start, T stop, T step) {
    auto res = std::vector<T>();
    res.reserve(abs(stop - start) / abs(step));

    if (start == stop || step == 0) {
        return res;
    }

    if (start < stop) {
        if (step < 0) {
            return res;
        }

        for (auto i = start; i < stop; i += step) {
            res.push_back(i);
        }
    }

    if (start > stop) {
        if (step > 0) {
            return res;
        }

        for (auto i = start; i > stop; i += step) {
            res.push_back(i);
        }
    }

    return res;
}

template <typename T = int32_t>
inline auto Range(T start, T stop) {
    if (start <= stop) {
        return Range<T>(start, stop, T(1));
    } else {
        return Range<T>(start, stop, T(-1));
    }
}

template <typename T = int32_t>
inline auto Range(T stop) {
    return Range<T>(T(0), stop);
}

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
