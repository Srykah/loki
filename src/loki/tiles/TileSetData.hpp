#pragma once

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/system/res/LogicResource.hpp>

namespace loki::tiles {

struct TileSetAttribute : public core::BaseObject {
 public:
  virtual void addChildResourcesToHolder(system::ResourceHolder& holder, system::ResourceListener& listener) {}
  LOKI_REFLECTION_CLASS_DECLARE_RTTI(TileSetAttribute)
};

struct SizeTileSetAttribute : public TileSetAttribute {
  sf::Vector2f tileSize;
  LOKI_REFLECTION_CLASS_DECLARE_RTTI(SizeTileSetAttribute)
};

struct TileAttribute : public core::BaseObject {
 public:
  virtual void addChildResourcesToHolder(system::ResourceHolder& holder, system::ResourceListener& listener) {}
  LOKI_REFLECTION_CLASS_DECLARE_RTTI(TileAttribute)
};

struct TileSetData {
  std::vector<std::unique_ptr<TileSetAttribute>> tileSetAttributes;
  std::vector<std::vector<std::unique_ptr<TileAttribute>>> tilesAttributes;

  template <class T>
  const T* getTileSetAttribute() const {
    const auto& classId = std::get<core::ClassInfo>(core::getTypeInfo<T>().info).id;
    for (const auto& tileSetAttr : tileSetAttributes) {
      if (std::get<core::ClassInfo>(tileSetAttr->getClassTypeInfo().info).id == classId)
        return static_cast<const T*>(tileSetAttr.get());
    }
    return nullptr;
  }

  template <class T>
  const T* getTileAttribute(std::size_t tileIndex) const {
    if (tileIndex >= tilesAttributes.size())
      return nullptr;
    const auto& classId = std::get<core::ClassInfo>(core::getTypeInfo<T>().info).id;
    for (const auto& tileSetAttr : tilesAttributes.at(tileIndex)) {
      if (std::get<core::ClassInfo>(tileSetAttr->getClassTypeInfo().info).id == classId)
        return static_cast<const T*>(tileSetAttr.get());
    }
    return nullptr;
  }
};

struct TileSetDataResource : public system::LogicResource<TileSetData> {
 private:
  bool addChildResourcesToHolder(system::ResourceHolder& resourceHolder) override {
    for (auto& tileSetAttr : tileSetAttributes) {
      tileSetAttr->addChildResourcesToHolder(resourceHolder, *this);
    }
    for (auto& tileAttrList : tilesAttributes) {
      for (auto& tileAttr : tileAttrList) {
        tileAttr->addChildResourcesToHolder(resourceHolder, *this);
      }
    }
    return true;
  }
};

}  // namespace loki::tiles

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::tiles::TileSetAttribute)
LOKI_REFLECTION_CLASS_END_RTTI(loki::tiles::TileSetAttribute)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::tiles::TileSetAttribute, loki::tiles::SizeTileSetAttribute)
LOKI_REFLECTION_CLASS_FIELD(loki::tiles::SizeTileSetAttribute, tileSize)
LOKI_REFLECTION_CLASS_END_RTTI(loki::tiles::SizeTileSetAttribute)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::tiles::TileAttribute)
LOKI_REFLECTION_CLASS_END_RTTI(loki::tiles::TileAttribute)

LOKI_REFLECTION_CLASS_BEGIN(loki::tiles::TileSetData)
LOKI_REFLECTION_CLASS_FIELD(loki::tiles::TileSetData, tileSetAttributes)
LOKI_REFLECTION_CLASS_FIELD(loki::tiles::TileSetData, tilesAttributes)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(loki::tiles::TileSetDataResource)
LOKI_REFLECTION_CLASS_END()