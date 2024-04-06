#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <iostream>

#include "../logger.h"
#include "point.h"

namespace mortido::models {

struct Garbage {
  std::string name;
  std::vector<Point> points;
  int width = 0;
  int height = 0;

  Garbage(std::string n, std::vector<Point> &&p) : name{std::move(n)}, points{std::move(p)} {
    normalize();
  }

  void print() {
    std::cout << std::endl << "ITEM" << std::endl;
    std::vector<std::vector<bool>> space_(width+1, std::vector<bool>(height +1, false));
    for (auto &p : points) {
      space_[p.x][p.y] = true;
    }
    for (int x = 0; x <= width; ++x) {
      for (int y = 0; y <= height; ++y) {
        std::cout << (space_[x][y] ? "#" : ".");
      }
      std::cout << std::endl;
    }
  }

  void rotate() {
    for (auto &point : points) {
      int temp = point.x;
      point.x = -point.y;
      point.y = temp;
    }
    normalize();
  }

  bool operator<(const Garbage &other) const {
    if (points.size() == other.points.size()) {
      return width+height > other.width+other.height;
//      return name < other.name;
    }
    return points.size() > other.points.size();
  }

 private:
  void normalize() {
    if (!points.empty()) {
      int minX = points[0].x, maxX = points[0].x;
      int minY = points[0].y, maxY = points[0].y;

      for (const auto &point : points) {
        minX = std::min(minX, point.x);
        maxX = std::max(maxX, point.x);
        minY = std::min(minY, point.y);
        maxY = std::max(maxY, point.y);
      }

      for (auto &point : this->points) {
        point.x -= minX;
        point.y -= minY;
      }

      width = maxX - minX;  // +1
      height = maxY - minY;  // +1
    }
  }
};

}
