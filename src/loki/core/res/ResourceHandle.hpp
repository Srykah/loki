/*!
* \file ResourceHandle.hpp
* \author Srykah
* \copyright GNU GPL v3.0
*/
#pragma once

#include <loki/core/json/Macros.hpp>
#include <loki/core/json/Path.hpp>

namespace loki::res {

template <class Res>
class ResourceHandle {
 public:
  ResourceHandle() = default;

  explicit ResourceHandle(std::filesystem::path path) : path(std::move(path)) {}

  const typename Res::DataType& operator*() const {
    return getData();
  }

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
  BorrowerPtr<Res> ptr;

  friend class ResourceHolder;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(ResourceHandle, path)
};

}  // namespace loki::res