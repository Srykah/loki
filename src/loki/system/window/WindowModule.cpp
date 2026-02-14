#include "WindowModule.hpp"

#include <SFML/Window/Event.hpp>

#include "loki/core/services/ServiceRegistry.hpp"
#include "loki/system/app/ApplicationInterface.hpp"

namespace loki::system {

const BaseUpdateTraits& WindowModule::getUpdateTraits() const {
  static const UpdateTraits<WindowModule> updateTraits;
  assert(updateTraits.hasUpdateStep(UpdateStep::InputPolling));
  return updateTraits;
}

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

void WindowModule::onInputPolling(sf::Time delta) {
  events.clear();
  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      getService<ApplicationInterface>().exit();
    }
    events.push_back(std::move(*event));
  }
}

void WindowModule::onPreRender(sf::Time delta) {
  window.clear();
}

void WindowModule::onPostRender(sf::Time delta) {
  window.display();
}

}  // namespace loki::system
