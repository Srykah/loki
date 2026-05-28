#include <format> // todo link with -lstdc++exp to allow println instead

#include "Application.hpp"

int main() {
  try {
    loki::app::Application app;
    app.run();
    return 0;
  } catch (const std::exception& e) {
    std::cerr << std::format("An exception occurred: {}\n", e.what());  // todo show callstack, cf <stacktrace>
    return -1;
  }
}
