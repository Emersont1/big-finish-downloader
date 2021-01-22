#pragma once

#include <mutex>
#include <queue>

namespace utils {
template <typename T>
class atomic_queue : protected std::queue<T, std::deque<T>> {
    std::mutex mutex;

  public:
    atomic_queue() = default;

    T pop() {
        std::scoped_lock lock(mutex);

        T value = std::queue<T>::front();
        std::queue<T>::pop();
        return value;
    }

    void push(T value) {
        std::scoped_lock lock(mutex);

        std::queue<T>::push(value);
    }

    size_t size() {
        std::scoped_lock lock(mutex);

        return std::queue<T>::size();
    }

    // Gets a list of elements (at present)
    std::vector<T> elements() {
        std::scoped_lock lock(mutex);
        std::vector<T> elements;
        std::copy(std::queue<T>::c.begin(), std::queue<T>::c.end(), std::back_inserter(elements));

        return elements;
    }
};
} // namespace utils