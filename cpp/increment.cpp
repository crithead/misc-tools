// C++11 Thread & Mutex exercise
//  g++ -Wall increment.cpp -o incr -std=c++11 -lpthread

#include <iostream>
#include <mutex>
#include <thread>

// Mutex shared by all threads
std::mutex m;

int value = 0;

void incr(int number, int increment, bool use_lock)
{
	volatile int temp;

	for (int j = 0; j < number; j++) {
		if (use_lock)
			m.lock();
		temp = value;
		temp = temp + increment;
		value = temp;
		if (use_lock)
			m.unlock();
	}

	std::cout << "incr value by " << number * increment << std::endl;
}

int main(void)
{
	value = 0;
	std::cout << "with mutex" << std::endl;
	std::cout << "initial value = " << value << std::endl;

	std::thread ctr1(incr, 1000000, 2, true);
	std::thread ctr2(incr, 1000000, 2, true);

	ctr1.join();
	ctr2.join();

	std::cout << "final value = " << value << std::endl;

	value = 0;
	std::cout << "without mutex" << std::endl;
	std::cout << "initial value = " << value << std::endl;

	std::thread ctr3(incr, 1000000, 2, false);
	std::thread ctr4(incr, 1000000, 2, false);

	ctr3.join();
	ctr4.join();

	std::cout << "final value = " << value << std::endl;

	return 0;
}
