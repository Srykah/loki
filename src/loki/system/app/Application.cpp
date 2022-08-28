#include "Application.hpp"

namespace {
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
}

namespace loki::system {

int Application::run(int argc, char** argv) {
  if (int errcode = parseArgs(argc, argv); errcode != 0) {
    return errcode;
  }
  init();
  loop();
  return 0;
}

void Application::loop() {
  sf::Clock clock;
  sf::Time timeSinceLastFrame;
  bool play = true;
  while (play) {
    timeSinceLastFrame += clock.restart();
    for (; timeSinceLastFrame >= TIME_PER_FRAME;
         timeSinceLastFrame -= TIME_PER_FRAME) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          play = false;
        }
      }
      eventHandler.update(TIME_PER_FRAME);
      actorManager.update(TIME_PER_FRAME);
      window.clear(sf::Color::Black);

      window.display();
    }
    sf::sleep((TIME_PER_FRAME - timeSinceLastFrame) / 2.f);
  }
}

}  // namespace loki::system