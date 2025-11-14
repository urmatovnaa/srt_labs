#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m;

void Func(std::string name) {
    long double i = 0;
    auto start = std::chrono::steady_clock::now();
    
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(1)) {
        i += 1e-9L;  // 10^(-9)
    }
    
    m.lock();
    std::cout << name << ": " << i << std::endl;   
    m.unlock();
}

int main() {
    std::thread thread1(Func, "t1");
    std::thread thread2(Func, "t2");
    std::thread thread3(Func, "t3");
    
    thread1.join();
    thread2.join();
    thread3.join();
    
    return 0;
}