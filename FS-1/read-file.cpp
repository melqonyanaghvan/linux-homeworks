#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int main(int argc, char** argv){
  if(argc < 2){
    std::cerr << "Error is found: file path is not given"<< std::endl;
    exit(1);
  }
  
  char* file_name = argv[1];
  int buffer_size = 10;
  int op =  open(file_name, O_RDONLY);
  
  if(op < 0){
     std::cerr<< errno << strerror(errno);
     exit(errno);
    }
  char* buffer = new char[buffer_size + 1];
  while(true){
     int read_bytes = read(op, buffer, buffer_size);
     if(read_bytes < 0){
         std::cerr<< strerror(errno);
         exit(errno);
      }
        if(read_bytes == 0){
                break;
        }

      buffer[read_bytes] = '\0';
      std::cout<< buffer;
    }
  int close_num = close(op);
  if(close_num < 0) {
     std::cerr<< errno << strerror(errno);
     exit(errno);
   }    
    delete[] buffer;
}
