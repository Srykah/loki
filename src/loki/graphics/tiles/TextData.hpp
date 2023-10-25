#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include <loki/core/json/Color.hpp>

namespace loki::gfx {

struct TextData {
  sf::Text::Style style = sf::Text::Style::Regular;
  sf::Color color = sf::Color::Black;
  std::string fontFamily = "sans-serif";
  unsigned int size = 16;
  std::string text = "";
  bool wrap = false;
  enum class HorizontalAlign { LEFT, CENTER, RIGHT, JUSTIFY } hAlign = HorizontalAlign::LEFT;
  enum class VerticalAlign {
    TOP,
    CENTER,
    BOTTOM,
  } vAlign = VerticalAlign::TOP;
};

NLOHMANN_JSON_SERIALIZE_ENUM(TextData::HorizontalAlign,
                             {
                                 {TextData::HorizontalAlign::LEFT, "left"},
                                 {TextData::HorizontalAlign::CENTER, "center"},
                                 {TextData::HorizontalAlign::RIGHT, "right"},
                                 {TextData::HorizontalAlign::JUSTIFY, "justify"},
                             })

NLOHMANN_JSON_SERIALIZE_ENUM(TextData::VerticalAlign,
                             {
                                 {TextData::VerticalAlign::TOP, "top"},
                                 {TextData::VerticalAlign::CENTER, "center"},
                                 {TextData::VerticalAlign::BOTTOM, "bottom"},
                             })

void from_json(const core::json& j, TextData& td);
void to_json(core::json& j, const TextData& td);

}  // namespace loki::gfx
