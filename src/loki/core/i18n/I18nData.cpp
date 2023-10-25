#include "I18nData.hpp"

#include <fstream>

#include <loki/core/serialization/ReflectToJson.hpp>

namespace loki::core {

const I18nData::RegisteredLangs& I18nData::getRegisteredLangs() const {
  return registeredLangs;
}

bool I18nData::setCurLang(std::string&& langId) {
  std::ifstream file(parentPath / registeredLangs.at(langId).filepath);
  core::json fileContents;
  file >> fileContents;
  currentLangData = std::move(fileContents.at("strings"));
  currentLangId = std::move(langId);
  return true;
}

bool I18nData::setCurLang(const std::string& langId) {
  return setCurLang(std::string{langId});
}

const core::json& I18nData::getCurLang() const {
  return currentLangData;
}

const std::string& I18nData::getCurLangId() const {
  return currentLangId;
}

void I18nData::loadFromFile(const std::filesystem::path& path) {
  std::ifstream file(path);
  core::json data;
  file >> data;
  data.at("langs").get_to(registeredLangs);
  parentPath = path.parent_path();
}

std::string I18nData::get(const I18nData::Ptr& ptr) const {
  return currentLangData.at(ptr);
}

}  // namespace loki::core
