#include "SpyListener.h"
#include <assert.h>
#include <memory.h>

static int updateCallCounter;
static int lCount;

typedef struct
{
	int isNotified;
	EventType event;
	iListener listener;
} Listener;

static Listener *listeners;

void SpyListener_Create(void)
{
	updateCallCounter = 0;
	lCount = 0;
	listeners = (Listener *)calloc(5, sizeof(Listener));
	assert(listeners);
}

void SpyListener_Destroy(void)
{
	if(listeners)
	{
		free(listeners);
	}
}

int SpyListener_GetTotalUpdateCounter(void)
{
	return updateCallCounter;
}

void SpyListener_Update(EventType event)
{
	for(int i = 0; i < 5; i++)
	{
		if(listeners[i].event == event && !listeners[i].isNotified)
		{
			listeners[i].isNotified = 1;
			updateCallCounter++;
		}
	}
}

iListener SpyListener_GetListener(EventType event)
{
	iListener l;

	for(int i = 0; i < 5; i++)
	{
		if(listeners[i].event == event)
		{
			l = listeners[i].listener;
			listeners[i].isNotified = 0;
			break;
		}
	}

	return l;
}

iListener SpyListener_CreateListener(EventType event)
{
	listeners[lCount].event = event;
	listeners[lCount].listener.update = SpyListener_Update;
	return listeners[lCount++].listener;
}
