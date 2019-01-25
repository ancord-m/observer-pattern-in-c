#ifndef SPYLISTENER_H
#define SPYLISTENER_H

#include "iListener.h"

void SpyListener_Create(void);
void SpyListener_Destroy(void);
int SpyListener_GetTotalUpdateCounter(void);
void SpyListener_Update(EventType event);
iListener SpyListener_GetListener(EventType event);
iListener SpyListener_CreateListener(EventType event);

#endif /* SPYLISTENER_H */
