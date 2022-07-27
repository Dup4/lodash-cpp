#ifndef LODASH_TYPE_UTILITY_REDUCE_HANDLER_H
#define LODASH_TYPE_UTILITY_REDUCE_HANDLER_H

#include <type_traits>

namespace lodash::type_utility {

template <typename F, typename T>
class ReduceHandler {
public:
    ReduceHandler(F&& f, T&& t) : f_(f), t_(t) {}

    template <typename... Args,
              std::enable_if_t<std::is_void_v<std::void_t<std::result_of_t<F(std::decay_t<T>, Args...)>>>, bool> = true>
    auto operator()(Args&&... args) {
        t_ = f_(t_, args...);
    }

    T&& GetRes() {
        return std::move(t_);
    }

private:
    F f_;
    T t_;
};

}  // namespace lodash::type_utility

#endif  // LODASH_TYPE_UTILITY_REDUCE_HANDLER_H
