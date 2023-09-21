#include <iostream>
#include <math.h>
#include "complex.h"


Complex_num Complex_num:: operator+(const Complex_num& other){
      return Complex_num(real_number + other.real_number,img_number + other.img_number);
 };
Complex_num Complex_num:: operator-(const Complex_num& other){
      return Complex_num(real_number - other.real_number,img_number - other.img_number);
};
Complex_num Complex_num:: operator*(const int number){
      return Complex_num(real_number * number,img_number * number);
};
int Complex_num:: abs_value() const {
    return sqrt(real_number * real_number + img_number * img_number);
};

