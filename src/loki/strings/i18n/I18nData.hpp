/*!
 * \file LangList.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <fmt/format.h>
#include <filesystem>
#include <loki/core/json/Path.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace loki::i18n {

class I18nData {
 private:
  struct LangMetaData {
    std::string name;
    std::filesystem::path filepath;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LangMetaData, name, filepath)
  };

 public:
  using RegisteredLangs = std::map<std::string, LangMetaData>;
  using Ptr = nlohmann::json_pointer<nlohmann::json>;

 public:
  void loadFromFile(const std::filesystem::path& path);

  [[nodiscard]] const RegisteredLangs& getRegisteredLangs() const;

  bool setCurLang(std::string&& langId);

  bool setCurLang(const std::string& langId);

  [[nodiscard]] const nlohmann::json& getCurLang() const;

  [[nodiscard]] const std::string& getCurLangId() const;

  [[nodiscard]] std::string get(const Ptr& ptr) const;

  template <class... Args>
  [[nodiscard]] std::string get(const std::string& uri, Args&&... args) const;

 private:
  std::filesystem::path parentPath;
  RegisteredLangs registeredLangs;
  nlohmann::json currentLangData;
  std::string currentLangId;
};

}  // namespace loki::i18n

#include "impl/I18nData.hxx"
