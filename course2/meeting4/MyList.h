#include <iostream>
#include <memory>

template<typename T>
struct Node
{
  T Data;
  std::unique_ptr<Node> Next;
};

template<typename T>
class ListIterator
{
public:
  ListIterator(Node<T>* node) : mCurrent(node) { }
  
  T& operator*() { return mCurrent->Data; }
  void operator++() { mCurrent = mCurrent->Next.get(); }
  bool operator!=(const ListIterator& other) const
  {
    return mCurrent != other.mCurrent;
  }

private:
  Node<T>* mCurrent = nullptr;
};

template<typename T>
class MyLinkedList
{
public:
using value_type = T;
  // bare minimum:
  MyLinkedList() : mSize(0) {}
  MyLinkedList(const MyLinkedList& other) : mSize(0)
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
    if (ptr)
    {
      mFront = std::move(ptr->Next);
      mSize--;
    }
  }
  std::size_t size() const { return mSize; }
  
  const T& front() const { if (!mFront) throw; return mFront->Data; } // read-only access to the first element
  T& front() { if (!mFront) throw; return mFront->Data; } ; // writeable access to the first element.
  
  // more advanced:
  void push_back(const T& element) // add at the end
  {
    mSize++;
    std::unique_ptr<Node<T> > node(new Node<T>{element});
    if (!mFront)
    {
      mFront = std::move(node);
      return;
    }

    auto ptr = mFront.get();
    while (ptr->Next)
      ptr = ptr->Next.get();

    ptr->Next = std::move(node);
  }
  void pop_back()
  {
    if (!mFront)
      return;

    mSize--;
    if (!mFront->Next)
    {
      auto ptr = std::move(mFront);
      return;
    }

    auto ptr = mFront.get();
    while (ptr->Next->Next)
      ptr = ptr->Next.get();

    auto uptr = std::move(ptr->Next);
  }
  T& back()
  {
    if (!mFront)
      throw;

    auto ptr = mFront.get();
    while (ptr->Next)
      ptr = ptr->Next.get();

    return ptr->Data;
  }
  const T& back() const // access to the last element
  {
    if (!mFront)
      throw;

    auto ptr = mFront.get();
    while (ptr->Next)
      ptr = ptr->Next.get();

    return *ptr;
  }  
  // extra:
  // how would you provide access to all elements of the list?

  // iterators
  ListIterator<T> begin() const
  {
    return ListIterator<T>(mFront.get());
  }

  ListIterator<T> end() const
  {
    return ListIterator<T>(nullptr);
  }

  void clear() // clear list 
  {
    auto ptr = std::move(mFront);
    mSize = 0;
  }

  const bool empty() const { return mSize == 0; }
 
private:
  std::unique_ptr<Node<T> > mFront;
  int mSize;
};
