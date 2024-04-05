#pragma once
#include <string>
#include <utility>

namespace mortido::net {

class Api {
 public:
  explicit Api(std::string token) : token_{std::move(token)} {

  }

 private:
  std::string token_;
};

}
