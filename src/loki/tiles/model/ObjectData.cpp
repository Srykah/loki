/*!
 * \file ObjectData.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "ObjectData.hpp"

namespace loki::tiles {

ObjectData loadObjectData(const nlohmann::json& jsonDatum) {
  if (jsonDatum.contains("gid")) {
    PropertyMap properties;
    if (jsonDatum.contains("properties")) {
      loadPropertyMap(properties, jsonDatum.at("properties"));
    }
    return TileObjectData {
        jsonDatum.at("gid").get<int>(),
        jsonDatum.at("name").get<std::string>(),
        jsonDatum.at("type").get<std::string>(),
        sf::Vector2f {
            jsonDatum.at("x").get<float>(),
            jsonDatum.at("y").get<float>(),
        },
        std::move(properties),
    };
  } else if (jsonDatum.value<bool>("ellipse", false)) {
    return EllipseObjectData {
        sf::FloatRect {
            jsonDatum.at("x").get<float>(),
            jsonDatum.at("y").get<float>(),
            jsonDatum.at("width").get<float>(),
            jsonDatum.at("height").get<float>(),
        },
        jsonDatum.value("rotation", 0.f),
    };
  } else if (jsonDatum.value<bool>("point", false)) {
    return PointObjectData {
        jsonDatum.at("x").get<float>(),
        jsonDatum.at("y").get<float>(),
    };
  } else if (jsonDatum.contains("polygon")) {
    PolygonObjectData polygonObjectData;
    for (const auto& vertexData : std::as_const(jsonDatum.at("polygon"))) {
      polygonObjectData.vertices.emplace_back(vertexData.at("x").get<float>(), vertexData.at("y").get<float>());
    }
    return polygonObjectData;
  } else if (jsonDatum.contains("polyline")) {
    PolylineObjectData polylineObjectData;
    for (const auto& vertexData : std::as_const(jsonDatum.at("polyline"))) {
      polylineObjectData.vertices.emplace_back(vertexData.at("x").get<float>(), vertexData.at("y").get<float>());
    }
    return polylineObjectData;
  } else {
    return RectangleObjectData {
        sf::FloatRect {
            jsonDatum.at("x").get<float>(),
            jsonDatum.at("y").get<float>(),
            jsonDatum.at("width").get<float>(),
            jsonDatum.at("height").get<float>(),
        },
        jsonDatum.value("rotation", 0.f),
    };
  }
}

}