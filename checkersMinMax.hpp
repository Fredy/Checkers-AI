#pragma once

#include "types.hpp"
#include <deque>
#include <list>
#include <utility>
using namespace std;

class Node;

class CheckersMinMax {
private:
  deque<Node> buildTree(const GameBoard &gameBoard, size_t treeLevels);

public:
  CheckersMinMax() = default;

  /**
   * @brief This decides the next mov for the computer player.
   * @param gameBoard Matrix containing pieces.
   * @param treeLevel The max level of the tree, starts at 0.
   * @param aiPlayer The player that represents the computes (player0 or
   * player1).
   * @param personPieces Number of pieces that the human player has.
   * @param aiPieces Number of pieces that the computer player has.
   * @return A pair containing the previous position and the next position of
   * the piece to be moved by the computer.
   */
  pair<array<int, 2>, array<int, 2>> playAI(const GameBoard &gameBoard,
                                            size_t treeLevels);
};
