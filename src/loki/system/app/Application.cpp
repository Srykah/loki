#include "Application.hpp"

namespace {
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
}

namespace loki::system {

void Application::registerServices() {
  serviceRegistry.registerService(runtimeObjectRegistry);
  serviceRegistry.registerService(componentRegistry);
  serviceRegistry.registerService(inputManager);
  serviceRegistry.registerService(resourceHolder);
  serviceRegistry.registerService(sceneManager);
  serviceRegistry.registerService(window);
}

Application::~Application() = default;

int Application::run(int argc, char** argv) {
  try {
    if (int errcode = parseArgs(argc, argv); errcode != 0) {
      return errcode;
    }
    init();
    loop();
  } catch (std::exception& e) {
    std::print(stderr, "{}", e.what());
  }
  return 0;
}

void Application::init() {
  registerServices();
}

void Application::loop() {
  sf::Clock clock;
  sf::Time timeSinceLastFrame;
  bool play = true;
  while (play) {
    timeSinceLastFrame += clock.restart();
    for (; timeSinceLastFrame >= TIME_PER_FRAME; timeSinceLastFrame -= TIME_PER_FRAME) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          play = false;
        }
      }
      resourceHolder.load();
      window.update(TIME_PER_FRAME);
      inputManager.update(TIME_PER_FRAME);
      sceneManager.update(TIME_PER_FRAME);
#if 0
      actorManager.update(TIME_PER_FRAME);
#endif
      window.clear(sf::Color::Black);
      sceneManager.draw(window);
      window.display();
    }
    sf::sleep((TIME_PER_FRAME - timeSinceLastFrame) / 2.f);
  }
  window.close();
}

}  // namespace loki::system
