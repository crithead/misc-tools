#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cstdlib>

class ringbuffer
{
public:
	ringbuffer(size_t capacity);
	~ringbuffer();
	size_t size(void) const;
	bool empty(void) const;
	bool full(void) const;
	void push(int);
	int pop(void);
protected:
	int clip(int) const;
private:
	size_t capacity;
	size_t front;
	size_t back;
	int *buffer;
};

#endif // RING_BUFFER_H


