#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {

template <>
struct adl_serializer<sf::Keyboard::Key> {
 private:
  static constexpr std::pair<sf::Keyboard::Key, const char*> KEY_NAMES[] = {
#define LOKI_JSON_KEY_NAME(Key) {sf::Keyboard::Key, #Key}
      LOKI_JSON_KEY_NAME(Unknown),   LOKI_JSON_KEY_NAME(A),
      LOKI_JSON_KEY_NAME(B),         LOKI_JSON_KEY_NAME(C),
      LOKI_JSON_KEY_NAME(D),         LOKI_JSON_KEY_NAME(E),
      LOKI_JSON_KEY_NAME(F),         LOKI_JSON_KEY_NAME(G),
      LOKI_JSON_KEY_NAME(H),         LOKI_JSON_KEY_NAME(I),
      LOKI_JSON_KEY_NAME(J),         LOKI_JSON_KEY_NAME(K),
      LOKI_JSON_KEY_NAME(L),         LOKI_JSON_KEY_NAME(M),
      LOKI_JSON_KEY_NAME(N),         LOKI_JSON_KEY_NAME(O),
      LOKI_JSON_KEY_NAME(P),         LOKI_JSON_KEY_NAME(Q),
      LOKI_JSON_KEY_NAME(R),         LOKI_JSON_KEY_NAME(S),
      LOKI_JSON_KEY_NAME(T),         LOKI_JSON_KEY_NAME(U),
      LOKI_JSON_KEY_NAME(V),         LOKI_JSON_KEY_NAME(W),
      LOKI_JSON_KEY_NAME(X),         LOKI_JSON_KEY_NAME(Y),
      LOKI_JSON_KEY_NAME(Z),         LOKI_JSON_KEY_NAME(Num0),
      LOKI_JSON_KEY_NAME(Num1),      LOKI_JSON_KEY_NAME(Num2),
      LOKI_JSON_KEY_NAME(Num3),      LOKI_JSON_KEY_NAME(Num4),
      LOKI_JSON_KEY_NAME(Num5),      LOKI_JSON_KEY_NAME(Num6),
      LOKI_JSON_KEY_NAME(Num7),      LOKI_JSON_KEY_NAME(Num8),
      LOKI_JSON_KEY_NAME(Num9),      LOKI_JSON_KEY_NAME(Escape),
      LOKI_JSON_KEY_NAME(LControl),  LOKI_JSON_KEY_NAME(LShift),
      LOKI_JSON_KEY_NAME(LAlt),      LOKI_JSON_KEY_NAME(LSystem),
      LOKI_JSON_KEY_NAME(RControl),  LOKI_JSON_KEY_NAME(RShift),
      LOKI_JSON_KEY_NAME(RAlt),      LOKI_JSON_KEY_NAME(RSystem),
      LOKI_JSON_KEY_NAME(Menu),      LOKI_JSON_KEY_NAME(LBracket),
      LOKI_JSON_KEY_NAME(RBracket),  LOKI_JSON_KEY_NAME(Semicolon),
      LOKI_JSON_KEY_NAME(Comma),     LOKI_JSON_KEY_NAME(Period),
      LOKI_JSON_KEY_NAME(Quote),     LOKI_JSON_KEY_NAME(Slash),
      LOKI_JSON_KEY_NAME(Backslash), LOKI_JSON_KEY_NAME(Tilde),
      LOKI_JSON_KEY_NAME(Equal),     LOKI_JSON_KEY_NAME(Hyphen),
      LOKI_JSON_KEY_NAME(Space),     LOKI_JSON_KEY_NAME(Enter),
      LOKI_JSON_KEY_NAME(Backspace), LOKI_JSON_KEY_NAME(Tab),
      LOKI_JSON_KEY_NAME(PageUp),    LOKI_JSON_KEY_NAME(PageDown),
      LOKI_JSON_KEY_NAME(End),       LOKI_JSON_KEY_NAME(Home),
      LOKI_JSON_KEY_NAME(Insert),    LOKI_JSON_KEY_NAME(Delete),
      LOKI_JSON_KEY_NAME(Add),       LOKI_JSON_KEY_NAME(Subtract),
      LOKI_JSON_KEY_NAME(Multiply),  LOKI_JSON_KEY_NAME(Divide),
      LOKI_JSON_KEY_NAME(Left),      LOKI_JSON_KEY_NAME(Right),
      LOKI_JSON_KEY_NAME(Up),        LOKI_JSON_KEY_NAME(Down),
      LOKI_JSON_KEY_NAME(Numpad0),   LOKI_JSON_KEY_NAME(Numpad1),
      LOKI_JSON_KEY_NAME(Numpad2),   LOKI_JSON_KEY_NAME(Numpad3),
      LOKI_JSON_KEY_NAME(Numpad4),   LOKI_JSON_KEY_NAME(Numpad5),
      LOKI_JSON_KEY_NAME(Numpad6),   LOKI_JSON_KEY_NAME(Numpad7),
      LOKI_JSON_KEY_NAME(Numpad8),   LOKI_JSON_KEY_NAME(Numpad9),
      LOKI_JSON_KEY_NAME(F1),        LOKI_JSON_KEY_NAME(F2),
      LOKI_JSON_KEY_NAME(F3),        LOKI_JSON_KEY_NAME(F4),
      LOKI_JSON_KEY_NAME(F5),        LOKI_JSON_KEY_NAME(F6),
      LOKI_JSON_KEY_NAME(F7),        LOKI_JSON_KEY_NAME(F8),
      LOKI_JSON_KEY_NAME(F9),        LOKI_JSON_KEY_NAME(F10),
      LOKI_JSON_KEY_NAME(F11),       LOKI_JSON_KEY_NAME(F12),
      LOKI_JSON_KEY_NAME(F13),       LOKI_JSON_KEY_NAME(F14),
      LOKI_JSON_KEY_NAME(F15),       LOKI_JSON_KEY_NAME(Pause),
#undef LOKI_JSON_KEY_NAME
  };

 public:
  static void to_json(json& j, sf::Keyboard::Key key) {
    auto it = std::find_if(std::begin(KEY_NAMES), std::end(KEY_NAMES),
                           [key](const auto& p) { return p.first == key; });
    j = ((it != std::end(KEY_NAMES)) ? it : std::begin(KEY_NAMES))->second;
  }

  static void from_json(const json& j, sf::Keyboard::Key& key) {
    auto it = std::find_if(std::begin(KEY_NAMES), std::end(KEY_NAMES),
                           [&j](const auto& p) { return p.second == j; });
    key = ((it != std::end(KEY_NAMES)) ? it : std::begin(KEY_NAMES))->first;
  }
};

}  // namespace nlohmann
