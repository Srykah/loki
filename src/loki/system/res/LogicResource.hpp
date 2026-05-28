#pragma once

#include <fstream>

#include <ryml.hpp>

#include <loki/core/serialization/yaml/fromYaml.hpp>
#include <loki/core/utils/Macros.hpp>
#include <loki/system/res/Resource.hpp>
#include <loki/system/res/ResourceHolder.hpp>

namespace loki::system {

template <class T>
class LogicResource : public Resource<T>, public T {
 public:
  const T& getData() const override { return static_cast<const T&>(*this); }

 protected:
  bool load(const std::filesystem::path& path) override {
    ryml::Tree tree;
    {
      std::fstream file{path};
      std::string fileContents{std::istreambuf_iterator(file), std::istreambuf_iterator<char>()};
      tree = ryml::parse_in_arena(fileContents.c_str());
    }
    core::fromYaml(tree, static_cast<T*>(this), core::getTypeInfo<T>());
    return true;
  }
};

}  // namespace loki::system

#define LOKI_LOGICRESOURCE_ADD_CHILD_TO_HOLDER(child) resourceHolder.add(child, this);

#define LOKI_LOGICRESOURCE_ADD_CHILDREN_TO_HOLDER(...)                                    \
 private:                                                                                 \
  bool addChildResourcesToHolder(loki::system::ResourceHolder& resourceHolder) override { \
    LOKI_CORE_REPEAT(LOKI_LOGICRESOURCE_ADD_CHILD_TO_HOLDER, __VA_ARGS__)                 \
    return true;                                                                          \
  }
