#include <iostream>
#include <memory>

template<typename T>
struct Node
{
  T Data;
  std::unique_ptr<Node> Next;
};

template<typename T>
class MyLinkedList
{
public:
  // bare minimum:
  MyLinkedList() : mSize(0) {}
  MyLinkedList(const MyLinkedList& other) :
      mSize(other.size())
  {
    auto ptr = other.mFront.get();
    while (ptr)
    {
      push_front(ptr->Data);
      ptr = ptr->Next.get();
    }
  }
  
  void push_front(const T& element) // adds element at the front
  {
    std::unique_ptr<Node<T> > node(new Node<T>{element});
    node->Next = std::move(mFront);
    mFront = std::move(node);
    mSize++;
  }
  void pop_front() // removes element from the front
  {
    auto ptr = std::move(mFront);
    mFront = std::move(ptr->Next);
    mSize--;
  }
  std::size_t size() const { return mSize; }
  
  const T& front() const { return mFront->mData; } // read-only access to the first element
  T& front() { return mFront->mData; } ; // writeable access to the first element.
  
  // more advanced:
  void push_back(const T& element); // add at the end
  void pop_back();
  T& back();
  const T& back() const; // access to the last element
  
  // extra:
  // how would you provide access to all elements of the list?
 
private:
  std::unique_ptr<Node<T> > mFront;
  int mSize;
};
