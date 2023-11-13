#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <chrono>
#include <string.h>

using namespace std;

void do_command(char** argv){
    auto begin = chrono::high_resolution_clock::now();
    pid_t process_id = fork();
    
    if(process_id < 0) {
      cout << "Error is found: " << strerror(errno) << endl;
      exit(errno);
    };
    
    int status;
    if(process_id == 0){
       int execute = execvp(argv[1],&argv[1]);    
       if(execute == -1){
         cout << "Error is found: " << strerror(errno) << endl;
         exit(errno);
         }
       }else{
         pid_t wait_result = waitpid(process_id, &status, 0);
         if(wait_result == -1){
            cout << "Error is found: " << strerror(errno) << endl;
            exit(errno);
         }
         auto end = chrono::high_resolution_clock::now();
         auto during = chrono::duration_cast<chrono::milliseconds>(end - begin);
         cout << "Exit status: " << WEXITSTATUS(status) << endl << "Duration of the command execution: " << during.count() << " milliseconds" << endl;
       }
    };
int main(int argc, char** argv){
    if(argc < 2){
      cout << "Error is found: " << strerror(errno) << endl;
      exit(1);
    }
    
    do_command(argv);
    return 0;
}
