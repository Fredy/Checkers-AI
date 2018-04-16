#include "checkersMinMax.hpp"
#include <iostream>
using namespace std;

void print(const array<array<Player, 8>, 8> &aa) {
  for (const auto &i : aa) {
    for (const auto &j : i) {
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
  cout << "ha" << endl;
}
