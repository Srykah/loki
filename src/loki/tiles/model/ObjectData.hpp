/*!
 * \file ObjectData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <variant>
#include "Property.hpp"

namespace loki::tiles {

struct TileObjectData {
  int globalTileId;
  std::string name;
  std::string type;
  sf::Vector2f position;
  PropertyMap properties;
};
struct EllipseObjectData {
  sf::FloatRect rect;
  float rotation = 0.f;
};
struct RectangleObjectData {
  sf::FloatRect rect;
  float rotation = 0.f;
};
using PointObjectData = sf::Vector2f;
struct PolygonObjectData {
  std::vector<sf::Vector2f> vertices;
};
struct PolylineObjectData {
  std::vector<sf::Vector2f> vertices;
};
struct TextObjectData {
  sf::FloatRect rect;
  sf::Text::Style style = sf::Text::Style::Regular;
  sf::Color color = sf::Color::Black;
  std::string fontFamily = "sans-serif";
  unsigned int size = 16;
  std::string text = "";
  bool wrap = false;
  enum class HorizontalAlign {
    LEFT,
    CENTER,
    RIGHT,
    JUSTIFY
  } horizontalAlign = HorizontalAlign::LEFT;
  enum class VerticalAlign {
    TOP,
    CENTER,
    BOTTOM,
  } verticalAlign = VerticalAlign::TOP;
};
using ObjectData = std::variant<
    TileObjectData,
    EllipseObjectData,
    RectangleObjectData,
    PointObjectData,
    PolygonObjectData,
    PolylineObjectData,
    TextObjectData>;

ObjectData loadObjectData(const nlohmann::json& jsonDatum);

}
