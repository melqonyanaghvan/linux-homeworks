#include "sort.h"

void sort_complex(Complex_num arr[], int size) {
    for (int i= 0;i < size-1; i++) {
        for (int j= 0; j < size-i-1; j++) {
            if (arr[j].abs_value() > arr[j+1].abs_value()) {
                Complex_num temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
           }
        }
   }
}
