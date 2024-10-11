// TODO rework this as a template class

#ifndef MESSAGE_QUEUE_HEADER
#define MESSAGE_QUEUE_HEADER

#include <pthread.h>
#include <semaphore.h>

#include <deque>


class Message
{
public:
	Message(const char *);
	~Message();
	void *msg;
};

class MessageQueue
{
public:
	MessageQueue();
	~MessageQueue();

	Message get(void);
	void put(Message);
	int size(void) const;

private:
	sem_t message_available;
	pthread_mutex_t queue_lock;
	std::deque<Message> queue;
};

#endif /* MESSAGE_QUEUE_HEADER */

