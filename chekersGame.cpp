#include "chekersGame.hpp"

CheckersGame::CheckersGame(Player firstPLayer) {
  reset(firstPLayer);
}

void CheckersGame::reset(Player firstPlayer) {
  this->firstPLayer = actualTurn = firstPLayer;
  playerPieces = {12, 12};
  initGameBoard();
}

void CheckersGame::initGameBoard() {
  // Set all the board squares to nothing.
  for (auto &row : gameBoard) {
    row.fill(Player::nothing);
  }

  // Set the top part of the board to player0.
  for (size_t i = 0; i < 3; i++) {
    const int evenRow = !(i & 1);
    for (size_t j = 0; j < gameBoard.size(); j += 2) {
      gameBoard[i][j + evenRow] = Player::player0;
    }
  }

  // Set the top part of the board to player0.
  for (size_t i = 0; i < 3; i++) {
    const int oddRow = i & 1;
    for (size_t j = 0; j < gameBoard.size(); j += 2) {
      gameBoard[7 - i][j + oddRow] = Player::player1;
    }
  }
}

const Player &CheckersGame::getActualTurn() {
  return actualTurn;
}

const Player &CheckersGame::getFirstPlayer() {
  return firstPLayer;
}

const array<array<Player, 8>, 8> &CheckersGame::getGameBoard() {
  return gameBoard;
}

const array<int, 2> &CheckersGame::getPlayerPieces() {
  return playerPieces;

}

void CheckersGame::play(Player player,
                        array<size_t, 2> initialPos,
                        array<size_t, 2> finalPos) {
  if (player == Player::nothing) {
    return; // TODO: throw error!
  }
  if (player != actualTurn) {
    return; // TODO: throw error!
  }
  if (gameBoard.at(initialPos[0]).at(initialPos[1]) != actualTurn){
    return; // TODO: throw error!
  }
  // TODO: Game logic

}