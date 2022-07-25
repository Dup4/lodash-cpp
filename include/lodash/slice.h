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

    type_utility::VisitContainer(std::forward<Container>(c), std::forward<F>(f), [&res](auto&& x) {
        type_utility::PushBackToContainer(res, x);
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
inline void ForEach(Container&& c, F&& f) {
    type_utility::VisitContainer(std::forward<Container>(c), std::forward<F>(f));
}

template <typename Container, typename F>
inline bool EveryBy(Container&& c, F&& f) {
    bool ok = true;

    type_utility::VisitContainer(std::forward<Container>(c), std::forward<F>(f), [&ok](auto&& x) {
        ok = x;
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

    type_utility::VisitContainer(std::forward<Container>(c), std::forward<F>(f), [&ok](auto&& x) {
        ok = x;
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

#endif  // LODASH_SLICE_H
