#include "checkersMinMax.hpp"
#include <iostream>
using namespace std;

void print(const array<array<Player, 8>, 8> &aa) {
  for (const auto &i : aa) {
    for (const auto &j : i) {
      if (j == Player::player0)
        cout << 'x';
      else if (j == Player::player1)
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
//  CheckersMinMax game;
//  auto &aa = game.getGameBoard();
//  print(aa);
  cout << "ha" << endl;
}
