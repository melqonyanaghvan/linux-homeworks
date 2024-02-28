#include <iostream>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ucontext.h>
#include <signal.h>
#include <pwd.h>

void sigusr_handler(int sig, siginfo_t* info, void* context){
    pid_t pid = info->si_pid;
    uid_t uid = info->si_uid;
  
    struct passwd* _info = getpwuid(uid);
    char* username = _info->pw_name;

    ucontext_t* _context = (ucontext_t*)context;
    int EIP = _context->uc_mcontext.gregs[REG_RIP];
    int EAX = _context->uc_mcontext.gregs[REG_RAX];
    int EBX = _context->uc_mcontext.gregs[REG_RBX];

    std::cout << "Received a SIGUSR1 signal from process " << pid << " executed by " << uid << " " << username <<std::endl;
    std::cout << "State of the context: EIP = "<< EIP << ", EAX = "<< EAX << ", EBX = " << EBX << std::endl; 
}

int main() {
    struct sigaction sig_action;
    memset(&sig_action, 0, sizeof(sig_action));
    action.sa_sigaction = sigusr_handler;
    action.sa_flags = SA_SIGINFO;

    int res = sigaction(SIGUSR1, &sig_action, NULL);
    
    if (res < 0){
      std::cerr << strerror(errno) << std::endl;
    }
    
    while(true){
      sleep(10);
    }
}
