#include "node.hpp"

void Node::addChild(Node *n) {
  children.push_back(n);
}

void Node::displayChildren() {
  std::cout << "(\n";
  for(std::vector<Node* >::size_type i = 0; i != children.size(); i++) {    
    children[i]->display();
  }
  std::cout << ")";
}

void Node::display() {
  std::cout << "Children";
  displayChildren();
  std::cout<< "\n";
}

