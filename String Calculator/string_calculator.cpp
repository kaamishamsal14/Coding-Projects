#include <iostream>
#include <string>
#include "./string_calculator.h"
#include <sstream>

using namespace std;
using std::cout;
using std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
int j = 0;
if ((digit == '0') || (digit == '1') || (digit == '2') || (digit == '3') || (digit == '4') || (digit == '5') || (digit == '6') || (digit == '7') || (digit == '8') || (digit == '9')) {
    std::stringstream num;
    num << digit;
    num >> j;
    if ((j >= 0) && (j <= 9)) {
        j = j;
    }
} else {
    throw std::invalid_argument("Invalid!");
}
    return j;
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    if (decimal > 9) {
        throw std::invalid_argument("Invalid!");
    } else {
        char digit = decimal + '0';
        return digit;
    }
}

string trim_leading_zeros(string num) {
    // TODO(student): implement
    for (int i = 0; i < (int)num.size(); i++) {
        if (num.at(0) == '0') {
            while (num.at(0) == '0') {
                num.erase(0, 1);
                if((int)num.size() == 0)
                {
                    return "0";
                }
                if ((int)num.size() == 1) {
                    if(num.at(0) != 0) {
                        return num;
                        break;
                    } else {
                        return "0";
                    }
                }
            }
        }
        if (num.at(0) == '-') {
            while (num.at(1) == '0') {
                num.erase(1, 1);
                if((int)num.size() == 2) {
                    if (num == "-0") {
                        return "0";
                    } else {
                        return num;
                        break;
                    }
                }
            }
        }
    }
    return num;
}

string add(string lhs, string rhs) {
    // TODO(student): implement
string zero = "", t_sum = "",d="";
  int carry = 0,temp = 0,len=0,minus=0;
  lhs=trim_leading_zeros(lhs);
  rhs=trim_leading_zeros(rhs);
  if(lhs.at(0)=='-' && rhs.at(0)=='-')
  {
      lhs=lhs.substr(1,(lhs.size()-1));
      rhs=rhs.substr(1,(rhs.size()-1));
      minus++;
  }
  if (lhs.size () < rhs.size ())
    {
      len=(rhs.size() - lhs.size());

      for (int i = 1; i <= len; i++){
	      zero += "0";
	    }
      lhs = zero + lhs;
    }
  else if (lhs.size() > rhs.size())
    {
      len=(lhs.size() - rhs.size());

      for (int i = 1; i <= len; i++){
	      zero += "0";
	    }
      rhs = zero + rhs;
    }                                
  for (int i = lhs.size() - 1; i >= 0; i--)
    {
      temp = digit_to_decimal(lhs.at(i))+ digit_to_decimal(rhs.at(i)) + carry;
      if (temp > 9 && i!=0)
      {
        std::string d=std::to_string(temp);
	    carry = digit_to_decimal(d.at(0));
	    t_sum.push_back(d.at(1));
      }
      else if (temp <= 9 && i!=0)
      {
	    carry = 0;
        t_sum.push_back(decimal_to_digit(temp));
      }
      else if (i==0 && temp<=9)
      {
      t_sum.push_back(decimal_to_digit(temp));
    }
        else if(i==0 && temp>9)
        {
           std::string d=std::to_string(temp);
            t_sum.push_back((d.at(1)));
            t_sum.push_back((d.at(0)));
        }
    }
    string sum="";
    for (int i = t_sum.size() - 1; i >= 0; i--)
    {
        sum.push_back(t_sum.at(i));
    }
    if (minus==1)
    sum= '-'+sum;
  return trim_leading_zeros(sum);
}


string multiply(string lhs, string rhs) {
    // TODO(student): implement
     string product="",d="",totalproduct="",multiply_="0",sum="";
  int carry=0,temp=0,c=0;
  lhs=trim_leading_zeros(lhs);
  rhs=trim_leading_zeros(rhs);
  if (lhs.at(0)=='-' && rhs.at(0)!='-')
  {
    product+="-";
    lhs=lhs.substr(1,(lhs.size()-1));
  }
  else if(lhs.at(0)!='-' && rhs.at(0)=='-')
  {
      product+="-";
      rhs=rhs.substr(1,(rhs.size()-1));
  }
  else if(lhs.at(0)=='-' && rhs.at(0)=='-')
  {
      product="";
    lhs=lhs.substr(1,(lhs.size()-1));
    rhs=rhs.substr(1,(rhs.size()-1));
  }
  else if(lhs.at(0)!='-' && rhs.at(0)!='-')
  {
      product="";
  }
  int len=lhs.size()-1;
  int len2=rhs.size()-1;
  for(int i=len2;i>=0;i--)
    {
      for(int j=len;j>=0;j--)
      {
        temp=digit_to_decimal(lhs.at(j))* digit_to_decimal(rhs.at(i)) + carry;
        if (temp > 9 && j!=0)
      {
        std::string d=std::to_string(temp);
	    carry = digit_to_decimal(d.at(0));
	    totalproduct.push_back(d.at(1));
      }
      else if (temp <= 9 && j!=0)
      {
	    carry = 0;
        totalproduct.push_back(decimal_to_digit(temp));
      }
      else if (j==0 && temp<=9)
      {
      totalproduct.push_back(decimal_to_digit(temp));
    }
        else if(j==0 && temp>9)
        {
           std::string d=std::to_string(temp);
            totalproduct.push_back((d.at(1)));
            totalproduct.push_back((d.at(0)));
        }
      }
    for (int l = totalproduct.size () - 1; l >= 0; l--)
    {
        sum.push_back(totalproduct.at(l));
    }
      for(int k=0;k<c;k++)
      {
          sum.push_back('0');
      }
      multiply_= add(multiply_,sum);
      totalproduct="";
      sum="";
      carry=0;
      c++;
    }
    product+=multiply_;
    return product;
}

