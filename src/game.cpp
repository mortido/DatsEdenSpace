#include <cmath>
#include <chrono>
#include <thread>

#include "game.h"
#include "models/garbage.h"

namespace mortido::game {

using namespace std::chrono_literals;

void Game::load() {
  LOG_INFO("Game loading...");
  auto json_state = api_.universe().value();
  team_name_ = json_state["name"].GetString();
  state_ = models::GameState::from_universe_json(json_state);
  state_.map.planets[home_].was_cleared = true;
  state_.map.planets[home_].can_have_items = false;
  state_.map.planets[garbage_collector_].was_cleared = true;
  state_.map.planets[garbage_collector_].can_have_items = false;
  LOG_INFO("Game loaded, team: %s", team_name_.c_str());
  LOG_INFO("Ship at '%s' fuel %d",
           state_.ship.planet.c_str(),
           state_.ship.fuelUsed);

  min_load_ = static_cast<int>(std::ceil(static_cast<double>(state_.ship.cargo->capacity()) * 0.3));
  min_load_on_planet_ = static_cast<int>(std::ceil(static_cast<double>(state_.ship.cargo->capacity()) * 0.05));
  LOG_INFO("Capacity: %d; Min load: %d; Min load on planet: %d",
           state_.ship.cargo->capacity(),
           min_load_,
           min_load_on_planet_);
  LOG_INFO("Planets in universe %zu", state_.map.planets.size());
}

bool Game::should_stop() {
  auto round = api_.get_current_round();
  if (round) {
    if (round.value() != id_) {
      LOG_INFO("Incorrect round (%s), stop game %s", round.value().c_str(), id_.c_str());
      return true;
    } else {
      LOG_INFO("Round active, continue game %s", id_.c_str());
      return false;
    }
  }
  LOG_INFO("No active round, continue game %s", id_.c_str());  // todo remove
  return false;
}

bool Game::play() {
  LOG_INFO("Game started, team: %s", team_name_.c_str());

  int collected = 0;
  while (true) {

    // move.
    std::string from = state_.ship.planet;
    std::vector<std::string> path;
    if (state_.ship.cargo->should_go_home()) {
      // go to eden.
      path = state_.map.find_path(from, garbage_collector_);
      state_.ship.planet = garbage_collector_;
    }

    // Find best planet to visit.
    auto path_to = state_.map.next_to_clean(state_.ship.planet);
    for (const auto &planet : path_to) {
      path.push_back(planet);
    }

    if (path.empty()) {
      if (state_.ship.cargo->filled()>0) {
        LOG_INFO("LAST TRIP TO EDEN!", id_.c_str());
        path = state_.map.find_path(from, garbage_collector_);
        auto travel_result = api_.travel(path);
        collected += state_.ship.cargo->items().size();
      }
      LOG_INFO("FINAL COLLECTED: %d", collected);
//      while (!(should_stop())) {
//        LOG_ERROR("WAITING GAME %s TO STOP", id_.c_str());
//        std::this_thread::sleep_for(60s);
//      }
      return false;
    }

//    if(state_.ship.cargo->filled() < (static_cast<double>(state_.ship.cargo->capacity()) * 0.9)) {
//      for (int i = 0; i < path.size(); i++) {
//        if (state_.map.planets[path[i]].can_have_items) {
//          path.resize(i + 1);
//        }
//      }
//    }

    if (std::find(path.begin(), path.end(), garbage_collector_) != path.end()) {
      collected += state_.ship.cargo->items().size();
      state_.ship.cargo->clear();
    }
    LOG_INFO("COLLECTED: %d", collected);

//    if (should_stop()) {
//      // check before api call.
//      return;
//    }
    auto travel_result = api_.travel(path);
    if (!travel_result) {
      LOG_ERROR("NO TRAVEL RESULTS, stop game %s", id_.c_str());
//      while (!(should_stop())) {
//        LOG_ERROR("WAITING GAME %s TO STOP", id_.c_str());
//        std::this_thread::sleep_for(60s);
//      }
      return true;
    }

    std::string to = path.back();
    state_.update_on_travel(from, to, travel_result.value());
    int threshold;
    if (state_.ship.cargo->filled() > 0) {
      threshold = state_.ship.cargo->filled() + min_load_on_planet_;
      LOG_INFO("Updated threshold = %d", threshold);
    } else {
      threshold = min_load_;
      LOG_INFO("Min load threshold = %d", threshold);
    }

    std::vector<models::Garbage> combined_items = state_.ship.cargo->items();
    for (const auto &item : state_.map.planets[state_.ship.planet].items) {
      combined_items.push_back(item);
    }
    std::sort(combined_items.begin(), combined_items.end());

    state_.ship.cargo->clear();
    state_.ship.cargo->fit_objects(combined_items);
    bool was_collect = false;
    int left_items = 0;
    if (state_.map.planets[state_.ship.planet].items.size() > 0 && (state_.ship.cargo->filled() >= threshold
        || state_.ship.cargo->full() || state_.ship.cargo->items().size() == combined_items.size())) {
      LOG_INFO("Ship will collect %zu items from %zu [%d / %d]",
               state_.ship.cargo->items().size(),
               combined_items.size(),
               state_.ship.cargo->filled(),
               state_.ship.cargo->capacity());
//      if (should_stop()) {
//        // check before api call.
//        return;
//      }
      auto collect_result = api_.collect(state_.ship.cargo->items());
      was_collect = true;
      if (!collect_result) {
        LOG_ERROR("No collect results");
        return false;
      }

//      std::unordered_map<std::string, const models::Garbage*> sent;
//      for(const auto& item: state_.ship.cargo->items()) {
//        sent[item.name] = &item;
//      }

      int count = 0;
      for (auto &m : collect_result.value()["garbage"].GetObject()) {
//        models::Garbage g(m.name.GetString(), parse_points(m.value));
        count++;
      }

      if (count != state_.ship.cargo->items().size()) {
        LOG_ERROR("COLLECTION MISSMATCH");
        return false;
      }

      for (auto &m : collect_result.value()["leaved"].GetArray()) {
        left_items++;
      }

      // TODO: update on collect?
    } else {
      LOG_INFO("Ship will ignore planet: filled %d required %d",
               state_.ship.cargo->filled(), threshold);
    }

    if (was_collect) {
//      if (state_.ship.cargo->items().size() == combined_items.size()) {
      if (left_items == 0) {
        state_.map.planets[to].was_cleared = true;
        state_.map.planets[to].items.clear();
        state_.map.planets[to].can_have_items = false;
      } else {
        state_.map.planets[to].can_have_items = true;
      }
    } else {
      state_.map.planets[to].can_have_items = false;
      if (state_.map.planets[to].items.size() > 0) {
        state_.map.planets[to].items.clear();
        for (const auto &n : state_.map.get_neighbours(to)) {
          if (!state_.map.planets[n.to].was_cleared) {
            state_.map.planets[n.to].can_have_items = true;
          }
        }
      }
    }
  }
}
}