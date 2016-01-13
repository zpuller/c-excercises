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
    for (int i = 0; str[i] != '\0'; i++)
      mLength++;

    mData = std::unique_ptr<char[]>(new char[mLength + 1]);
    for (int i = 0; str[i] != '\0'; i++)
      mData[i] = str[i];

    mData[mLength] = '\0';
  }

  MyString(const MyString& other)
  {
    mLength = other.length();
    mData = std::unique_ptr<char[]>(new char[mLength + 1]);
    std::copy(other.data(), other.data() + mLength + 1, mData.get());
  }

  MyString& operator=(const MyString& other)
  {
    if (this != &other)
    {
      mLength = other.length();
      mData.reset(new char[mLength + 1]);
      std::copy(other.data(), other.data() + mLength + 1, mData.get());
    }

    return *this;
  }

  char& operator[](std::size_t i) { return mData.get()[i]; }

  bool operator==(MyString& other) 
  { 
    if (mLength != other.length())
      return false;

    for (int i = 0; i < mLength; i++)
    {
      if (mData[i] != other.data()[i])
        return false;
    }

    return true;
  }

  bool operator==(const char* other) 
  {
    int i = 0;
    for (; i < mLength; i++)
      if (mData[i] != other[i])
        return false;

    if (other[i] != '\0')
      return false;

    return true;
  }

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
