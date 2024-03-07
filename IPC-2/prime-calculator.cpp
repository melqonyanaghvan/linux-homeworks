#include <iostream>
#include <unistd.h>
#include <cstring>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


bool prime_check(int x){
  if(x <= 1){
    return false;
  }
  for(int i = 2; i < x; i++){
    if(x % i == 0){
      return false;
    }
  }
  return true;
}

int mth_prime(int m){
  int count = 0;
  int i = 0;
  while(count < m){
    if(prime_check(i)){
      count++;
    }
    i++;
  }
  return i-1;
}

int main(){
  int pipe_first[2];
  int pipe_second[2];

  int pipe1 = pipe(pipe_first);
  if(pipe1 < 0){
      std::cerr << strerror(errno);
      exit(errno);
  }
  
  int pipe2 = pipe(pipe_second);
  if(pipe2 < 0 ){
      std::cerr << strerror(errno);
      exit(errno);
  }
  
  
  int pid = fork();
  if(pid < 0){
    std::cerr << strerror(errno);
    exit(errno);
  }


  //Parent
  if(pid > 0){
    std::string m;
    close(pipe_first[0]);
    close(pipe_second[1]);
    
    while(1){
      std::cout << "[Parent] Please enter the number: "<< std::endl;;
      std::cin >> m;

      if(m == "exit"){
        break;
      }

      int num = std::stoi(m);
      std::cout << "[Parent] Sending " << num << " to the child process" << std::endl;
      
      int write_result = write(pipe_first[1], &num , sizeof(int));
      if(write_result < 0){
          std::cerr << strerror(errno) << std::endl;
          exit(errno);
      }
      
      std::cout << "[Parent] Waiting for the response from the child process" << std::endl;
      int prime_number = 0;
      int read_result = read(pipe_second[0], &prime_number, sizeof(int));
      
      if(read_result < 0){
         std::cerr << strerror(errno) << std::endl;
         exit(errno);
      }
      std::cout << "[Parent] Received calculation result of prime(" << m << ") = " << prime_number << std::endl;
      
      
    }
  }

  //Child
  if(pid == 0){
    close(pipe_first[1]);
    close(pipe_second[0]);
    int num;
    
    while (true) {
      int read_result = read(pipe_first[0], &num, sizeof(int));  
      
      if(read_result < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
      }
      int prime_number = mth_prime(num);
      int write_result = write(pipe_second[1], &prime_number, sizeof(int));
      
      if(write_result < 0){
          std::cerr << strerror(errno) << std::endl;
          exit(errno);
      } 
    }
    
  }
  return 0;
}
