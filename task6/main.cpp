#include <iostream>
#include "lazy_string.h"

using namespace std;

int main() {
    lazy_string str(string("kek\n"));
    //string s = str;
    cout << str;
    lazy_string _str = str.substr(1);
    cout << str;
    cout << _str;
    str[2] = str[0] = 'l';
    cout << str;
    cout << _str;
    cout << str[0];

    return 0;
}