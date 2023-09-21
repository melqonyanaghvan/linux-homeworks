#ifndef COMPLEX_INCLUDED
#define COMPLEX_INCLUDED

#include <iostream>
#include <math.h>

class Complex_num{
private:
    int real_number;
    int img_number;
     
public:
    Complex_num():real_number(0),img_number(0){};  
    Complex_num(int real, int img): real_number(real),img_number(img){};

    Complex_num operator+(const Complex_num& other);
    Complex_num operator-(const Complex_num& other);
    Complex_num operator*(const int number);
    int abs_value() const;
};
#endif