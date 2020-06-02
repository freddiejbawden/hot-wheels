#pragma once
#ifndef CSS_SELECTOR
#define CSS_SELECTOR

#include <vector>

class Selector {
  public:
    virtual ~Selector()=0;
    virtual void display();
    virtual  std::vector<int> getSpecificity();
};

#endif
