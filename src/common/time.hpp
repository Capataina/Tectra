#pragma once

#include <chrono>
#include <cstdint>

namespace tectra::common {

using Timestamp = std::int64_t;

class Clock {
public:
  virtual ~Clock() = default;

  virtual Timestamp now() const = 0;

  virtual bool is_virtual() const = 0;
};

class RealClock final : public Clock {
public:
  Timestamp now() const override {
    auto now = std::chrono::steady_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration)
        .count();
  }

  bool is_virtual() const override { return false; }
};

class VirtualClock final : public Clock {
public:
  explicit VirtualClock(Timestamp start_time = 0) : current_time_(start_time) {}
  Timestamp now() const override { return current_time_; }
  bool is_virtual() const override { return true; }
  void advance(std::int64_t delta_ns) { current_time_ += delta_ns; }
  void set_time(Timestamp absolute_time) { current_time_ = absolute_time; }

private:
  Timestamp current_time_;
};

} // namespace tectra::common
