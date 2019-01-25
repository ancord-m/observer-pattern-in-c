#include "CppUTest/TestHarness.h"

extern "C"
{
#include "SpyListener.h"
#include "Publisher.h"
}

TEST_GROUP(Publisher)
{
	void setup()
	{
		Publisher_Create(5);
		SpyListener_Create();
	}

	void teardown()
	{
		Publisher_Destroy();
		SpyListener_Destroy();
	}
};

TEST(Publisher, NoSubscibers_NoNotifications)
{
	Publisher_Notify(NEW_DATA);

	LONGS_EQUAL(0, SpyListener_GetTotalUpdateCounter());
}

TEST(Publisher, OneSubscriber_OneNotification)
{
	Publisher_Subscribe(NEW_DATA, SpyListener_CreateListener(NEW_DATA));
	Publisher_Notify(NEW_DATA);
	LONGS_EQUAL(1, SpyListener_GetTotalUpdateCounter());
}

TEST(Publisher, OneSubscriber_WrongEvent_NoNotification)
{
	Publisher_Subscribe(NEW_DATA, SpyListener_CreateListener(NO_EVENT));
	Publisher_Notify(NEW_DATA);
	LONGS_EQUAL(0, SpyListener_GetTotalUpdateCounter());
}

TEST(Publisher, TwoSubscribers_OneRightEvents_OneNotification)
{
	Publisher_Subscribe(NEW_DATA, SpyListener_CreateListener(NEW_DATA));
	Publisher_Subscribe(NEW_COMMAND, SpyListener_CreateListener(NEW_COMMAND));

	Publisher_Notify(NEW_DATA);

	LONGS_EQUAL(1, SpyListener_GetTotalUpdateCounter());
}

TEST(Publisher, ThreeSubscribers_OneUnsibscribed_TwoNotification)
{
	Publisher_Subscribe(NEW_DATA, SpyListener_CreateListener(NEW_DATA));
	Publisher_Subscribe(NEW_DATA, SpyListener_CreateListener(NEW_DATA));
	Publisher_Subscribe(NEW_DATA, SpyListener_CreateListener(NEW_DATA));

	Publisher_Unsubscribe(NEW_DATA, SpyListener_GetListener(NEW_DATA));

	Publisher_Notify(NEW_DATA);

	LONGS_EQUAL(2, SpyListener_GetTotalUpdateCounter());
}

