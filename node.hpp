#pragma once
#include "types.hpp"
#include <deque>

struct Move {
  SmallInt prevRow;
  SmallInt prevCol;
  SmallInt nextRow;
  SmallInt nextCol;
  Player player;

  Move() = default;
  Move(SmallInt prevRow, SmallInt prevCol, SmallInt nextRow, SmallInt nextCol,
       Player player)
      : prevRow(prevRow), prevCol(prevCol), nextRow(nextRow), nextCol(nextCol),
        player(player) {}
};

class Node {
private:
  size_t numberChilds;
  size_t firstChildIndex;
  size_t parentIndex;
  Move *moves;   // An array of Moves in order. In level 0, 0 moves are done; in
                 // level 1, 1 move, and so on.
  int pieceDiff; // Computer Pieces - Human Pieces.

  /* Returns: 0 if it's an invalid square, 1 if its valid and -1 if it contains
   * and enemy piece */
  int checkSquare(const GameBoard &gameBoard, SmallInt row, SmallInt col,
                  Player playerTurn);
  deque<Move> generateHumanMoves(const GameBoard &gameBoard);
  deque<Move> generateComputerMoves(const GameBoard &gameBoard);
  deque<Move> generatePlayerMoves(const GameBoard &gameBoard, Player player,
                                  const array<int, 2> &movLeft,
                                  const array<int, 2> &movRight);

public:
  Node() = delete;
  explicit Node(size_t treeLevel);
  Node(size_t treeLevel, const Move *parentMoves, const Move &newMove);

  ~Node();

  deque<Move> generateChildMoves(const GameBoard &gameBoard,
                                 size_t currentTreeLevel);
  void calcPieceDiff(const GameBoard &gameBoard, size_t treeLevels);

  size_t getNumberChilds() const;
  void setNumberChilds(size_t numberChilds);
  size_t getFirstChildIndex() const;
  void setFirstChildIndex(size_t firstChildIndex);
  size_t getParentIndex() const;
  void setParentIndex(size_t parentIndex);
  Move *getMoves() const;
  int getPieceDiff() const;
  void setPieceDiff(int pieceDiff);
};
