/*!
 * \file ObjectLayerData.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <string>
#include <vector>
#include "ObjectData.hpp"

namespace loki::tiles {

struct ObjectLayerData {
  std::string name;
  std::vector<ObjectData> objects;
};

}

