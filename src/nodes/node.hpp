#pragma once
#ifndef NODE
#define NODE
#include <vector>
#include <string>
#include <iostream>

class Node {
  public:
    std::vector<Node* > children;
    virtual void display();
    void displayChildren();
    void addChild(Node *n);
};
#endif



