#pragma once

#if 0

#include <cassert>

#include <loki/core/reflection/TypeInfo.hpp>
#include <loki/core/reflection/reflectionUtils.hpp>

#include "Component.hpp"

namespace loki::system {

class Actor;

/// @note Will get invalidated if the number of components of the actor changes
struct ComponentSlot {
  explicit ComponentSlot(Actor& actor);
  explicit ComponentSlot(Actor& actor, std::size_t index) : actor(actor), index(index) {}

  [[nodiscard]] Component*& get();
  [[nodiscard]] const Component* get() const;

  void destroy();

  Actor& actor;
  std::size_t index = -1;
};

}

namespace loki::core {

template <>
struct TypeInfoHolder<system::ComponentSlot> {
  static const TypeInfo& getTypeInfo_internal() {
    static TypeInfo PTR_INFO{
        .factory = [](void* ctx, TmpObj::Ownership ownership) -> TmpObj {
          assert(ownership != TmpObj::Ownership::NonOwned);
          return TmpObj::makeOwned<system::ComponentSlot>(to<system::Actor>(ctx));
        },
        .info =
            PtrInfo{.innerType = getTypeInfo<system::Component>(),
                    .getter = [](void* obj) -> TmpObj { return TmpObj::fromPtrNonOwned(to<system::ComponentSlot>(obj).get()); },
                    .getterConst = [](const void* obj) -> ConstTmpObj {
                      return ConstTmpObj::fromPtrNonOwned(to<system::ComponentSlot>(obj).get());
                    },
                    .setter =
                        [](void* obj, void* ptr) {
                          system::Component*& curComp = to<system::ComponentSlot>(obj).get();
                          system::Component* newComp = static_cast<system::Component*>(ptr);
                          if (curComp == newComp)
                            return;  // nothing to do!
                          curComp->destroy();
                          curComp = newComp;
                        },
                    .emplacer = [](void* obj) -> TmpObj {
                      assert(false && "Not implemented!");
                      return {};
                    },
                    .clear = [](void* obj) { to<system::ComponentSlot>(obj).destroy(); }},
    };
    return PTR_INFO;
  }
};
}

#endif