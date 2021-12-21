/*!
 * \file LayerView.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include "MapView.hpp"
namespace loki::tiles {

class LayerView : public sf::Drawable {
 public:
  LayerView(const MapView& parent) : parent(parent) {}

  virtual void update(const sf::Time& delta) = 0;

 protected:
  sf::Transform getParentTransform() const { return parent.getTransform(); }

 private:
  const MapView& parent;
};

}  // namespace loki::tiles