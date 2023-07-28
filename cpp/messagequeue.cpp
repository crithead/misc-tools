//
//
//

#include "messagequeue.h"


Message::Message(const char *);
Message::~Message();
void *Message::msg;


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

