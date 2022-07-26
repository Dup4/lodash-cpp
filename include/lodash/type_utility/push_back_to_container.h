#ifndef LODASH_TYPE_UTILITY_PUSH_BACK_TO_CONTAINER_H
#define LODASH_TYPE_UTILITY_PUSH_BACK_TO_CONTAINER_H

#include <string>
#include <type_traits>

#include "../type_check/is_map.h"

namespace lodash::type_utility {

template <typename Container, typename T>
inline void PushBackToContainer(Container&& c, T&& t) {
    if constexpr (type_check::is_map<std::decay_t<Container>>) {
        c.emplace(std::forward<T>(t));
    } else if constexpr (std::is_same_v<std::decay_t<Container>, std::string>) {
        c.push_back(t);
    } else {
        c.emplace_back(std::forward<T>(t));
    }
}

}  // namespace lodash::type_utility

#endif  // LODASH_TYPE_UTILITY_PUSH_BACK_TO_CONTAINER_H
