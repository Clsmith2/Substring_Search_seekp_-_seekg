#ifndef GRADINGDEQUEUE
#define GRADINGDEQUEUE
#include<iostream>
#include<deque>

class GradingDeque : public std::deque<char> {
  private:
    size_t maxgrowth;
  public:
    GradingDeque() :maxgrowth(0){ }
    void push_back(const char& arg) {
      std::deque<char>::push_back(arg);
      size_t sz=std::deque<char>::size();
      maxgrowth= (sz > maxgrowth) ? sz : maxgrowth;
    }

    void push_front(const char& arg) {
      std::deque<char>::push_front(arg);
      size_t sz=std::deque<char>::size();
      maxgrowth= (sz > maxgrowth) ? sz : maxgrowth;
    }
    ~GradingDeque() { std::cerr << "Maximum deque size ---> " << maxgrowth << " <---" << std::endl; }
};
#endif