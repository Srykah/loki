#pragma once

namespace loki::core {
struct ClassAttribute {
  enum class Type { SerializeAsFlow, SerializeAsValue };

  virtual ~ClassAttribute() = default;
  virtual Type getType() const = 0;
};

struct SerializeAsFlow final : ClassAttribute {
  Type getType() const override { return Type::SerializeAsFlow; }
};

struct SerializeAsValue final : ClassAttribute {
  Type getType() const override { return Type::SerializeAsValue; }
};

}  // namespace loki::core