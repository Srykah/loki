#include <format>

#include "Application.hpp"

int main() {
  try {
    loki::app::Application app;
    app.run();
    return 0;
  } catch (const std::exception& e) {
    std::cerr << std::format("An exception occurred: {}. This is terrible!!! :-((((\n", e.what());
    return -1;
  }
}
