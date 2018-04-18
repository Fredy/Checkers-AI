#include "node.hpp"
#include <cstdlib>

size_t Node::getNumberChilds() const { return numberChilds; }

void Node::setNumberChilds(size_t numberChilds) {
  Node::numberChilds = numberChilds;
}

size_t Node::getFirstChildIndex() const { return firstChildIndex; }

void Node::setFirstChildIndex(size_t firstChildIndex) {
  Node::firstChildIndex = firstChildIndex;
}

size_t Node::getParentIndex() const { return parentIndex; }

void Node::setParentIndex(size_t parentIndex) {
  Node::parentIndex = parentIndex;
}

Move *Node::getMoves() const { return moves; }

int Node::getPieceDiff() const { return pieceDiff; }

void Node::setPieceDiff(int pieceDiff) {
  Node::pieceDiff = pieceDiff;
}

Node::Node(size_t threeLevel) {
  moves = new Move[threeLevel];
  parentIndex = -1;
  firstChildIndex = -1;
  numberChilds = 0;
}

Node::Node(size_t treeLevel, const Move *parentMoves, const Move &newMove) {
  moves = new Move[treeLevel];
  parentIndex = -1;
  firstChildIndex = -1;
  numberChilds = 0;

  copy(parentMoves, parentMoves + treeLevel - 1, moves);
  moves[treeLevel - 1] = newMove;
}

Node::~Node() { delete[] moves; }

deque<Move> Node::generateChildMoves(const GameBoard &gameBoard,
                                     size_t currentTreeLevel) {
  GameBoard currentGameBoard = gameBoard;
  for (size_t i = 0; i < currentTreeLevel; i++) {
    currentGameBoard[moves[i].prevRow][moves[i].prevCol] = Player::nothing;
    currentGameBoard[moves[i].nextRow][moves[i].nextCol] = moves[i].player;
    if (abs(moves[i].nextRow - moves[i].prevRow) == 2) {
      SmallInt eatenRow = (moves[i].nextRow + moves[i].prevRow) / SmallInt(2);
      SmallInt eatenCol = (moves[i].nextCol + moves[i].prevCol) / SmallInt(2);
      currentGameBoard[eatenRow][eatenCol] = Player::nothing;
    }
  }
  // top: l: -1, -1; r: -1, 1
  // bottom: l: 1, -1; r: 1, 1
  // Remember that human player goes from bottom to top and computer player goes
  // from top to bottom.
  if (moves[currentTreeLevel - 1].player == Player::human) {
    // Computer has the next turn
    return generateComputerMoves(currentGameBoard);
  } else {
    // Human has the next turn
    return generateHumanMoves(currentGameBoard);
  }
}

void Node::calcPieceDiff(const GameBoard &gameBoard, size_t treeLevels) {
  GameBoard currentGameBoard = gameBoard;
  for (size_t i = 0; i < treeLevels; i++) {
    currentGameBoard[moves[i].prevRow][moves[i].prevCol] = Player::nothing;
    currentGameBoard[moves[i].nextRow][moves[i].nextCol] = moves[i].player;
    if (abs(moves[i].nextRow - moves[i].prevRow) == 2) {
      SmallInt eatenRow = (moves[i].nextRow + moves[i].prevRow) / SmallInt(2);
      SmallInt eatenCol = (moves[i].nextCol + moves[i].prevCol) / SmallInt(2);
      currentGameBoard[eatenRow][eatenCol] = Player::nothing;
    }
  }
  pieceDiff = 0;
  for (const auto&row : currentGameBoard) {
    for (const auto& i : row) {
      if (i == Player::human) {
        pieceDiff--;
      } else if (i == Player::computer) {
        pieceDiff++;
      }
    }
  }
}

deque<Move> Node::generatePlayerMoves(const GameBoard &gameBoard, Player player,
                                      const array<int, 2> &movLeft,
                                      const array<int, 2> &movRight) {
  deque<Move> genMoves;
  for (size_t i = 0; i < gameBoard.size(); i++) {
    for (size_t j = 0; j < gameBoard.at(0).size(); j++) {

      if (gameBoard[i][j] == player) {
        int checkLeft =
            checkSquare(gameBoard, i + movLeft[0], j + movLeft[1], player);
        if (checkLeft == 1) {
          genMoves.emplace_back(i, j, i + movLeft[0], j + movLeft[1], player);
        } else if (checkLeft == -1) {
          int checkEat = checkSquare(gameBoard, i + 2 * movLeft[0],
                                     j + 2 * movLeft[1], player);
          if (checkEat == 1) {
            genMoves.emplace_back(i, j, i + 2 * movLeft[0], j + 2 * movLeft[1],
                                  player);
          }
        }

        int checkRight =
            checkSquare(gameBoard, i + movRight[0], j + movRight[1], player);
        if (checkRight == 1) {
          genMoves.emplace_back(i, j, i + movRight[0], j + movRight[1], player);
        } else if (checkRight == -1) {
          int checkEat = checkSquare(gameBoard, i + 2 * movRight[0],
                                     j + 2 * movRight[1], player);
          if (checkEat == 1) {
            genMoves.emplace_back(i, j, i + 2 * movRight[0],
                                  j + 2 * movRight[1], player);
          }
        }
      }
    }
  }

  return genMoves;
}

int Node::checkSquare(const GameBoard &gameBoard, SmallInt row, SmallInt col,
                      Player playerTurn) {
  if (row < 0 or row >= 8 or col < 0 or col >= 8) {
    return 0;
  }
  if (gameBoard[row][col] == playerTurn) {
    return 0;
  } else if (gameBoard[row][col] == Player::nothing) {
    return 1;
  } else {
    return -1;
  }
}

deque<Move> Node::generateComputerMoves(const GameBoard &gameBoard) {
  return generatePlayerMoves(gameBoard, Player::computer, {1, -1}, {1, 1});
}

deque<Move> Node::generateHumanMoves(const GameBoard &gameBoard) {
  return generatePlayerMoves(gameBoard, Player::human, {-1, -1}, {-1, 1});
}

