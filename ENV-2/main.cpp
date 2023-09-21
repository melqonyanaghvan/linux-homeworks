#include <iostream>
#include "complex.h"
#include "sort.h"

int main() {
    int size = 4;
    Complex_num sorting_example[size];
    sorting_example[0] = Complex_num(3, 4);
    sorting_example[1] = Complex_num(1, -2);
    sorting_example[2] = Complex_num(2, 3);
    sorting_example[3] = Complex_num(-8, 1);

  std::cout << "Not sorted - ";
     for (int i = 0; i < size-1; i++) {
        std::cout << sorting_example[i].abs_value();
        std::cout << " , ";
    } 
   std::cout << sorting_example[size-1].abs_value();
  std::cout<< std::endl;
//////////--demonstartion of sorted complex numbers--//////
    sort_complex(sorting_example,size);
    std::cout << "Sorted - ";
    for (int i = 0; i < size-1; i++) {
        std::cout << sorting_example[i].abs_value();
        std::cout << " , ";
    } 
     std::cout << sorting_example[size-1].abs_value();
//////////////////////////////////////////////////////////
    std::cout << std::endl;

    return 0;
}
