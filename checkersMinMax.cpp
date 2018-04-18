#include "checkersMinMax.hpp"
#include "node.hpp"
#include <algorithm>
#include <vector>

pair<array<int, 2>, array<int, 2>>
CheckersMinMax::playAI(const GameBoard &gameBoard, size_t treeLevels) {
  if (treeLevels <= 1) {
    return {};
  }
  deque<Node> arrayTree = buildTree(gameBoard, treeLevels);
  vector<deque<Node>::reverse_iterator> levelsLimit(treeLevels);
  levelsLimit[0] = arrayTree.rend();
  for (size_t i = 1; i < treeLevels; i++) {
    size_t nextLevelLimit = (levelsLimit[i - 1] - 1)->getFirstChildIndex();
    levelsLimit[i] = arrayTree.rend() - nextLevelLimit;
  }

  auto nodeIndex = arrayTree.rbegin();

  auto minMaxElement = arrayTree.begin();
  for (size_t i = treeLevels - 1; i < treeLevels; i--) {
    for (; nodeIndex < levelsLimit[i]; nodeIndex++) {
      if (nodeIndex->getNumberChilds() == 0) {
        nodeIndex->calcPieceDiff(gameBoard, treeLevels);
      } else {
        size_t numChildren = nodeIndex->getNumberChilds();
        size_t indexChildren = nodeIndex->getFirstChildIndex();

        minMaxElement =
            (i % 2 == 1)
                ? min_element(arrayTree.begin() + indexChildren,
                              arrayTree.begin() + indexChildren + numChildren,
                              [](const auto &a, const auto &b) {
                                return a.getPieceDiff() < b.getPieceDiff();
                              })
                : max_element(arrayTree.begin() + indexChildren,
                              arrayTree.begin() + indexChildren + numChildren,
                              [](const auto &a, const auto &b) {
                                return a.getPieceDiff() > b.getPieceDiff();
                              });
        nodeIndex->setPieceDiff(minMaxElement->getPieceDiff());
      }
    }
    nodeIndex = levelsLimit[i];
  }

  auto chosenMove = minMaxElement->getMoves();
  return {{chosenMove[0].prevRow, chosenMove[0].prevCol},
          {chosenMove[0].nextRow, chosenMove->nextCol}};
}

deque<Node> CheckersMinMax::buildTree(const GameBoard &gameBoard,
                                      size_t treeLevels) {
  deque<Node> arrayTree;
  arrayTree.emplace_back(0);

  deque<Move> possibleMoves =
      arrayTree.front().generateChildMoves(gameBoard, 0);
  arrayTree.front().setFirstChildIndex(1);
  arrayTree.front().setNumberChilds(possibleMoves.size());

  for (const auto &move : possibleMoves) {
    arrayTree.emplace_back(1, arrayTree[0].getMoves(), move);
    arrayTree.back().setParentIndex(0);
  }

  size_t firstChildOfLevel = 1; // begin + 1
  size_t lastChildOfLevel = arrayTree.size() - 1; // end - 1

  for (size_t i = 1; i < treeLevels - 1; i++) {
    for (size_t j = firstChildOfLevel; j <= lastChildOfLevel; j++) {
      possibleMoves = arrayTree[j].generateChildMoves(gameBoard, 0);
      arrayTree[j].setFirstChildIndex(arrayTree.size());
      arrayTree[j].setNumberChilds(possibleMoves.size());

      for (const auto &move : possibleMoves) {
        arrayTree.emplace_back(i + 1, arrayTree[j].getMoves(), move);
        arrayTree.back().setParentIndex(j);
      }
    }
    firstChildOfLevel = lastChildOfLevel + 1;
    lastChildOfLevel = arrayTree.size() - 1;
  }
  return arrayTree;
}
