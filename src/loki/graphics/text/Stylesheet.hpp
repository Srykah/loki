#pragma once

#include <filesystem>
#include <string>

#include <nlohmann/json.hpp>

#include "AnimatedTextStyle.hpp"

namespace loki::gfx {

class Stylesheet {
 public:
  void setStyle(const std::string& styleName, const AnimatedTextStyle& style);
  void setDefaultStyle(const AnimatedTextStyle& defaultStyle);
  [[nodiscard]] const AnimatedTextStyle& getStyle(
      const std::string& styleName) const;
  [[nodiscard]] const AnimatedTextStyle& getDefaultStyle() const;

  [[nodiscard]] AnimatedTextStyle getNewStyleFromBase(
      AnimatedTextStyle base,
      const std::vector<std::string>& styleNames) const;

 private:
  std::map<std::string, AnimatedTextStyle> styles;
};

void from_json(const nlohmann::json& json, Stylesheet& ss);

}  // namespace loki::gfx
