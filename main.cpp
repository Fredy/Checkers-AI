#include "checkersMinMax.hpp"
#include <iostream>
using namespace std;

GameBoard gameBoard;
void initGameBoard() {
  // Set all the board squares to nothing.
  for (auto &row : gameBoard) {
    row.fill(Player::nothing);
  }

  // Set the top part of the board to player0.
  for (size_t i = 0; i < 3; i++) {
    const int evenRow = !(i & 1);
    for (size_t j = 0; j < gameBoard.size(); j += 2) {
      gameBoard[i][j + evenRow] = Player::computer;
    }
  }

  // Set the top part of the board to player0.
  for (size_t i = 0; i < 3; i++) {
    const int oddRow = i & 1;
    for (size_t j = 0; j < gameBoard.size(); j += 2) {
      gameBoard[7 - i][j + oddRow] = Player::human;
    }
  }
}

void print(GameBoard &aa) {
  for (const auto& i : aa) {
    for (const auto& j : i) {
      if (j == Player::computer)
        cout << 'x';
      else if (j == Player::human)
        cout << 'o';
      else if (j == Player::nothing)
        cout << ' ';
      else
        cout << '-';
    }
    cout << '\n';
  }
}

int main() {
  CheckersMinMax game;

  initGameBoard();
  print(gameBoard);
  cout << "\n------\n";
  auto asd =  game.playAI(gameBoard, 5);
  cout << asd.first[0] << ' ' << asd.first[1] << " - " << asd.second[0] << ' ' << asd.second[1];
}
