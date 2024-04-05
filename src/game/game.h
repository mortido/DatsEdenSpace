#pragma once
#include <string>
#include <utility>

#include "../logger.h"

namespace mortido::game {

class Game {
 public:
  explicit Game(std::string game_id)
      : id_{std::move(game_id)}, log_file_{"data/game_" + id_ + ".log"} {
    loguru::add_file(log_file_.c_str(), loguru::Truncate, loguru::Verbosity_INFO);
  }

  ~Game() {
    loguru::remove_callback(log_file_.c_str());
    loguru::flush();
  }

  void play() {
    LOG_SCOPE_FUNCTION(INFO);
    LOG_INFO("Game %s started", id_.c_str());


    // Log completion
    LOG_INFO("Game %s finished", id_.c_str());
  }

 private:
  std::string id_;
  std::string log_file_;
};

}  // namespace mortido
