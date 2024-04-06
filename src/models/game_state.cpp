#include <algorithm>

#include "game_state.h"

namespace mortido::models {

namespace {
std::vector<Point> parse_points(const rapidjson::Value &val) {
  std::vector<Point> points;
  for (const auto &pos : val.GetArray()) {
    points.push_back({pos[0].GetInt(), pos[1].GetInt()});
  }
  return points;
}

void set_garbage(std::vector<Garbage> &items, const rapidjson::Value &new_values) {
  items.clear();
  if (!new_values.IsNull()) {
    for (auto &m : new_values.GetObject()) {
      items.emplace_back(m.name.GetString(), parse_points(m.value));
    }
    std::sort(items.begin(), items.end());
  }
}
}

void GameState::update_on_travel(const std::string &from,
                                 const std::string &to,
                                 const rapidjson::Document &json_state) {
  ship.fuelUsed += json_state["fuelDiff"].GetInt();
  ship.planet = to;
  // TODO: compare garbage with prev planet.
  for (const auto &edge : json_state["planetDiffs"].GetArray()) {
    map.update_edge(edge["from"].GetString(), edge["to"].GetString(), edge["fuel"].GetInt());
  }

  ship.cargo->clear();
  if (!json_state["shipGarbage"].IsNull()) {
    for (auto &m : json_state["shipGarbage"].GetObject()) {
      ship.cargo->emplace(Garbage(m.name.GetString(), parse_points(m.value)));
    }
  }
  set_garbage(map.planets[to].items, json_state["planetGarbage"]);
}

GameState GameState::from_universe_json(const rapidjson::Document &json_state) {
  GameState state;

  const auto &shipJson = json_state["ship"];

  state.ship.cargo = std::make_unique<Cargo>(shipJson["capacityX"].GetInt(), shipJson["capacityY"].GetInt());
  state.ship.fuelUsed = shipJson["fuelUsed"].GetInt();

  if (!shipJson["garbage"].IsNull()) {
    for (auto &m : shipJson["garbage"].GetObject()) {
      state.ship.cargo->emplace(Garbage(m.name.GetString(), parse_points(m.value)));
    }
  }

  const auto &planet = shipJson["planet"];
  state.ship.planet = planet["name"].GetString();
  set_garbage(state.map.planets[state.ship.planet].items, planet["garbage"]);

  for (const auto &trip : json_state["universe"].GetArray()) {
    std::string from = trip[0].GetString();
    std::string to = trip[1].GetString();

    state.map.planets[from].name = from;
    state.map.planets[to].name = to;
    int distance = trip[2].GetInt();
    state.map.add_edge(from, to, distance);
  }

  return state;
}

}
