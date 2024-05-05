#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

#include <fmt/format.h>

namespace loki::core {

struct LangMetaData {
  std::string name;
  std::filesystem::path filepath;
};

using RegisteredLangs = std::map<std::string, LangMetaData>;

class I18nData {
 private:
  using LangData = std::map<std::string, std::string>;

 public:
  void loadFromFile(const std::filesystem::path& path);

  [[nodiscard]] const RegisteredLangs& getRegisteredLangs() const;

  bool setCurLang(std::string&& langId);

  bool setCurLang(std::string_view langId);

  [[nodiscard]] const LangMetaData& getCurLang() const;

  [[nodiscard]] const std::string& getCurLangId() const;

  [[nodiscard]] const std::string* get(std::string_view uri) const;

  // helper to get with formattable uri
  template <class... Args>
  [[nodiscard]] std::string get(std::string_view fmt, Args&&... fmtArgs) const;

 private:
  std::filesystem::path parentPath;
  RegisteredLangs registeredLangs;
  LangData currentLangData;
  std::string currentLangId;
};

}  // namespace loki::core

#include "I18nData.hxx"
