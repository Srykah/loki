#include "I18nData.hpp"

#include <fstream>

namespace loki::core {

const RegisteredLangs& I18nData::getRegisteredLangs() const {
  return registeredLangs;
}

bool I18nData::setCurLang(std::string&& langId) {
#if 0
  std::ifstream file(parentPath / registeredLangs.at(langId).filepath);
  nlohmann::json fileContents;
  file >> fileContents;
  currentLangData = std::move(fileContents.at("strings"));
  currentLangId = std::move(langId);
#endif
  return true;
}

bool I18nData::setCurLang(std::string_view langId) {
  return setCurLang(std::string{langId});
}

const I18nData::LangData& I18nData::getCurLang() const {
  return currentLangData;
}

const std::string& I18nData::getCurLangId() const {
  return currentLangId;
}

void I18nData::loadFromFile(const std::filesystem::path& path) {
#if 0
  std::ifstream file(path);
  nlohmann::json data;
  file >> data;
  data.at("langs").get_to(registeredLangs);
  parentPath = path.parent_path();
#endif
}

const std::string* I18nData::get(std::string_view uri) const {
  if (!currentLangData.contains(uri))
    return nullptr;
  return &currentLangData.at(uri);
}

}  // namespace loki::core
