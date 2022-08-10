/*!
 * \file TextData.cpp.c
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TextData.hpp"

namespace loki::tiles {

namespace {

sf::Text::Style& operator|=(sf::Text::Style& s, sf::Text::Style other) {
  return s = static_cast<sf::Text::Style>(s | other);
}

}  // namespace

void from_json(const nlohmann::json& j, TextData& td) {
  if (j.at("bold").get<bool>()) {
    td.style |= sf::Text::Style::Bold;
  }
  if (j.at("italic").get<bool>()) {
    td.style |= sf::Text::Style::Italic;
  }
  if (j.at("underline").get<bool>()) {
    td.style |= sf::Text::Style::Underlined;
  }
  if (j.at("strikethrough").get<bool>()) {
    td.style |= sf::Text::Style::StrikeThrough;
  }
  j.at("color").get_to(td.color);
  j.at("fontfamily").get_to(td.fontFamily);
  j.at("size").get_to(td.size);
  j.at("textbutton").get_to(td.text);
  j.at("wrap").get_to(td.wrap);
  j.at("halign").get_to(td.hAlign);
  j.at("valign").get_to(td.vAlign);
}

void to_json(nlohmann::json& j, const TextData& td) {
  j["bold"] = bool(td.style & sf::Text::Style::Bold);
  j["italic"] = bool(td.style & sf::Text::Style::Italic);
  j["underline"] = bool(td.style & sf::Text::Style::Underlined);
  j["strikethrough"] = bool(td.style & sf::Text::Style::StrikeThrough);
  j["color"] = td.color;
  j["fontfamily"] = td.fontFamily;
  j["size"] = td.size;
  j["textbutton"] = td.text;
  j["wrap"] = td.wrap;
  j["halign"] = td.hAlign;
  j["valign"] = td.vAlign;
}

}  // namespace loki::tiles
