#include "checkersMinMax.hpp"
#include "stateCounter.hpp"

array<bool, 2> CheckersMinMax::validateMove(const GameBoard &gameBoard,
                                            const array<int, 2> &currentPos,
                                            const array<int, 2> &nextPos,
                                            Player player) {
  // array[rows, cols]
  if (nextPos[0] >= 8 or nextPos[0] < 0 or nextPos[1] >= 8 or nextPos[1] < 0) {
    return {false, false};
  }
  if (gameBoard[nextPos[0]][nextPos[1]] == player) {
    return {false, false};
  } else if (gameBoard[nextPos[0]][nextPos[1]] != Player::nothing) {
    // Is an opponent piece
    const array<int, 2> jumpSquare = {nextPos[0] + nextPos[0] - currentPos[0],
                                      nextPos[1] + nextPos[1] - currentPos[1]};

    if (jumpSquare[0] >= 8 or jumpSquare[0] < 0 or jumpSquare[1] >= 8 or
        jumpSquare[1] < 0) {
      return {false, false};
    }
    if (gameBoard[jumpSquare[0]][jumpSquare[1]] != Player::nothing) {
      return {false, false};
    }
    return {true, true};
  }
  return {true, false};
}

pair<array<int, 2>, array<int, 2>>
CheckersMinMax::playAI(const GameBoard &gameBoard, int treeLevel,
                       Player aiPlayer, int personPieces, int aiPieces) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; i < 8; j++) {
    }
  }

  return pair<array<int, 2>, array<int, 2>>();
}

list<StateCounter>
CheckersMinMax::generateValidMoves(const GameBoard &gameBoard,
                                   Player playerTurn, Player aiPlayer,
                                   int currentLevel) {
  list<StateCounter> states;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (gameBoard[i][j] == playerTurn) {
        if (playerTurn == aiPlayer) { // AI go down.
          auto left =
              validateMove(gameBoard, {i, j}, {i + 1, j - 1}, playerTurn);
          auto right =
              validateMove(gameBoard, {i, j}, {i + 1, j + 1}, playerTurn);
          if (left[0]) {
            states.emplace_back(currentLevel + 1);
            states.back().boardState = gameBoard;
            if (left[1]) { // Piece eaten.
              states.back().boardState[i][j] = Player::nothing;
              states.back().boardState[i + 2][j - 2] = playerTurn;
            } else {
              states.back().boardState[i][j] = Player::nothing;
              states.back().boardState[i + 1][j - 1] = playerTurn;
            }
          }
          if (right[0]) {
            states.emplace_back(currentLevel + 1);
            states.back().boardState = gameBoard;
            if (right[1]) { // piece eaten
              states.back().boardState[i][j] = Player::nothing;
              states.back().boardState[i + 2][j + 2] = playerTurn;
            } else {
              states.back().boardState[i][j] = Player::nothing;
              states.back().boardState[i + 1][j + 1] = playerTurn;
            }
          }
        } else { // Human go up.
          auto left =
              validateMove(gameBoard, {i, j}, {i - 1, j - 1}, playerTurn);
          auto right =
              validateMove(gameBoard, {i, j}, {i - 1, j + 1}, playerTurn);
          if (left[0]) {
            states.emplace_back(currentLevel + 1);
            states.back().boardState = gameBoard;
            if (left[1]) { // Piece eaten.
              states.back().boardState[i][j] = Player::nothing;
              states.back().boardState[i - 2][j - 2] = playerTurn;
            } else {
              states.back().boardState[i][j] = Player::nothing;
              states.back().boardState[i - 1][j - 1] = playerTurn;
            }
          }
          if (right[0]) {
            states.emplace_back(currentLevel + 1);
            states.back().boardState = gameBoard;
            if (right[1]) { // piece eaten
              states.back().boardState[i][j] = Player::nothing;
              states.back().boardState[i - 2][j + 2] = playerTurn;
            } else {
              states.back().boardState[i][j] = Player::nothing;
              states.back().boardState[i - 1][j + 1] = playerTurn;
            }
          }
        }
      }
    }
  }

  return list<StateCounter>();
}
