#pragma once

#include <string>
#include <vector>

#include <rapidjson/document.h>

#include "../logger.h"
#include "ship.h"
#include "map.h"

namespace mortido::models {

struct GameState {
  Ship ship;
  UniverseGraph map;

  static GameState from_universe_json(const rapidjson::Document &json_state);
  void update_planet_garbage(const std::string &planet, const rapidjson::Value &garbage);
  void update_on_travel(const std::string &from, const std::string &to, const rapidjson::Document &json_state);
};

}
