#include <iostream>

struct Visitor;
struct PrintVisitor;
struct IotaVisitor;
struct Node;
struct RedNode;
struct BlueNode;

struct Visitor {
  virtual void visit(Node *){};
  virtual void visit(RedNode *);
  virtual void visit(BlueNode *);
};

struct Node {
  int _val = 0;
  Node *_left = nullptr;
  Node *_right = nullptr;
  Node() = default;
  Node(Node *left, Node *right) : _left(left), _right(right) {}
  virtual ~Node() {
    if (_left) delete _left;
    if (_right) delete _right;
  }

  virtual void accept(Visitor &v) = 0;
  void preorder(Visitor &v) {
    accept(v);
    if (_left) _left->preorder(v);
    if (_right) _right->preorder(v);
  }
  void inorder(Visitor &v) {
    if (_left) _left->inorder(v);
    accept(v);
    if (_right) _right->inorder(v);
  }
};

struct RedNode : Node {
  RedNode() = default;
  RedNode(Node *left, Node *right) : Node(left, right) {}
  virtual void accept(Visitor &v) override { v.visit(this); }
};

struct BlueNode : Node {
  BlueNode() = default;
  BlueNode(Node *left, Node *right) : Node(left, right) {}
  virtual void accept(Visitor &v) override { v.visit(this); }
};

void Visitor::visit(RedNode *n) { visit(static_cast<Node *>(n)); }

void Visitor::visit(BlueNode *n) { visit(static_cast<Node *>(n)); }

struct PrintVisitor : Visitor {
  virtual void visit(RedNode *n) override {
    std::cout << "\033[0;31mRed:  " << n->_val << "\033[0m" << std::endl;
  }
  virtual void visit(BlueNode *n) override {
    std::cout << "\033[0;34mBlue: " << n->_val << "\033[0m" << std::endl;
  }
};

struct IotaVisitor : Visitor {
  int _cnt = 0;
  virtual void visit(Node *n) override { n->_val = ++_cnt; }
};

int main() {
  Node *root = new RedNode(new BlueNode, new BlueNode);
  IotaVisitor iv;
  root->preorder(iv);
  PrintVisitor pv;
  root->inorder(pv);

  delete root;
}