#include "node.hpp"

void Node::addChild(Node *n) {
  children.push_back(n);
}

void Node::displayChildren(int level) {
  std::cout << "\n";
  for(std::vector<Node* >::size_type i = 0; i != children.size(); i++) {    
      std::cout << std::string(level, '\t');
    if (i == children.size() - 1) {
      std::cout << "└── ";
    } else {
      std::cout << "├── ";
    }
    children[i]->display(level + 1);
    if (i != children.size() - 1) {
      std::cout << "\n";
    }
  }
}

void Node::display(int level) {
  std::cout << "Children";
  displayChildren(level);
  std::cout<< "\n";
}

