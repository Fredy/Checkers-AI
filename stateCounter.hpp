#pragma once

#include "types.hpp"
#include <algorithm>
#include <list>
using namespace std;

// TODO: implement proper getters and setters, and separate declaration and
// definition
class StateCounter {
public:
  int piecesDiff = 0; // Stores the min-max value of the child nodes, if it's a leaf
  // node it stores the min-max of the board state (AI Pieces - Human Pieces)

  GameBoard boardState;
  int treeLevel;             // Starts at 0.
  list<StateCounter> *nodes; // The tree nodes.

  StateCounter(int level) {
    treeLevel = level;
    nodes = nullptr;
  }

  void coutPieces(Player aiPlayer) {
    for (const auto &row : boardState) {
      for (const auto &i : row) {
        if (i == aiPlayer) {
          piecesDiff++;
        } else if (i != Player::nothing) {
          piecesDiff--;
        }
      }
    }
  }

  int calculateMin() {
    if (nodes == nullptr) {
      // THROW EXCEPTION!
    } else if (nodes->front().nodes == nullptr) { // Leaf Node
      piecesDiff = min_element(nodes->begin(), nodes->end(),
                           [](const auto &a, const auto &b) {
                             return a->piecesDiff < b->piecesDiff;
                           })->piecesDiff;
    } else { // Non-leaf Node
      piecesDiff = min_element(nodes->begin(), nodes->end(),
                           [](const auto &a, const auto &b) {
                             return a->minMax < b->minMax;
                           })->piecesDiff;
    }
    return piecesDiff;
  }
  int calculateMax() {
    if (nodes == nullptr) {
      // THROW EXCEPTION!
    } else if (nodes->front().nodes == nullptr) { // Leaf Node
      piecesDiff = max_element(nodes->begin(), nodes->end(),
                           [](const auto &a, const auto &b) {
                             return a->piecesDiff < b->piecesDiff;
                           })->piecesDiff;
    } else { // Non-leaf Node
      piecesDiff = max_element(nodes->begin(), nodes->end(),
                           [](const auto &a, const auto &b) {
                             return a->minMax < b->minMax;
                           })->piecesDiff;
    }
    return piecesDiff;
  }
};
