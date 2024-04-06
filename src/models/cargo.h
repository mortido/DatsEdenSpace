#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>

#include <iostream>

#include "../logger.h"
#include "garbage.h"

namespace mortido::models {

class Cargo {
 public:

  Cargo(int w, int h) : width_{w}, height_{h}, capacity_{w * h}, filled_{0}, space_(w, std::vector<bool>(h, false)) {
    for (int x = 0; x < width_; ++x) {
      for (int y = 0; y < height_; ++y) {
        candidates_.emplace_back(x, y);
      }
    }
    std::sort(candidates_.begin(), candidates_.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
//      return a.second < b.second || (a.second == b.second && a.first < b.first);
      return a.second + a.first < b.second + b.first;
    });
  }

  void print() {
    std::cout << std::endl << "CARGO" << std::endl;
    for (int x = 0; x < width_; ++x) {
      for (int y = 0; y < height_; ++y) {
        std::cout << (space_[x][y] ? "#" : ".");
      }
      std::cout << std::endl;
    }
  }

  void fit_objects(std::vector<Garbage> &items) {
    LOG_SCOPE_FUNCTION(INFO);
    LOG_INFO("Items: %zu", items.size());
    failed_fit_ = false;
    std::unordered_set<std::string> names;
    for (auto &item : items) {
      if (names.find(item.name) != names.end()) {
        LOG_ERROR("ITEM NAMES COLLISION %s", item.name);
        continue;
      }
      names.insert(item.name);

      bool placed = false;

      int max_x = width_ - item.width;
      int max_y = height_ - item.height;
      for (const auto &candidate : candidates_) {
        for (int i = 0; !placed && i < 4; ++i) {
          if (candidate.first < max_x && candidate.second < max_y
              && can_fit(item, candidate.first, candidate.second)) {
            place(item, candidate.first, candidate.second);
            placed = true;
            break; // Stop searching once placed
          } else {
            item.rotate();
          }
        }
        if (placed) {
          break;
        }
      }
    }
    failed_fit_ = items_.size() < items.size();
  }

  const std::vector<Garbage> &items() {
    return items_;
  }

  int capacity() {
    return capacity_;
  }

  int filled() {
    return filled_;
  }

  void emplace(Garbage &&item) {
    items_.emplace_back(std::move(item));
    filled_ += items_.back().points.size();
    for (auto &p : items_.back().points) {
      space_[p.x][p.y] = true;
    }
  }

  void clear() {
    filled_ = 0;
    items_.clear();
    std::vector temp(width_, std::vector<bool>(height_, false));
    space_.swap(temp);
  }

  bool full() {
    return filled_ == capacity_;
  }

  bool should_go_home() {
    return failed_fit_ || filled_ > (static_cast<double>(capacity_) * 0.5);
  }

 private:
  int width_;
  int height_;
  int capacity_;
  int filled_;
  bool failed_fit_;
  std::vector<std::pair<int, int>> candidates_;
  std::vector<std::vector<bool>> space_;
  std::vector<Garbage> items_;

  bool can_fit(const Garbage &item, int offset_x, int offset_y) {
    for (const auto &p : item.points) {
      int new_x = p.x + offset_x;
      int new_y = p.y + offset_y;
      if (new_x >= space_.size() || new_y >= space_[0].size() || space_[new_x][new_y]) {
        return false;
      }
    }
    return true;
  }

  void place(Garbage item, int offset_x, int offset_y) {
    for (auto &p : item.points) {
      p.x += offset_x;
      p.y += offset_y;
      space_[p.x][p.y] = true;
    }
    filled_ += item.points.size();
    items_.emplace_back(std::move(item));
  }
};

}
