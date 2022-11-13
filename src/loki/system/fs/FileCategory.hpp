#pragma once

namespace loki::system {

enum class FileCategory : int;

constexpr FileCategory FileCategory_Prefab{0};
constexpr FileCategory FileCategory_Scene{1};

constexpr FileCategory FileCategory_Client{63};  // feel free to add your own types after this one

}  // namespace loki::system