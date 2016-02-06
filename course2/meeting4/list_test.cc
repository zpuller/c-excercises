#include <cassert>
#include "MyList.h"

int main()
{
  MyLinkedList<int> list;
  assert(list.size() == 0);
  list.push_front(1);
  assert(list.size() == 1);
  assert(list.front() == 1);
}
