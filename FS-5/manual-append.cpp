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
   int op =  open(file_name, O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
   
   if(op < 0){
     std::cerr<< errno << strerror(errno);
     exit(errno);
    }
    
   int desc_new = 0;
   int dup = dup2(op,desc_new);
   
   if(dup < 0){
     std::cerr<< errno << strerror(errno);
     exit(errno);
    }
       
   std::string one = "first line\n" ;// size is 11
   std::string two = "second line\n"; //size is 12
   write(op,one.c_str(),11);
   write(dup,two.c_str(),12);
   
   close(op);
   close(dup);
}
