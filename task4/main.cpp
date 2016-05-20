//
// Created by aydar on 17.05.16.
//
#include <iostream>
#include "format.h"

using namespace std;

int main() {
    /*char cs[] = "kekkek";
    std::string s = format("%s", cs);
    cout << s;*/

    //printf("#%010s#\n", "kek");
    //cout << format("#%010s#\n", "kek");

    /*cout << format("Characters: %c %c \n", 'a', 'b');
    printf("Characters: %c %c \n", 'a', 'b');
    cout << format("Decimals: %d %ld\n", 1977, 650000L);
    printf("Decimals: %d %ld\n", 1977, 650000L);
    cout << format("Preceding with blanks: %10d \n", 1977);
    printf("Preceding with blanks: %10d \n", 1977);
    cout << format("Preceding with zeros: %010d \n", 1977);
    printf("Preceding with zeros: %010d \n", 1977);
    cout << format("Some different radices: %d %x %o %#x %#o \n", 100, 100U, 100U, 100U, 100U);
    printf("Some different radices: %d %x %o %#x %#o \n", 100, 100U, 100U, 100U, 100U);*/
    cout << format("floats: %07.2f %+.0e %f \n", 3.1416, 3.1416, 1e-9);
    printf("floats: %07.2f %+.0e %f \n", 3.1416, 3.1416, 1e-9);
    /*cout << format("Width trick: %*d \n", 5, 10);
    printf("Width trick: %*d \n", 5, 10);
    cout << format("%s \n", "A string");
    printf("%s \n", "A string");*/
    /*char s[1000];
    double d = 1e309;
    printf("%f", d);*/
    //formatRealizationTwoExtAr(std::string(""), 1, 1, 1, 1, 1);
}