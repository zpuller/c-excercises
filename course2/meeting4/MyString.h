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
  }
  MyString(const MyString& other)
  {
    mLength = other.length();
  }
  bool operator==(MyString& other) { return true; }
  bool operator!=(MyString& other) { return true; }
  bool operator==(const char* other) { return true; }
  bool operator!=(const char* other) { return true; }
  bool operator<(MyString& other) { return true; }

private:
  int mLength = 0;
};
