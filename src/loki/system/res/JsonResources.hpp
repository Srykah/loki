#pragma once

#include "Resource.hpp"
#include "ResourceHolder.hpp"

namespace loki::system {

template <class T>
class JsonResource : public Resource {
 public:
  using DataType = T;

 public:
  explicit JsonResource(std::filesystem::path path) : Resource(std::move(path)) {}
  ~JsonResource() override = default;

  virtual void addChildResourcesToHolder(ResourceHolder& resourceHolder) = 0;

  void loadImpl(const std::filesystem::path& path, ResourceHolder& resourceHolder) override {
    std::ifstream fs{path};
    core::json j;
    fs >> j;
    j.get_to(static_cast<T&>(*this));
    this->addChildResourcesToHolder(resourceHolder);
  };

  void unloadImpl() override {
    // todo
  }

  const T& getData() const { return static_cast<const T&>(*this); }
};

}  // namespace loki::system

#define LOKI_RES_JSONRESOURCE_CTOR(Res) \
  explicit Res(std::filesystem::path p) : loki::system::JsonResource<Res>(std::move(p)) {}

#define LOKI_RES_JSONRESOURCE_CTOR_DTOR(Res) \
  LOKI_RES_JSONRESOURCE_CTOR(Res)            \
  ~Res() override = default;

#define LOKI_RES_JSONRESOURCE_ADD_CHILD_TO_HOLDER(child) resourceHolder.add(child);

#define LOKI_RES_JSONRESOURCE_ADD_CHILDREN_TO_HOLDER(...)                                 \
 private:                                                                                 \
  void addChildResourcesToHolder(loki::system::ResourceHolder& resourceHolder) override { \
    LOKI_CORE_REPEAT(LOKI_RES_JSONRESOURCE_ADD_CHILD_TO_HOLDER, __VA_ARGS__)              \
  }
