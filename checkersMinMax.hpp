#pragma once

#include "types.hpp"
#include <list>
#include <utility>
using namespace std;

class StateCounter;

class CheckersMinMax {
private:
  // The first bool represents if the move is valid, the second if a piece was
  // eaten
  array<bool, 2> validateMove(const GameBoard &gameBoard,
                              const array<int, 2> &currentPos,
                              const array<int, 2> &nextPos, Player player);

  list<StateCounter> generateValidMoves(const GameBoard &gameBoard,
                                        Player playerTurn, Player aiPlayer, int currentLevel);

public:
  CheckersMinMax() = delete;

  /**
   * @brief This decides the next mov for the computer player.
   * @param gameBoard Matrix containing pieces.
   * @param treeLevel The max level of the tree.
   * @param aiPlayer The player that represents the computes (player0 or
   * player1).
   * @param personPieces Number of pieces that the human player has.
   * @param aiPieces Number of pieces that the computer player has.
   * @return A pair containing the previous position and the next position of
   * the piece to be moved by the computer.
   */
  pair<array<int, 2>, array<int, 2>> playAI(const GameBoard &gameBoard,
                                            int treeLevel, Player aiPlayer,
                                            int personPieces, int aiPieces);
};
