/// How to time a function in C++17.

#include <chrono>
#include <iostream>
#include <thread>

/// A function that takes some time to execute (so it can be timed).
static void LongRunningFunction() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

/// Time a function and print the duration in milliseconds.
int main() {
    // Start timing
    auto t1 = std::chrono::high_resolution_clock::now();

    // Call the long-running function
    LongRunningFunction();

    // End timing
    auto t2 = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    // Calculate the duration in microseconds
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "LongRunningFunction took " << duration_ms << " milliseconds." << std::endl;
    std::cout << "LongRunningFunction took " << duration_us << " microseconds." << std::endl;

    return 0;
}
