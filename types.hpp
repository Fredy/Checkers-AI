#pragma once

#include <array>
using namespace std;

enum class Player : char {
  player0 = 0,
  player1 = 1,
  nothing = 2
};

using GameBoard = array<array<Player, 8>, 8>;
