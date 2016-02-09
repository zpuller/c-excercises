#include <list>
#include <vector>
#include <numeric>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>

#include "MyList.h"

static const int NUM = 10;

template<typename List>
void Populate(List& l)
{
  std::vector<int> v(NUM);
  std::iota(v.begin(), v.end(), 0); // fill vector with 0 .. 9
  
  // copy from vector to list
  l.clear();
  assert(l.empty());
  std::copy(v.begin(), v.end(), std::front_inserter(l));
  assert(l.size() == NUM);
}

template<typename List>
void Verify(const List& l)
{
  assert(l.size() == NUM);
  
  int first = l.front();
  int sum = std::accumulate(l.begin(), l.end(), 0);
  
  assert(first == 9);
  assert(sum == 45);
}

int main()
{
  // default constructor
  MyLinkedList<int> list;
  assert(list.size() == 0);

  // push_front
  list.push_front(1);
  assert(list.size() == 1);
  assert(list.front() == 1);

  // write access to first elem
  int& front = list.front();
  front = 5;
  assert(list.front() == 5);

  //  copy constructor
  MyLinkedList<int> list2(list);
  assert(list2.size() == 1);
  assert(list2.front() == 5);

  // pop_front
  list.pop_front();
  assert(list.size() == 0);
  list.pop_front();
  assert(list.size() == 0);

  // push_back
  list.push_back(1);
  list.push_back(2);
  assert(list.front() == 1);
  assert(list.size() == 2);

  // back
  int& back = list.back();
  assert(back == 2);
  back = 3;
  assert(list.back() == 3);

  // pop_back
  list.pop_back();
  assert(list.front() == 1);
  assert(list.size() == 1);
  list.pop_back();
  assert(list.size() == 0);
  list.pop_back();
  assert(list.size() == 0);


  // iterators
  MyLinkedList<int> l;

  Populate(l);
  Verify(l);
}
