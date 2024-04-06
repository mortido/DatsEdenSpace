#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

#include <rapidjson/document.h>

#include "logger.h"

namespace mortido::models {

class Cargo {
  int fitObjects(int width, int height, std::vector<Garbage>& objects) {
    std::vector<std::vector<bool>> board(width, std::vector<bool>(height, false));
    int count = 0;

    for (auto& object : objects) {
      bool placed = false;
      for (int x = 0; !placed && x < width; ++x) {
        for (int y = 0; !placed && y < height; ++y) {
          if (canFit(object.points, board, x, y)) {
            placeObject(object.points, board, x, y);
            placed = true;
            count++;
          }
        }
      }
    }

    return count;
  }

 private:
  int width_;
  int height_;
  int capacity_;
  int filled_;
  std::vector<std::vector<bool>> space_;
  std::vector<Garbage> items_;

  bool can_fit(const Garbage& item, int offset_x, int offset_y) {
    for (const auto& p : item.points) {
      int new_x = p.x + offset_x;
      int new_y = p.y + offset_y;
      if (new_x >= space_.size() || new_y >= space_[0].size() || space_[new_x][new_y]) {
        return false;
      }
    }
    return true;
  }

  void place(const Garbage& item, int offset_x, int offset_y) {

  }
};

struct Ship {
  int capacityX;
  int capacityY;
  int fuelUsed;
  std::string planet;
  std::vector<Garbage> items;
};

struct Edge {
  std::string to;
  int distance;

  bool operator<(const Edge &other) const {
    return distance < other.distance;
  }
};

class UniverseGraph {
 public:
  void add_edge(const std::string &from, const std::string &to, int distance) {
    neighbours[from].push_back({to, distance});
    std::sort(neighbours[from].begin(), neighbours[from].end());
  }

  void update_edge(const std::string &from, const std::string &to, int distance) {
    for (auto &edge : neighbours[from]) {
      if (edge.to == to) {
        edge.distance = distance;
        break;
      }
    }
    std::sort(neighbours[from].begin(), neighbours[from].end());
  }

  [[nodiscard]] const std::vector<Edge> &get_neighbours(const std::string &from) const {
    static const std::vector<Edge> empty;

    auto it = neighbours.find(from);
    if (it != neighbours.end()) {
      return it->second;
    }
    return empty;
  }

 private:
  std::unordered_map<std::string, std::vector<Edge>> neighbours;
};

struct GameState {
  Ship ship;
  std::unordered_map<std::string, Planet> planets;
  UniverseGraph map;

  static GameState from_universe_json(const rapidjson::Document &json_state);
  void update_planet_garbage(const std::string &planet, const rapidjson::Value &garbage);
  void update_on_travel(const std::string &from, const std::string &to, const rapidjson::Document &json_state);
};

}
