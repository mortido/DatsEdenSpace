#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>

#include "logger.h"
#include "game.h"
#include "api.h"

using namespace std::chrono_literals;

std::string get_game_id() {
  auto now = std::chrono::system_clock::now();
  auto now_time_t = std::chrono::system_clock::to_time_t(now);

  std::ostringstream oss;
  oss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d_%H-%M-%S");
  return oss.str();
}

constexpr const char *kMainLogFile = "data/main.log";

int main(int argc, char *argv[]) {
  loguru::init(argc, argv);
  loguru::g_flush_interval_ms = 0;  // unbuffered
  loguru::add_file(kMainLogFile, loguru::Append, loguru::Verbosity_WARNING);

  mortido::net::Api api("https://datsedenspace.datsteam.dev", "YOUR_TOKEN_HERE");

  std::string game_id = get_game_id();
  auto round = api.get_current_round();
  if (round) {
    game_id = round.value();
  }

//  api.reset();
  while(true) {
    mortido::game::Game game(game_id, api);
    game.load();
    bool result = game.play();

    if (!result){
      LOG_INFO("GAME %s FINISHED WITH POSSIBLE ERROR, RESTART", game_id.c_str());
      continue;
    }

    LOG_INFO("GAME %s FINISHED, WAITING FOR NEW ONE....", game_id.c_str());
    auto old_game = game_id;

    game_id = api.get_current_round().value_or("");
    while (game_id.empty() || game_id == old_game) {
      LOG_INFO("NO NEW CURRENT ROUND");
      std::this_thread::sleep_for(30s);
      game_id = api.get_current_round().value_or("");
    }
  }

  loguru::remove_all_callbacks();
  loguru::flush();

  return EXIT_SUCCESS;
}