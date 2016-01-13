#include <cassert>
#include <iostream>
#include <sstream>
#include <memory>

class MyString
{
public:
  MyString() {}

  MyString(const char* str)
  {
    mLength = std::strlen(str);
    mData = std::unique_ptr<char[]>(new char[mLength + 1]);
    std::strcpy(data(), str);
  }

  MyString(const MyString& other)
  {
    mLength = other.length();
    mData = std::unique_ptr<char[]>(new char[mLength + 1]);
    std::strcpy(data(), other.data());
  }

  MyString& operator=(const MyString& other)
  {
    if (this != &other)
    {
      mLength = other.length();
      mData.reset(new char[mLength + 1]);
      std::strcpy(data(), other.data());
    }

    return *this;
  }

  char& operator[](std::size_t i) { return mData.get()[i]; }

  bool operator==(MyString& other) { return !std::strcmp(data(), other.data()); }
  bool operator==(const char* other) { return !std::strcmp(data(), other); }
  bool operator!=(MyString& other) { return !(*this == other); }
  bool operator!=(const char* other) { return !(*this == other); }

  bool operator<(MyString& other)
  {
    for (int i = 0; i < mLength; i++)
    {
      if (mData[i] < other.data()[i])
        return true;

      if (mData[i] > other.data()[i])
        return false;
    }

    return (mLength < other.length());
  }

  friend std::ostream& operator<<(std::ostream& os, MyString& string)
  {
    os << string.data();
    return os;
  }

  MyString operator+(MyString& other)
  {
    char oString[mLength + other.mLength + 1];
    std::strcpy(oString, data());
    std::strcat(oString, other.data());
    return MyString(oString);
  }

  MyString& operator+=(MyString& other)
  {
    char oString[mLength + other.mLength + 1];
    std::strcpy(oString, data());
    std::strcat(oString, other.data());

    mLength += other.mLength;
    mData.reset(new char[mLength + 1]);
    std::strcpy(data(), oString);

    return *this;
  }

  int length() const { return mLength; }
  char* data() const { return mData.get(); }

private:
  std::unique_ptr<char[]> mData;
  int mLength = 0;
};
