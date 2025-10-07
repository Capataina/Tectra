#include "common/time.hpp"
#include <chrono>
#include <iostream>
#include <thread>

using namespace tectra::common;

int main() {
  std::cout << "Tectra v0.1.0 - Clock Abstraction Test\n\n";

  std::cout << "=== RealClock Test ===\n";
  RealClock real_clock;

  auto t1 = real_clock.now();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  auto t2 = real_clock.now();

  auto delta_ns = t2 - t1;
  auto delta_ms = delta_ns / 1'000'000;

  std::cout << "Time elapsed: " << delta_ms << " ms\n";
  std::cout << "Is virtual: " << (real_clock.is_virtual() ? "yes" : "no")
            << "\n\n";

  std::cout << "=== VirtualClock Test ===\n";
  VirtualClock virtual_clock(0);

  std::cout << "Initial time: " << virtual_clock.now() << " ns\n";

  virtual_clock.advance(1'000'000'000);
  std::cout << "After advance(1s): " << virtual_clock.now() << " ns\n";

  virtual_clock.set_time(5'000'000'000);
  std::cout << "After set_time(5s): " << virtual_clock.now() << " ns\n";
  std::cout << "Is virtual: " << (virtual_clock.is_virtual() ? "yes" : "no")
            << "\n";

  return 0;
}
