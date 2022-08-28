#include "InputType.hpp"

namespace {

std::map<std::string, sf::Mouse::Button> mouseButtonTable = {
    {"left", sf::Mouse::Left},     {"right", sf::Mouse::Right},
    {"middle", sf::Mouse::Middle}, {"x1", sf::Mouse::XButton1},
    {"x2", sf::Mouse::XButton2},
};

std::map<std::string, sf::Keyboard::Key> keyTable = {
    {"d", sf::Keyboard::D},
    {"q", sf::Keyboard::Q},
    {"s", sf::Keyboard::S},
    {"up", sf::Keyboard::Up},
    {"down", sf::Keyboard::Down},
    {"left", sf::Keyboard::Left},
    {"right", sf::Keyboard::Right},
    {"space", sf::Keyboard::Space},
    {
        "enter",
        sf::Keyboard::Enter,
    },
    {
        "backspace",
        sf::Keyboard::Backspace,
    },
};

std::map<std::string, sf::Joystick::Axis> axisTable = {
    {"x", sf::Joystick::X},       {"y", sf::Joystick::Y},
    {"z", sf::Joystick::Z},       {"r", sf::Joystick::R},
    {"u", sf::Joystick::U},       {"v", sf::Joystick::V},
    {"povx", sf::Joystick::PovX}, {"povy", sf::Joystick::PovY},
};

std::map<std::string, loki::system::JoystickAxisTrigger::Direction>
    directionTable = {
        {"positive", loki::system::JoystickAxisTrigger::Direction::POSITIVE},
        {"negative", loki::system::JoystickAxisTrigger::Direction::NEGATIVE},
        {"both", loki::system::JoystickAxisTrigger::Direction::BOTH},
};

}  // namespace

namespace loki::system {

InputTrigger loadTrigger(const nlohmann::json& triggerDatum) {
  const auto& triggerType = triggerDatum.at("type").get<std::string>();
  if (triggerType == "key") {
    const auto& id = triggerDatum.at("id").get<std::string>();
    return keyTable.at(id);
  } else if (triggerType == "mouseButton") {
    const auto& id = triggerDatum.at("id").get<std::string>();
    return mouseButtonTable.at(id);
  } else if (triggerType == "joystickButton") {
    return JoystickButtonTrigger{triggerDatum.at("id").get<unsigned int>()};
  } else if (triggerType == "axis") {
    const auto& axis = triggerDatum.at("axis").get<std::string>();
    const auto& direction = triggerDatum.at("direction").get<std::string>();
    return JoystickAxisTrigger{axisTable.at(axis),
                               directionTable.at(direction)};
  } else {
    throw std::runtime_error("invalid trigger type");
  }
}

}  // namespace loki::system