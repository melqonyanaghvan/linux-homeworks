#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc,char **argv){
    if(argc < 2){
    std::cerr << "Error is found: file path is not given"<< std::endl;
    exit(1);
   }
   char* file_name = argv[1];
   int buffer_size = 10;
   int op =  open(file_name, O_WRONLY);
   
   if(op < 0){
     std::cerr<< errno << strerror(errno);
     exit(errno);
    }
  
   char* buffer = new char[buffer_size +1];
   for(int i = 0; i< buffer_size ;i++){
      buffer[i] ='\0';
    }
  
   struct stat b_stat;
   int info_file = stat(file_name, &b_stat);
   if(info_file  < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(1);
    }
   int count = 0;
   int size = b_stat.st_size;
   while(count < size ){
    int write_bytes = write(op, buffer, buffer_size);
    if(write_bytes < 0){
     std::cerr<< errno << strerror(errno);
     exit(errno);
    }    
    count = count + write_bytes;
   }
   
  int delete_file = unlink(file_name);
  if(delete_file < 0){
     std::cerr << strerror(errno) << std::endl;
     exit(1);
    }else{
    std::cout << "File is removed" << std::endl;
   }
  delete[] buffer;
}
