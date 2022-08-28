#pragma once

#include <filesystem>
#include <loki/system/res/JsonResources.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <variant>

namespace loki::core {

class LangData : public system::JsonResource<LangData> {
 private:
  struct Node {
    using Branch = std::unordered_map<std::string, Node>;
    using BranchPtr = std::unique_ptr<Branch>;
    using Leaf = std::string;

    std::variant<BranchPtr, Leaf> content;
  };

 public:
  using Path = std::vector<std::string>;

  explicit LangData(std::filesystem::path path);

  [[nodiscard]] const std::string& get(const Path& path) const;
  [[nodiscard]] const std::string& getId() const { return id; }

  LOKI_RES_JSONRESOURCE_ADD_CHILDREN_TO_HOLDER(0)

 private:
  std::string id;
  Node root;

  friend void from_json(const nlohmann::json& j, LangData& ld);
  friend void to_json(nlohmann::json& j, const LangData& ld);
  friend void from_json(const nlohmann::json& j, Node& n);
  friend void to_json(nlohmann::json& j, const Node& n);
};

}  // namespace loki::core
