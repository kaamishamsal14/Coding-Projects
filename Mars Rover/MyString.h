// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
using namespace std;

class MyString {
    private:
        char *str;
        size_t strSize;
        size_t strCapacity;

    public:
    MyString(): str(nullptr), strSize(0), strCapacity(0){}
    MyString(const MyString& myStr);
    MyString(const char* cStr);
    ~MyString();
    void resize(size_t n);
    size_t capacity() const { return strCapacity;}
    size_t size() const { return strSize;}
    size_t length() const {return strSize;}

    const char* data() const noexcept;
    
    bool empty() const {return !strSize; }

    void clear();

    const char& front() const {return str[0];}
    const char& at(size_t pos) const;
    MyString& operator = (const MyString& myStr);
    MyString& operator += (const MyString& myStr);

    friend std::ostream& operator<<(std::ostream& os, const MyString& myStr)
    {
        for(size_t i = 0; i < myStr.size(); ++i)
        {
            os << myStr.at(i);
        }
        return os;
    }
    size_t find(const MyString& myStr, size_t pos = 0) const;
};
#endif