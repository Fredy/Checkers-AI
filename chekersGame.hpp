#pragma once

#include <array>
using namespace std;

enum class Player {
  player0 = 0,
  player1 = 1,
  nothing = 2
};

class CheckersGame {
private:
  array<array<Player, 8>, 8> gameBoard;
  Player firstPLayer; // 0: playerA, 1: playerB;
  Player actualTurn;  // 0: playerA, 1: playerB;
  array<int, 2> playerPieces;

  void initGameBoard();

public:
  explicit CheckersGame(Player firstPLayer = Player::player0);
  void reset(Player firstPlayer = Player::player0);
  const Player &getActualTurn();
  const Player &getFirstPlayer();
  const array<array<Player, 8>, 8> &getGameBoard();
  const array<int, 2> &getPlayerPieces();
  void play(Player player, array<size_t, 2> initialPos, array<size_t, 2> finalPos);
};
