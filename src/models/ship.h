#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../logger.h"
#include "garbage.h"
#include "cargo.h"

namespace mortido::models {

struct Ship {
  std::unique_ptr<Cargo> cargo;
  int fuelUsed;
  std::string planet;
};

}
