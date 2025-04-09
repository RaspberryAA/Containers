#ifndef RB_TREE_H
#define RB_TREE_H

#include "../s21_containers.h"
#include "nodes.h"

namespace s21 {

template <typename N, typename Compare>
class RBTree {
 private:
  std::shared_ptr<N> root;
  Compare compare_;

 public:
  RBTree() : root(nullptr) {}
  void insert(std::shared_ptr<N> node);
  std::shared_ptr<N> search(std::shared_ptr<N> node);
  bool del(std::shared_ptr<N> node);
  std::shared_ptr<N> getRoot();
  std::shared_ptr<N> nextElement(std::shared_ptr<N> node);
  std::shared_ptr<N> prevElement(std::shared_ptr<N> node);
  std::shared_ptr<N> minimum(std::shared_ptr<N> node);
  std::shared_ptr<N> maximum(std::shared_ptr<N> node);

 private:
  void rotateLeft(std::shared_ptr<N> node);
  void rotateRight(std::shared_ptr<N> node);
  void fixInsertion(std::shared_ptr<N> node);
  void fixIns1(std::shared_ptr<N> node);
  void fixIns2(std::shared_ptr<N> node);
  void transplant(std::shared_ptr<N> u, std::shared_ptr<N> v);
  void fixDeleting(std::shared_ptr<N> node);
  void fixDel1(std::shared_ptr<N> node);
  void fixDel2(std::shared_ptr<N> node);
  COLOR getNodeColor(std::shared_ptr<N> node);
};

}  // namespace s21

#include "treeImpl.tpp"

#endif