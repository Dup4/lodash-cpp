#ifndef LODASH_TYPE_MANIPULATION_H
#define LODASH_TYPE_MANIPULATION_H

namespace lodash {

template <typename T>
T Empty() {
    return T{};
}

template <typename T>
bool IsEmpty(T&& t) {
    return t == Empty<T>();
}

template <typename T>
bool IsNotEmpty(T&& t) {
    return !IsEmpty(t);
}

}  // namespace lodash

#endif  // LODASH_TYPE_MANIPULATION_H
