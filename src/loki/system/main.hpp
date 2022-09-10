#if defined(LOKI_MAIN_HPP)
#error only include this file in a single source file in your project!
#else
#define LOKI_MAIN_HPP

#include <iostream>

#include <loki/system/app/Application.hpp>

extern std::unique_ptr<loki::system::Application> getApplication();

int main(int argc, char** argv) {
  try {
    auto app = getApplication();
    return app->run(argc, argv);
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
}

#endif  // defined(LOKIMON_MAIN_HPP)
