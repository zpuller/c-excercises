#include <cassert>
#include <iostream>
#include <sstream>
#include <memory>

class MyString
{
public:
  MyString() {}
  int length() const { return mLength; }
  MyString(const char* str)
  {
    for (int i = 0; str[i] != '\0'; i++)
      mLength++;

    mData = std::unique_ptr<char[]>(new char[mLength]);
    for (int i = 0; str[i] != '\0'; i++)
      mData[i] = str[i];
    
  }
  MyString(const MyString& other)
  {
    mLength = other.length();
  }
  void operator=(const MyString& other)
  {
    mLength = other.length();
  }
  bool operator==(MyString& other) { return true; }
  bool operator!=(MyString& other) { return true; }
  bool operator==(const char* other) { return true; }
  bool operator!=(const char* other) { return true; }
  bool operator<(MyString& other) { return true; }

private:
  std::unique_ptr<char[]> mData;
  int mLength = 0;
};
