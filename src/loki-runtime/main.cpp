#include <print>

#include "Application.hpp"

int main() {
  try {
    loki::app::Application app;
    app.run();
    return 0;
  } catch (const std::exception& e) {
    std::println(stderr, "{}", e.what());
    return -1;
  }
}
