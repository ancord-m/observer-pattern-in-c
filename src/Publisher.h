/*
 * Publisher.h
 *
 *  Created on: Jul 9, 2018
 *      Author: ancord
 */

#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "iListener.h"

void Publisher_Create(int maxSubscribersQuantity);
void Publisher_Destroy(void);
void Publisher_Subscribe(EventType event, iListener subscriber);
void Publisher_Unsubscribe(EventType event, iListener subscruber);
void Publisher_Notify(EventType event);

#endif /* PUBLISHER_H_ */
