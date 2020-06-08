#pragma once
#ifndef CSS_VALUE
#define CSS_VALUE
class Value {
  public:
    virtual ~Value()=0;
    virtual void display();
    virtual float toPX();
};
#endif