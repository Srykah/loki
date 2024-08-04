#include "WindowModule.hpp"

#include <SFML/Window/Event.hpp>

#include "loki/core/services/ServiceRegistry.hpp"
#include "loki/system/app/ApplicationInterface.hpp"

namespace loki::system {

void WindowModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void WindowModule::init() {
  window.create(windowSize, windowTitle, windowStyle);
  if (internalResolution != sf::Vector2u{})
    window.setInternalResolution(internalResolution);
  if (minimumSize != sf::Vector2u{})
    window.setMinimumSize(minimumSize);
}

void WindowModule::update(sf::Time delta) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      getService<ApplicationInterface>().exit();
    }
  }
}

void WindowModule::draw(const sf::Drawable& drawable) {
  window.clear();
  window.draw(drawable);
  window.display();
}

}  // namespace loki::system
