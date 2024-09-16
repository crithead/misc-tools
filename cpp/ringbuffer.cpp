/// @ingroup cppexp
/// @{

#include <stdexcept>

#include "ringbuffer.hpp"

ringbuffer::ringbuffer(size_t capacity) :
	capacity(capacity), front(0), back(0), buffer(new int[capacity])
{
}

ringbuffer::~ringbuffer()
{
	if (buffer) {
		delete buffer;
		buffer = 0;
	}
}

size_t ringbuffer::size(void) const
{
	return back - front;
}

bool ringbuffer::empty(void) const
{
	return front == back;
}

bool ringbuffer::full(void) const
{
	return size() == capacity;
}

void ringbuffer::push(int n)
{
	if (!full())
		buffer[clip(back++)] = n;
}

int ringbuffer::pop(void)
{
	if (!empty())
		return buffer[clip(front++)];
	else
		throw std::runtime_error("buffer empty");
}

int ringbuffer::clip(int index) const
{
	return index % capacity;
}

//	private:
//	size_t capacity;
//	size_t front;
//	size_t back;
//	int *buffer;

#if defined(DEMO)
#include <iostream>

static void report(const ringbuffer& rb);


int main(int argc, char **argv)
{
	ringbuffer rb(5);

	const int input[8] = { 11, 22, 33, 44, 55, 66, 77, 88 };

	report(rb);

	for (int i : input) {
		std::cout << "i = " << i << std::endl;
		rb.push(i);
		report(rb);
	}

	while (!rb.empty()) {
		int j = rb.pop();
		std::cout << "j = " << j << std::endl;
		report(rb);
	}

		report(rb);
	
	return 0;
}

static void report(const ringbuffer& rb)
{
	std::cout << "--- empty = " << rb.empty() << std::endl;
	std::cout << "--- full = " << rb.full() << std::endl;
	std::cout << "--- size = " << rb.size() << std::endl;
}

#endif // DEMO

/// @}

