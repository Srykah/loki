#pragma once

#include <variant>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <nlohmann/json.hpp>

#include <loki/core/json/Rect.hpp>
#include <loki/core/json/Variant.hpp>
#include <loki/core/json/Vector2.hpp>

#include "Property.hpp"
#include "TextData.hpp"

namespace loki::gfx {

// TileObjectData

struct TileObjectData {
  int gid = -1;
  std::string name;
  std::string type;
  sf::Vector2f position;
  PropertyMap properties;
};

void from_json(const nlohmann::json& j, TileObjectData& tod);
void to_json(nlohmann::json& j, const TileObjectData& tod);

// EllipseObjectData

struct EllipseObjectData {
  sf::FloatRect rect;
  float rotation = 0.f;
};

void from_json(const nlohmann::json& j, EllipseObjectData& eod);
void to_json(nlohmann::json& j, const EllipseObjectData& eod);

// RectangleObjectData

struct RectangleObjectData {
  sf::FloatRect rect;
  float rotation = 0.f;
};

void from_json(const nlohmann::json& j, RectangleObjectData& rod);
void to_json(nlohmann::json& j, const RectangleObjectData& rod);

// PointObjectData

struct PointObjectData {
  std::string name;
  sf::Vector2f position;
};

void from_json(const nlohmann::json& j, PointObjectData& pod);
void to_json(nlohmann::json& j, const PointObjectData& pod);

// PolygonObjectData

struct PolygonObjectData {
  std::vector<sf::Vector2f> vertices;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PolygonObjectData, vertices);

// PolylineObjectData

struct PolylineObjectData {
  std::vector<sf::Vector2f> vertices;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PolylineObjectData, vertices);

// TextObjectData

struct TextObjectData {
  sf::FloatRect rect;
  TextData text;
};

void from_json(const nlohmann::json& j, TextObjectData& tod);
void to_json(nlohmann::json& j, const TextObjectData& tod);

// ObjectData

using ObjectData = std::variant<TileObjectData,
                                EllipseObjectData,
                                RectangleObjectData,
                                PointObjectData,
                                PolygonObjectData,
                                PolylineObjectData,
                                TextObjectData>;

}  // namespace loki::gfx

namespace nlohmann {

template <>
struct adl_serializer<loki::gfx::ObjectData> {
  static void from_json(const nlohmann::json& j, loki::gfx::ObjectData& od) {
    using loki::gfx::from_json;
    if (j.contains("gid")) {
      loki::gfx::TileObjectData tod;
      from_json(j, tod);
      od = std::move(tod);
    } else if (j.value<bool>("ellipse", false)) {
      loki::gfx::EllipseObjectData eod;
      from_json(j, eod);
      od = std::move(eod);
    } else if (j.value<bool>("point", false)) {
      loki::gfx::PointObjectData pod;
      from_json(j, pod);
      od = std::move(pod);
    } else if (j.contains("polygon")) {
      loki::gfx::PolygonObjectData pod;
      from_json(j, pod);
      od = std::move(pod);
    } else if (j.contains("polyline")) {
      loki::gfx::PolylineObjectData pod;
      from_json(j, pod);
      od = std::move(pod);
    } else if (j.contains("textbutton")) {
      loki::gfx::TextObjectData tod;
      from_json(j, tod);
      od = std::move(tod);
    } else {
      loki::gfx::RectangleObjectData rod;
      from_json(j, rod);
      od = std::move(rod);
    }
  }

  static void to_json(nlohmann::json& j, const loki::gfx::ObjectData& od) {
    std::visit([&](const auto& data) { to_json(j, data); }, od);
    /*
    // PS : I tried using visit and failed miserably, maybe try again sometime
    using loki::gfx::to_json;
#define LOKI_TILES_OBJECTDATA_TEST(type)                           \
  if (std::holds_alternative<loki::gfx::type##ObjectData>(od)) { \
    to_json(j, std::get<loki::gfx::type##ObjectData>(od));       \
  } else
    LOKI_TILES_OBJECTDATA_TEST(Tile)
    LOKI_TILES_OBJECTDATA_TEST(Ellipse)
    LOKI_TILES_OBJECTDATA_TEST(Point)
    LOKI_TILES_OBJECTDATA_TEST(Polygon)
    LOKI_TILES_OBJECTDATA_TEST(Polyline)
    LOKI_TILES_OBJECTDATA_TEST(Text)
    LOKI_TILES_OBJECTDATA_TEST(Rectangle);
    */
  }
};

}  // namespace nlohmann
