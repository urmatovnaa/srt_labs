#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <time.h>

std::mutex cout_mutex;

static unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for(int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

void Func(std::string name) {
    const int iterations = 10000000;
    
     unsigned long long result = 0;
    for(int i = 0; i < iterations; i++) {
        result += factorial(10);
    }
    
    cout_mutex.lock();
    cout_mutex.unlock();
}

void runExercise3() {    
    // Параллельное выполнение
    clock_t start_parallel = clock();
    
    std::thread thread1(Func, "t1");
    std::thread thread2(Func, "t2");
    thread1.join();
    thread2.join();
    
    clock_t end_parallel = clock();
    double seconds_parallel = (double)(end_parallel - start_parallel) / CLOCKS_PER_SEC;
    
    // Последовательное выполнение  
    clock_t start_sequential = clock();
    
    Func("seq1");
    Func("seq2");
    
    clock_t end_sequential = clock();
    double seconds_sequential = (double)(end_sequential - start_sequential) / CLOCKS_PER_SEC;
    
    std::cout << "Пункт 1.3:" << std::endl;
    std::cout << "Параллельно: " << seconds_parallel << " сек" << std::endl;
    std::cout << "Последовательно: " << seconds_sequential << " сек" << std::endl;
    std::cout << "Ускорение: " << seconds_sequential / seconds_parallel << " раз" << std::endl;
}