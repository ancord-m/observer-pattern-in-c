#include <assert.h>
#include "Publisher.h"

static int maxSubscribersQuantity;
static int subscribersCount;
typedef struct
{
	EventType event;
	iListener subscriber;
} Subscriber;

Subscriber *subscribers;

void Publisher_Create(int msq)
{
	assert(msq > 0);
	maxSubscribersQuantity = msq;
	subscribersCount = 0;
	subscribers = (Subscriber *) calloc(msq, sizeof(Subscriber));
	assert(subscribers);
}

void Publisher_Destroy(void)
{
	if(subscribers)
	{
		free(subscribers);
	}
}

void Publisher_Subscribe(EventType event, iListener subscriber)
{
	subscribers[subscribersCount].event = event;
	subscribers[subscribersCount].subscriber.update = subscriber.update;
	subscribersCount++;
}

void Publisher_Unsubscribe(EventType event, iListener subscriber)
{
	for(int i = 0; i < subscribersCount; i++)
	{
		if(subscriber.update== subscribers[i].subscriber.update)
		{
			subscribers[i].subscriber.update = 0;
			break;
		}
	}
	subscribersCount--;
}

void Publisher_Notify(EventType event)
{
	for(int i = 0; i < subscribersCount; i++)
	{
		if(subscribers[i].event == event)
		{
			subscribers[i].subscriber.update(event);
		}
	}
}
