#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    // TODO(student): implement the UI

    string input = "";
    string lhs = "";
    string rhs = "";
    char h = '/';

    while (true) {
        cout << ">> " << endl;
        getline(cin, input);
        if (input.at(0) == 'q') {
            break;
        }
        for (uint i = 0; i < input.size(); i++) {
            if (input.at(i + 2) == '+' || input.at(i + 2) == '*')
            {
                h = input.at(i + 2);
                lhs = input.substr(0, i+1);
                rhs = input.substr((i + 4), input.size() - 1);
                break;
            }
        }
        if (h == '+') {
            cout << "ans =" << endl;
            cout << endl;
            cout << "    " << add(lhs, rhs) << endl;
            cout << endl;
        } else if (h == '*') {
            cout << "ans =" << endl;
            cout << endl;
            cout << "    " << multiply(lhs, rhs) << endl;
            cout << endl;
        }
    }
    cout << "farvel!" << endl;
    cout << endl;
}

