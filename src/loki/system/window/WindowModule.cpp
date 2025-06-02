#include "WindowModule.hpp"

#include <SFML/Window/Event.hpp>

#include "loki/core/services/ServiceRegistry.hpp"
#include "loki/system/app/ApplicationInterface.hpp"

namespace loki::system {

const ::loki::system::BaseUpdateTraits& WindowModule::getUpdateTraits() const {
  static const ::loki::system::UpdateTraits<WindowModule> updateTraits;
  assert(updateTraits.hasUpdateStep(UpdateStep::InputPolling));
  return updateTraits;
}

void WindowModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void WindowModule::init() {
  window.create(windowSize, windowTitle, windowStyle);
  if (internalResolution != sf::Vector2f{})
    window.setInternalResolution(internalResolution);
  if (minimumSize != sf::Vector2f{})
    window.setMinimumSize(minimumSize);
}

void WindowModule::onInputPolling(sf::Time delta) {
  events.clear();
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      getService<ApplicationInterface>().exit();
    }
    events.push_back(std::move(event));
  }
}

void WindowModule::onPreRender(sf::Time delta) {
  window.clear();
}

void WindowModule::onPostRender(sf::Time delta) {
  window.display();
}

}  // namespace loki::system
