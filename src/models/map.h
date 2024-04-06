#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <optional>

#include "../logger.h"

namespace mortido::models {

struct Planet {
  std::string name;
  bool was_cleared = false;
  bool can_have_items = true;
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

  std::vector<std::string> next_to_clean(const std::string from) {
    LOG_SCOPE_FUNCTION(INFO);
    LOG_INFO("Looking for planet to clean from %s", from.c_str());

    std::unordered_map<std::string, int> distances;
    std::unordered_map<std::string, std::string> predecessors;
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<>> frontier;
    std::unordered_set<std::string> visited;

    // Initialize distances to all nodes as infinity, except the from node
    for (const auto &pair : neighbours) {
      distances[pair.first] = std::numeric_limits<int>::max();
    }
    distances[from] = 0;

    frontier.push({0, from});

    std::optional<std::string> to;
    while (!frontier.empty()) {
      auto [currentDistance, currentNode] = frontier.top();
      frontier.pop();

      if (visited.find(currentNode) != visited.end()) {
        continue;
      }
      visited.insert(currentNode);

      if (currentNode != from && !planets[currentNode].was_cleared && planets[currentNode].can_have_items) {
        LOG_INFO("Found planet to clean %s, distance: %d", currentNode.c_str(), currentDistance);
        to = currentNode;
        break;
      }

      for (const auto &edge : neighbours[currentNode]) {
        int newDistance = currentDistance + edge.distance;
        if (newDistance < distances[edge.to]) {
          distances[edge.to] = newDistance;
          predecessors[edge.to] = currentNode;
          frontier.push({newDistance, edge.to});
        }
      }
    }

    if (!to) {
      LOG_INFO("NO MORE PLANETS TO CLEAN");
      return {}; // Return empty if no path found
    }

    // Backtrack from to to from using predecessors to find the path
    std::vector<std::string> path;
    for (std::string at = to.value(); at != from; at = predecessors[at]) {
      if (at.empty() || predecessors.find(at) == predecessors.end()) {
        LOG_ERROR("CANT RESTORE PATH");
        return {}; // Return empty if no path found
      }
      path.push_back(at);
    }
//    path.push_back(from);
    std::reverse(path.begin(), path.end());

    std::stringstream ss;
    for (const auto &p : path) {
      ss << " -> " << p;
    }
    LOG_INFO(ss.str().c_str());

    return path;
  }

  std::vector<std::string> find_path(const std::string &from, const std::string &to) {
    LOG_SCOPE_FUNCTION(INFO);
    LOG_INFO("Looking for path from %s to %s", from.c_str(), to.c_str());
    std::unordered_map<std::string, int> distances;
    std::unordered_map<std::string, std::string> predecessors;
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<>> frontier;
    std::unordered_set<std::string> visited;

    // Initialize distances to all nodes as infinity, except the from node
    for (const auto &pair : neighbours) {
      distances[pair.first] = std::numeric_limits<int>::max();
    }
    distances[from] = 0;

    frontier.push({0, from});

    while (!frontier.empty()) {
      auto [currentDistance, currentNode] = frontier.top();
      frontier.pop();

      if (visited.find(currentNode) != visited.end()) {
        continue;
      }
      visited.insert(currentNode);

      if (currentNode == to) {
        LOG_INFO("Found path from %s to %s, distance: %d", from.c_str(), to.c_str(), currentDistance);
        break;
      }

      for (const auto &edge : neighbours[currentNode]) {
        int newDistance = currentDistance + edge.distance;
        if (newDistance < distances[edge.to]) {
          distances[edge.to] = newDistance;
          predecessors[edge.to] = currentNode;
          frontier.push({newDistance, edge.to});
        }
      }
    }

    // Backtrack from to to from using predecessors to find the path
    std::vector<std::string> path;
    for (std::string at = to; at != from; at = predecessors[at]) {
      if (at.empty() || predecessors.find(at) == predecessors.end()) {
        LOG_ERROR("Didn't found path from %s to %s", from.c_str(), to.c_str());
        return {}; // Return empty if no path found
      }
      path.push_back(at);
    }
//    path.push_back(from);
    std::reverse(path.begin(), path.end());

    std::stringstream ss;
    for (const auto &p : path) {
      ss << " -> " << p;
    }
    LOG_INFO(ss.str().c_str());

    return path;
  }
 public:
  std::unordered_map<std::string, Planet> planets;
 private:
  std::unordered_map<std::string, std::vector<Edge>> neighbours;
};

}
