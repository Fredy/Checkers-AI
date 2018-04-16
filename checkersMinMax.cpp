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

  size_t parentIndex = 0;

  for (const auto &move : possibleMoves) {
    arrayTree.emplace_back(1, arrayTree.front().getMoves(), move);
    arrayTree.back().setParentIndex(parentIndex);
  }

  auto firstChildOfLevel = arrayTree.begin() + 1;
  auto lastChildOfLevel = arrayTree.end() - 1;

  for (size_t i = 1; i < treeLevels - 1; i++) {
    for (; firstChildOfLevel <= lastChildOfLevel; firstChildOfLevel++) {
      possibleMoves = firstChildOfLevel->generateChildMoves(gameBoard, 0);
      firstChildOfLevel->setFirstChildIndex(arrayTree.size());
      firstChildOfLevel->setNumberChilds(possibleMoves.size());

      parentIndex = firstChildOfLevel - arrayTree.begin();
      for (const auto &move : possibleMoves) {
        arrayTree.emplace_back(i + 1, arrayTree.front().getMoves(), move);
        arrayTree.back().setParentIndex(parentIndex);
      }
    }
    firstChildOfLevel = lastChildOfLevel + 1;
    lastChildOfLevel = arrayTree.end() - 1;
  }
  return arrayTree;
}
