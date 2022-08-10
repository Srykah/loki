/*!
 * \file LangData.cpp.cc
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "LangData.hpp"

namespace loki::i18n {

LangData::LangData(std::filesystem::path path)
    : res::JsonResource<LangData>(std::move(path)) {}

const std::string& LangData::get(const LangData::Path& path) const {
  const Node* node = &root;
  for (const auto& part : path) {
    if (!std::holds_alternative<Node::BranchPtr>(node->content)) {
      throw std::runtime_error("LangData::get : Invalid path");
    }
    node = &std::get<Node::BranchPtr>(node->content)->at(part);
  }
  if (!std::holds_alternative<Node::Leaf>(node->content)) {
    throw std::runtime_error("LangData::get : Invalid path");
  }
  return std::get<Node::Leaf>(node->content);
}

void from_json(const nlohmann::json& j, LangData::Node& n) {
  if (j.is_string()) {
    n.content = j.get<std::string>();
  } else if (j.is_object()) {
    auto branch = std::make_unique<LangData::Node::Branch>();
    for (const auto& [name, value] : j.items()) {
      value.get_to((*branch)[name]);
    }
    n.content = std::move(branch);
  } else {
    throw std::runtime_error(
        "LangData::Node::from_json : Can't handle non-string or object data");
  }
}

void to_json(nlohmann::json& j, const LangData::Node& n) {
  // todo (or not)
}

void from_json(const nlohmann::json& j, LangData& ld) {
  j.at("/meta/lang"_json_pointer).get_to(ld.id);
  j.at("strings").get_to(ld.root);
}

void to_json(nlohmann::json& j, const LangData& ld) {
  // todo (or not)
}

}  // namespace loki::i18n
