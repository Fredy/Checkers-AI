#pragma once

#include <array>
using namespace std;

enum class Player : char {
  computer = 0,
  human = 1,
  nothing = 2
};

using GameBoard = array<array<Player, 8>, 8>;

using SmallInt = signed char;
