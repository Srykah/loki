#include "Grid.hpp"

namespace loki::gui {

Grid::Grid(sf::Vector2u size) : items(size.x, size.y) {}

void Grid::setItem(sf::Vector2u coords, Widget::UPtr&& item) {
  items[{coords.x, coords.y}] = std::move(item);
}

void Grid::update(sf::Time delta) {}

}  // namespace loki::gui
