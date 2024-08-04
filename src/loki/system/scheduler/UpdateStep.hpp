#pragma once

#include <cstdint>

#include <loki/core/utils/EnumAsBitField.hpp>

namespace loki::system {

enum class UpdateStep : std::uint64_t {
  InputPolling = 1 << 0,       // for the event polling of the Window
  InputReading = 1 << 1,       // for the InputModule & ImGuiModule
  PrePhysics = 1 << 2,         // for character controllers
  PhysicsSimulation = 1 << 3,  // for the PhysicsWorld
  PhysicsResult = 1 << 4,      // for the PhysicsBodies
  Default = 1 << 5,            // for pretty much everything
  PreRender = 1 << 6,          // for the clearing of the Window
  Render = 1 << 7,             // for the RendererModule
  EditorRender = 1 << 8,       // for the ImGuiModule
  PostRender = 1 << 9,         // for the display of the Window
};

LOKI_ENUM_AS_BITFIELD(UpdateStep)

}  // namespace loki::system
