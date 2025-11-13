#include <iostream>
#include "exercise1.h"
#include "exercise2.h"
#include "exercise3.h"

void runWarmup();

int main() {
    runWarmup();
    std::cout << std::endl;
    
    runExercise2();
    std::cout << std::endl;
    
    runExercise3();
    
    return 0;
}