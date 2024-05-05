#pragma once

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/utils/Memory.hpp>

namespace loki::system {

template <class Res>
class ResourceHandle {
 public:
  ResourceHandle() = default;

  const typename Res::DataType& operator*() const { return getData(); }
  const typename Res::DataType* operator->() const { return &getData(); }

  [[nodiscard]] const std::filesystem::path& getPath() const { return path; }

  const typename Res::DataType& getData() const {
    if (!ptr) {
      throw std::runtime_error("ResourceHandle handles no resource");
    }
    return ptr->getData();
  }

 private:
  std::filesystem::path path;
  core::BorrowerPtr<Res> ptr;

  friend class ResourceHolder;

  LOKI_REFLECTION_CLASS_DECLARE(ResourceHandle<Res>)
};

}  // namespace loki::system

LOKI_REFLECTION_TEMPLATE_CLASS_BEGIN(loki::system::ResourceHandle)
LOKI_REFLECTION_TEMPLATE_CLASS_FIELD(loki::system::ResourceHandle, path)
LOKI_REFLECTION_TEMPLATE_CLASS_END()