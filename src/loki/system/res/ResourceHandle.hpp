#pragma once

#include <filesystem>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/utils/Memory.hpp>
#include <loki/system/res/Resource.hpp>

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

  void setPtr(core::BorrowerPtr<BaseResource>&& _ptr) { ptr = core::static_pointer_cast<Res>(_ptr); }
  const BaseResource* getPtr() const { return ptr.get(); }

 private:
  std::filesystem::path path;
  core::BorrowerPtr<Res> ptr;

  LOKI_REFLECTION_CLASS_DECLARE(ResourceHandle<Res>)
};

}  // namespace loki::system

LOKI_REFLECTION_TEMPLATE_CLASS_BEGIN(loki::system::ResourceHandle)
LOKI_REFLECTION_CLASS_FIELD(path)
LOKI_REFLECTION_CLASS_END()
