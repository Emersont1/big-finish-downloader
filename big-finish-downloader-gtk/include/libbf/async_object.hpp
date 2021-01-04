#pragma once
#include <functional>
#include <future>
#include <memory>
#include <thread>

namespace libbf {
template <typename T> class async_getter {
  T           object;
  std::thread internal_thread;
  bool        started, is_ready, was_ready;

public:
  async_getter() : started(false), is_ready(false), was_ready(false){};

  void begin(std::function<T()> getter) {
    started = true;
    is_ready = false;
    was_ready = false;

    auto f = [](async_getter<T> * obj, std::function<T()> getter) -> void {
      obj->object = getter();
      obj->is_ready = true;
    };
    internal_thread = std::move(std::thread(f, this, getter));
  }

  ~async_getter() {
    if (internal_thread.joinable())
      internal_thread.join();
  }

  void update() {
    if (is_ready && internal_thread.joinable())
      internal_thread.join();
    was_ready = is_ready;
  }

  bool complete_trigger() {     if (is_ready && internal_thread.joinable())
      internal_thread.join();return is_ready && !was_ready; }

  // returns true if ready
  bool ready() { return is_ready; }
  bool active() {
    return started;
    ;
  }

  T * operator->() { return &object; }
  T & operator* () { return object; }
};
} // namespace libbf