#include "rbTree.h"

using namespace s21;

template <typename N, typename Compare>
void RBTree<N, Compare>::insert(std::shared_ptr<N> node) {
  std::shared_ptr<N> x = root;
  std::shared_ptr<N> y = nullptr;
  while (x != nullptr) {
    y = x;
    if (compare_(node->getKey(), x->getKey())) {
      x = x->getLeft();
    } else {
      x = x->getRight();
    }
  }
  node->setParent(y);
  if (y == nullptr) {
    root = node;
  } else if (compare_(y->getKey(), node->getKey())) {
    y->setRight(node);
  } else {
    y->setLeft(node);
  }
  fixInsertion(node);
}

template <typename N, typename Compare>
void RBTree<N, Compare>::rotateLeft(std::shared_ptr<N> node) {
  std::shared_ptr<N> p = node->getRight();
  node->setRight(p->getLeft());
  if (p->getLeft() != nullptr) {
    p->getLeft()->setParent(node);
  }
  p->setParent(node->getParent());
  if (node->getParent() == nullptr) {
    root = p;
  } else if (node == node->getParent()->getLeft()) {
    node->getParent()->setLeft(p);
  } else if (node == node->getParent()->getRight()) {
    node->getParent()->setRight(p);
  }
  p->setLeft(node);
  node->setParent(p);
}

template <typename N, typename Compare>
void RBTree<N, Compare>::rotateRight(std::shared_ptr<N> node) {
  std::shared_ptr<N> p = node->getLeft();
  node->setLeft(p->getRight());
  if (p->getRight() != nullptr) {
    p->getRight()->setParent(node);
  }
  p->setParent(node->getParent());
  if (node->getParent() == nullptr) {
    root = p;
  } else if (node == node->getParent()->getRight()) {
    node->getParent()->setRight(p);
  } else if (node == node->getParent()->getLeft()) {
    node->getParent()->setLeft(p);
  }
  p->setRight(node);
  node->setParent(p);
}

template <typename N, typename Compare>
void RBTree<N, Compare>::fixInsertion(std::shared_ptr<N> node) {
  while (this->getNodeColor(node->getParent()) == COLOR::RED) {
    if (node->getParent() == node->getParent()->getParent()->getLeft()) {
      fixIns1(node);
    } else if (node->getParent() ==
               node->getParent()->getParent()->getRight()) {
      fixIns2(node);
    }
  }
  root->setColor(COLOR::BLACK);
}

template <typename N, typename Compare>
void RBTree<N, Compare>::fixIns1(std::shared_ptr<N> node) {
  std::shared_ptr<N> u = node->getParent()->getParent()->getRight();
  if (this->getNodeColor(u) == COLOR::RED) {
    node->getParent()->setColor(COLOR::BLACK);
    u->setColor(COLOR::BLACK);
    node->getParent()->getParent()->setColor(COLOR::RED);
    node = node->getParent()->getParent();
  } else {
    if (node == node->getParent()->getRight()) {
      node = node->getParent();
      rotateLeft(node);
    }
    node->getParent()->setColor(COLOR::BLACK);
    node->getParent()->getParent()->setColor(COLOR::RED);
    rotateRight(node->getParent()->getParent());
  }
}

template <typename N, typename Compare>
void RBTree<N, Compare>::fixIns2(std::shared_ptr<N> node) {
  std::shared_ptr<N> u = node->getParent()->getParent()->getLeft();
  if (this->getNodeColor(u) == COLOR::RED) {
    node->getParent()->setColor(COLOR::BLACK);
    u->setColor(COLOR::BLACK);
    node->getParent()->getParent()->setColor(COLOR::RED);
    node = node->getParent()->getParent();
  } else {
    if (node == node->getParent()->getLeft()) {
      node = node->getParent();
      rotateRight(node);
    }
    node->getParent()->setColor(COLOR::BLACK);
    node->getParent()->getParent()->setColor(COLOR::RED);
    rotateLeft(node->getParent()->getParent());
  }
}

template <typename N, typename Compare>
std::shared_ptr<N> RBTree<N, Compare>::search(std::shared_ptr<N> node) {
  std::shared_ptr<N> p = root;
  while (p != nullptr && p->getKey() != node->getKey()) {
    if (compare_(p->getKey(), node->getKey())) {
      p = p->getRight();
    } else {
      p = p->getLeft();
    }
  }
  return p;
}

template <typename N, typename Compare>
std::shared_ptr<N> RBTree<N, Compare>::minimum(std::shared_ptr<N> node) {
  while (node != nullptr && node->getLeft() != nullptr) {
    node = node->getLeft();
  }
  return node;
}

template <typename N, typename Compare>
std::shared_ptr<N> RBTree<N, Compare>::maximum(std::shared_ptr<N> node) {
  while (node != nullptr && node->getRight() != nullptr) {
    node = node->getRight();
  }
  return node;
}

template <typename N, typename Compare>
void RBTree<N, Compare>::transplant(std::shared_ptr<N> u,
                                    std::shared_ptr<N> v) {
  if (u->getParent() == nullptr)
    root = v;
  else if (u == u->getParent()->getLeft())
    u->getParent()->setLeft(v);
  else
    u->getParent()->setRight(v);
  if (v != nullptr) {
    v->setParent(u->getParent());
    v->setColor(this->getNodeColor(u));
  }
}

