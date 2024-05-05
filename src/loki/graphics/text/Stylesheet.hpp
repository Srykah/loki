#pragma once

#include <filesystem>
#include <string>
#include "AnimatedTextStyle.hpp"

#if 0
#include <nlohmann/json.hpp>
#endif

namespace loki::graphics {

class Stylesheet {
 public:
  void setStyle(const std::string& styleName, const AnimatedTextStyle& style);
  void setDefaultStyle(const AnimatedTextStyle& defaultStyle);
  [[nodiscard]] const AnimatedTextStyle& getStyle(const std::string& styleName) const;
  [[nodiscard]] const AnimatedTextStyle& getDefaultStyle() const;

  [[nodiscard]] AnimatedTextStyle getNewStyleFromBase(AnimatedTextStyle base,
                                                      const std::vector<std::string>& styleNames) const;

 private:
  std::map<std::string, AnimatedTextStyle> styles;
};

#if 0
void from_json(const nlohmann::json& json, Stylesheet& ss);
#endif

}  // namespace loki::graphics
