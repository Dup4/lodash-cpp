#ifndef LODASH_SLICE_H
#define LODASH_SLICE_H

#include <iterator>
#include <type_traits>

#include <iostream>

#include "./type_utility/visit_container.h"

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
    type_utility::VisitContainer(std::forward<Container>(c), std::forward<F>(f));
}

template <typename Container, typename F>
bool EveryBy(Container&& c, F&& f) {
    bool ok = true;

    type_utility::VisitContainer(std::forward<Container>(c), std::forward<F>(f), [&ok](auto&& x) {
        ok = x;
        return type_utility::ReturnInfo{.need_exit = !ok};
    });

    return ok;
}

template <typename Container>
bool Every(Container&& c) {
    return EveryBy(std::forward<Container>(c), [](auto&& x) {
        return static_cast<bool>(x);
    });
}

template <typename Container, typename F>
bool SomeBy(Container&& c, F&& f) {
    bool ok = false;

    type_utility::VisitContainer(std::forward<Container>(c), std::forward<F>(f), [&ok](auto&& x) {
        ok = x;
        return type_utility::ReturnInfo{.need_exit = ok};
    });

    return ok;
}

template <typename Container>
bool Some(Container&& c) {
    return SomeBy(std::forward<Container>(c), [](auto&& x) {
        return static_cast<bool>(x);
    });
}

}  // namespace lodash

#endif  // LODASH_SLICE_H