template <typename N, typename Compare>
bool RBTree<N, Compare>::del(std::shared_ptr<N> node) {
  bool ret = false;
  node = search(node);
  if (node != nullptr) {
    ret = true;
    std::shared_ptr<N> y = node;
    std::shared_ptr<N> x = nullptr;
    COLOR yOriginalColor = this->getNodeColor(y);
    if (node->getLeft() == nullptr) {
      x = node->getRight();
      transplant(node, node->getRight());
    } else if (node->getRight() == nullptr) {
      x = node->getLeft();
      transplant(node, node->getLeft());
    } else {
      y = minimum(node->getRight());
      yOriginalColor = this->getNodeColor(y);
      x = y->getRight();
      if (y->getParent() == node) {
        if (x != nullptr) {
          x->setParent(y);
        }
      } else {
        transplant(y, y->getRight());
        y->setRight(node->getRight());
        if (y->getRight() != nullptr) {
          y->getRight()->setParent(y);
        }
      }
      transplant(node, y);
      y->setLeft(node->getLeft());
      if (y->getLeft() != nullptr) {
        y->getLeft()->setParent(y);
      }
      y->setColor(this->getNodeColor(node));
    }
    if (x != nullptr && yOriginalColor == COLOR::BLACK) {
      fixDeleting(x);
    }
    node = nullptr;
  }
  return ret;
}

template <typename N, typename Compare>
void RBTree<N, Compare>::fixDeleting(std::shared_ptr<N> node) {
  while (node != root && this->getNodeColor(node) == COLOR::BLACK) {
    if (node == node->getParent()->getLeft() &&
        node->getParent()->getRight() != nullptr) {
      fixDel1(node);
    } else if (node->getParent()->getLeft() != nullptr) {
      fixDel2(node);
    }
  }
  node->setColor(COLOR::BLACK);
}

template <typename N, typename Compare>
void RBTree<N, Compare>::fixDel1(std::shared_ptr<N> node) {
  std::shared_ptr<N> b = node->getParent()->getRight();
  if (this->getNodeColor(b) == COLOR::RED) {
    b->setColor(COLOR::BLACK);
    node->getParent()->setColor(COLOR::RED);
    rotateLeft(node->getParent());
    b = node->getParent()->getRight();
  } else if (this->getNodeColor(b->getLeft()) == COLOR::BLACK &&
             this->getNodeColor(b->getRight()) == COLOR::BLACK) {
    b->setColor(COLOR::RED);
    node = node->getParent();
  } else if (this->getNodeColor(b->getRight()) == COLOR::BLACK) {
    b->getLeft()->setColor(COLOR::BLACK);
    b->setColor(COLOR::RED);
    rotateRight(b);
    b = node->getParent()->getRight();
  } else {
    b->setColor(this->getNodeColor(node->getParent()));
    node->getParent()->setColor(COLOR::BLACK);
    b->getRight()->setColor(COLOR::BLACK);
    rotateLeft(node->getParent());
    node = root;
  }
}

template <typename N, typename Compare>
void RBTree<N, Compare>::fixDel2(std::shared_ptr<N> node) {
  std::shared_ptr<N> b = node->getParent()->getLeft();
  if (this->getNodeColor(b) == COLOR::RED) {
    b->setColor(COLOR::BLACK);
    node->getParent()->setColor(COLOR::RED);
    rotateRight(node->getParent());
    b = node->getParent()->getLeft();
  } else if (this->getNodeColor(b->getRight()) == COLOR::BLACK &&
             this->getNodeColor(b->getLeft()) == COLOR::BLACK) {
    b->setColor(COLOR::RED);
    node = node->getParent();
  } else if (this->getNodeColor(b->getLeft()) == COLOR::BLACK) {
    b->getRight()->setColor(COLOR::BLACK);
    b->setColor(COLOR::RED);
    rotateLeft(b);
    b = node->getParent()->getLeft();
  } else {
    b->setColor(this->getNodeColor(node->getParent()));
    node->getParent()->setColor(COLOR::BLACK);
    b->getLeft()->setColor(COLOR::BLACK);
    rotateRight(node->getParent());
    node = root;
  }
}

template <typename N, typename Compare>
std::shared_ptr<N> RBTree<N, Compare>::getRoot() {
  return root;
}

template <typename N, typename Compare>
std::shared_ptr<N> RBTree<N, Compare>::prevElement(std::shared_ptr<N> node) {
  if (node->getLeft() != nullptr) {
    node = maximum(node->getLeft());
  } else {
    std::shared_ptr<N> parent = node->getParent();
    while (parent != nullptr && node == parent->getLeft()) {
      node = parent;
      parent = parent->getParent();
    }
    node = parent;
  }
  return node;
}

template <typename N, typename Compare>
std::shared_ptr<N> RBTree<N, Compare>::nextElement(std::shared_ptr<N> node) {
  if (node->getRight() != nullptr) {
    node = minimum(node->getRight());
  } else {
    std::shared_ptr<N> parent = node->getParent();
    while (parent != nullptr && node == parent->getRight()) {
      node = parent;
      parent = parent->getParent();
    }
    node = parent;
  }
  return node;
}

template <typename N, typename Compare>
COLOR RBTree<N, Compare>::getNodeColor(std::shared_ptr<N> node) {
  COLOR c = COLOR::BLACK;
  if (node != nullptr) {
    c = node->getColor();
  }
  return c;
}
