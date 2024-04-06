#pragma once
#include <string>
#include <utility>

#include "logger.h"
#include "api.h"

#include "models/game_state.h"

namespace mortido::game {

class Game {
 public:
  explicit Game(std::string game_id, net::Api &api)
      : id_{std::move(game_id)}, log_file_{"data/game_" + id_ + ".log"}, api_{api} {
    loguru::add_file(log_file_.c_str(), loguru::Append, loguru::Verbosity_MAX);
  }

  ~Game() {
    loguru::remove_callback(log_file_.c_str());
    loguru::flush();
  }

  void load();
  bool play();

 private:
  std::string id_;
  std::string log_file_;
  net::Api &api_;

  int min_load_;
  int min_load_on_planet_;

  std::string home_{"Earth"};
  std::string garbage_collector_{"Eden"};

  std::string team_name_;
  models::GameState state_;

  bool should_stop();
};

}  // namespace mortido
