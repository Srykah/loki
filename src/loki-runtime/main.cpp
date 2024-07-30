#include <cstdlib>

#include "Application.hpp"

int main() {
  try {
    loki::app::Application app;
    app.run();
    return 0;
  } catch (const std::exception& e) {
    std::fprintf(stderr, e.what());
    return -1;
  }
}
