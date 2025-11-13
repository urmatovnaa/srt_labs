#include <iostream>
#include <time.h>

static unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for(int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

void runExercise2() {
    const int iterations = 10000000;
    const int n = 10;
    
    clock_t start = clock();
    
    unsigned long long result = 0;
    for(int i = 0; i < iterations; i++) {
        result = factorial(n);
    }
    
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "Пункт 1.2:" << std::endl;
    std::cout << n << "! = " << result << std::endl;
    std::cout << "Время: " << seconds << " сек" << std::endl;
}