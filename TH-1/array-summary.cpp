#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <chrono>
#include <string.h>

using namespace std;

struct local_sum_arg {
    int* array;
    int begin;
    int end;
};

void* local_sum(void* arg){
    local_sum_arg* part = (local_sum_arg*) arg;
    int local_sum = 0;
    for(int i = part->begin; i < part->end; i++){
        local_sum += part->array[i];
    }

    return new int(local_sum);
}

int main(int argc, char** argv){
    if(argc < 3){
      cout << "Error is found: " << strerror(errno) << endl;
      exit(1);
    }
    
    int size = stoi(argv[1]);
    int thread_count = stoi(argv[2]);
    int* array = new int[size];
    
    for(int i = 0; i < size; i++)
    {
        array[i] = rand() ;
    }
    
    int sum = 0;
    int global_sum = 0;
    auto begin = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    
    auto end = chrono::high_resolution_clock::now();
    
    double duration_without_threads = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    
    pthread_t* threads = new pthread_t[thread_count];
    local_sum_arg** array_of_args = new local_sum_arg*[thread_count];
    
    for(int i = 0; i < thread_count; i++){
        array_of_args[i] = new local_sum_arg;
        array_of_args[i]->array = array;
        array_of_args[i]->begin = i * (size / thread_count);
        array_of_args[i]->end = min(array_of_args[i]->begin + (size / thread_count), size);
        int result = pthread_create(&threads[i], NULL, local_sum, array_of_args[i]);
        
        if(result != 0){
            cout << "Error is found: " << strerror(errno) << endl;
            exit(result);
        }
    }
    
    for(int i = 0; i < thread_count; i++){
        void* return_value;
        int result = pthread_join(threads[i], &return_value);
        int* local_sum_result = (int*)return_value;
        global_sum += *local_sum_result;
        delete local_sum_result;
        delete array_of_args[i];
    }
    
    end = chrono::system_clock::now();
    double duration_with_threads = chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    
    cout << "Time spent without threads: " << duration_without_threads << " milliseconds" << std::endl;
	cout << "Time spent with " << thread_count << " threads: " << duration_with_threads << " milliseconds" << std::endl;
    
    delete[] array_of_args;
    delete[] array;



    
    return 0;
}
