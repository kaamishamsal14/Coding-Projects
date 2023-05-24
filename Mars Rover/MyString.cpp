// TODO: Implement this source file
#include "MyString.h"
#include <iostream>
using namespace std;

MyString::MyString(const MyString& myStr): str(), strSize(), strCapacity(){
    strSize = myStr.size();
    strCapacity = myStr.size() + 1;

    str = new char[strCapacity];

    for(size_t i = 0; i < strSize; ++i)
    {
        str[i] = myStr.at(i);
    }
    str[strSize] =  '\0';
}

MyString::MyString(const char* cStr): str(), strSize(), strCapacity()
{
    size_t i = 0;
    while (cStr[i]){
        i++;
    }
    strSize = i;
    strCapacity = i + 1;
    str = new char[strCapacity];
    for(size_t i = 0; i < strSize; ++i)
    {
        str[i] = cStr[i];
    }
    str[strSize] = '\0';
}

MyString::~MyString()
{
    if(str)
    {
        delete[] str;
        str = nullptr;
    }
}

void MyString::resize(size_t n)
{
    char *resizedStr = new char[n];
    for(size_t i = 0; i < n; ++i)
    {
        if(i < strSize)
        {
            resizedStr[i] = str[i];
        }
        else{
            resizedStr[i] = '\0';
        }
    }

    if(n < strSize)
    {
        strSize = n;
    }

    strCapacity = n;
    delete[] str;
    str = resizedStr;
}

const char* MyString::data() const noexcept
{
    return str;
}

void MyString::clear(){
    //str[0] = '\0';
    strSize = 0;
    strCapacity = 0;
    //delete[] str;
    //str = nullptr;
    
    
}

const char& MyString::at(size_t pos) const
{
    if(pos >= strSize)
    {
        throw std::out_of_range("position iis out of bounds of MyString");
    }

    return str[pos];
}

MyString& MyString::operator = (const MyString& myStr)
{
    this-> clear();

    strSize = myStr.size();
    strCapacity = myStr.size() + 1;
    str = new char[strCapacity];
    for(size_t i = 0; i < strSize; ++i)
    {
        str[i] = myStr.at(i);
    }
    str[strSize] = '\0';

    return *this;
}

MyString& MyString::operator += (const MyString& myStr)
{
    this->resize(strSize + myStr.capacity());

    for(size_t i = 0; i < myStr.size(); ++i)
    {
        str[strSize + i] = myStr.at(i);
    }
    strSize += myStr.size();
    return *this;
}

size_t MyString::find(const MyString& myStr, size_t pos) const
{
    size_t charMatches = 0;
    for(size_t i = pos; i < strSize; ++i)
    {
        if(charMatches == myStr.size())
        {
            return i - charMatches;
        }
        else if(str[i] == myStr.at(charMatches))
        {
            charMatches++;

        }
        else{

            charMatches = 0;
        }
    }
    return -1;
}