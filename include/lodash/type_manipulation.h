#ifndef LODASH_TYPE_MANIPULATION_H
#define LODASH_TYPE_MANIPULATION_H

namespace lodash {

template <typename T>
inline T Empty() {
    return T{};
}

template <typename T>
inline bool IsEmpty(T&& t) {
    return t == Empty<T>();
}

template <typename T>
inline bool IsNotEmpty(T&& t) {
    return !IsEmpty(t);
}

}  // namespace lodash

#endif  // LODASH_TYPE_MANIPULATION_H
