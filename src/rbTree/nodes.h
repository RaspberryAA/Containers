#ifndef NODES_H
#define NODES_H

namespace s21 {

enum COLOR { RED, BLACK };

template <typename N>
class treeNode {
 protected:
  COLOR color;
  std::shared_ptr<N> left;
  std::shared_ptr<N> right;
  std::weak_ptr<N> parent;

 public:
  treeNode() : color(COLOR::RED), left(nullptr), right(nullptr), parent() {}

  std::shared_ptr<N> getLeft() { return left; }
  std::shared_ptr<N> getRight() { return right; }
  COLOR getColor() { return color; }
  std::shared_ptr<N> getParent() { return parent.lock(); }

  void setLeft(std::shared_ptr<N> n) { left = n; }
  void setRight(std::shared_ptr<N> n) { right = n; }
  void setColor(COLOR c) { color = c; }
  void setParent(std::shared_ptr<N> n) { parent = n; }
};

}  // namespace s21

#endif
