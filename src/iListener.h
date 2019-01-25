/*
 * iListener.h
 *
 *  Created on: Jul 9, 2018
 *      Author: ancord
 */

#ifndef ILISTENER_H_
#define ILISTENER_H_

typedef enum
{
	NO_EVENT = 1,
	NEW_DATA,
	NEW_COMMAND
} EventType;

typedef struct
{
	void (*update)(EventType event);
} iListener;

#endif /* ILISTENER_H_ */
