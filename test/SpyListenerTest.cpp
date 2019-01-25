#include "CppUTest/TestHarness.h"

extern "C"
{
#include "SpyListener.h"
}

TEST_GROUP(SpyListener)
{
	void setup()
	{
		SpyListener_Create();
	}

	void teardown()
	{
		SpyListener_Destroy();
	}
};

TEST(SpyListener, SpyWasNotUpdatedNotificationCounterZero)
{
	LONGS_EQUAL(0, SpyListener_GetTotalUpdateCounter());
}

TEST(SpyListener, SpyWasUpdatedOnceNotificationCounterOne)
{
	iListener listener = SpyListener_CreateListener(NO_EVENT);

	SpyListener_Update(NO_EVENT);

	LONGS_EQUAL(1, SpyListener_GetTotalUpdateCounter());
}

TEST(SpyListener, OneListener_WrongEvent_ZeroNotifications)
{
	iListener listener  = SpyListener_CreateListener(NEW_COMMAND);

	SpyListener_Update(NO_EVENT);

	LONGS_EQUAL(0, SpyListener_GetTotalUpdateCounter());
}

TEST(SpyListener, OneListener_RightEvent_OneNotification)
{
	iListener listener = SpyListener_CreateListener(NEW_COMMAND);

	SpyListener_Update(NEW_COMMAND);

	LONGS_EQUAL(1, SpyListener_GetTotalUpdateCounter());
}

TEST(SpyListener, TwoListeners_RightEvents_TwoNotifications)
{
	iListener l1 = SpyListener_CreateListener(NEW_COMMAND);
	iListener l2 = SpyListener_CreateListener(NEW_COMMAND);

	SpyListener_Update(NEW_COMMAND);

	LONGS_EQUAL(2, SpyListener_GetTotalUpdateCounter());
}

TEST(SpyListener, TwoListeners_DiffRightEvents_TwoNotifications)
{
	iListener l1 = SpyListener_CreateListener(NEW_COMMAND);
	iListener l2 = SpyListener_CreateListener(NEW_DATA);

	SpyListener_Update(NEW_COMMAND);
	SpyListener_Update(NEW_DATA);

	LONGS_EQUAL(2, SpyListener_GetTotalUpdateCounter());
}

TEST(SpyListener, TwoListeners_OneRightEvents_OneNotifications)
{
	iListener l1 = SpyListener_CreateListener(NEW_COMMAND);
	iListener l2 = SpyListener_CreateListener(NEW_DATA);


	SpyListener_Update(NEW_DATA);

	LONGS_EQUAL(1, SpyListener_GetTotalUpdateCounter());
}
