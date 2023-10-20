#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv) {
    if(argc < 3) {
        std::cerr << "Error: Some paths are not given" << std::endl;
        exit(1);
    }
    char* source_path = argv[1];
    char* destination_path = argv[2];
    int source_file = open(source_path, O_RDONLY);
    int destination_file = open(destination_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if(source_file < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
      }
    if(destination_file < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
      }
    int buffer_size = 100;
    char* buffer = new char[buffer_size + 1];

    int read_bytes = 0;
    int write_bytes = 0;
    while(true) {
        read_bytes = read(source_file, buffer, buffer_size);
        if(read_bytes < 0) {
           std::cerr << strerror(errno) << std::endl;
           exit(errno);
          }
        if(read_bytes == 0) {
           break;
          }
        write_bytes = write(destination_file, buffer, read_bytes);
        if(write_bytes < 0) {
           std::cerr << strerror(errno) << std::endl;
           exit(errno);
        }
    }
    close(source_file);
    close(destination_file);
}
