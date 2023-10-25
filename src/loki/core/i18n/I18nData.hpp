#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include <loki/core/json/Json.hpp>
#include <loki/core/json/Path.hpp>
#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::core {

class I18nData {
 private:
  struct LangMetaData {
    std::string name;
    std::filesystem::path filepath;
  };

 public:
  using RegisteredLangs = std::map<std::string, LangMetaData>;
  using Ptr = nlohmann::json_pointer<core::json>;

 public:
  void loadFromFile(const std::filesystem::path& path);

  [[nodiscard]] const RegisteredLangs& getRegisteredLangs() const;

  bool setCurLang(std::string&& langId);

  bool setCurLang(const std::string& langId);

  [[nodiscard]] const core::json& getCurLang() const;

  [[nodiscard]] const std::string& getCurLangId() const;

  [[nodiscard]] std::string get(const Ptr& ptr) const;

  template <class... Args>
  [[nodiscard]] std::string get(const std::string& uri, Args&&... args) const;

 private:
  std::filesystem::path parentPath;
  RegisteredLangs registeredLangs;
  core::json currentLangData;
  std::string currentLangId;

  friend const ::loki::core::TypeInfo* ::loki::core::getTypeInfo<LangMetaData>();
};

}  // namespace loki::core

#include "I18nData.hxx"
