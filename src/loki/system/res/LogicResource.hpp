#pragma once

#include <fstream>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

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
  void loadImpl(const std::filesystem::path& path) override {
    std::fstream file{path};
    YAML::Node node = YAML::Load(file);
    core::fromYaml(node, static_cast<T*>(this), core::getTypeInfo<T>());
  }
};

}  // namespace loki::system

#define LOKI_LOGICRESOURCE_ADD_CHILD_TO_HOLDER(child) addChildResourceToHolder(resourceHolder, child);

#define LOKI_LOGICRESOURCE_ADD_CHILDREN_TO_HOLDER(...)                                    \
 private:                                                                                 \
  bool addChildResourcesToHolder(loki::system::ResourceHolder& resourceHolder) override { \
    LOKI_CORE_REPEAT(LOKI_LOGICRESOURCE_ADD_CHILD_TO_HOLDER, __VA_ARGS__)                 \
    return true;                                                                          \
  }
