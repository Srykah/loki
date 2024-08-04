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

void WindowModule::update(UpdateStep updateStep, sf::Time delta) {
  if (updateStep == UpdateStep::InputPolling) {
    events.clear();
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        getService<ApplicationInterface>().exit();
      }
      events.push_back(std::move(event));
    }
  } else if (updateStep == UpdateStep::PreRender) {
    window.clear();
  } else if (updateStep == UpdateStep::PostRender) {
    window.display();
  }
}

}  // namespace loki::system
