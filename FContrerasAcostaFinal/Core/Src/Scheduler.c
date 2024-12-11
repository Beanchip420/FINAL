/*
 * Scheduler.c
 *
 *  Created on: Sep 10, 2024
 *      Author: beanchip42
 */


#include "Scheduler.h"

static uint32_t scheduledEvents;

void addSchedulerEvent(uint32_t event)
{
	scheduledEvents |= event; // Is this what we want?
}

void removeSchedulerEvent(uint32_t event)
{
	scheduledEvents &= ~event; // Is this what we want?
}

uint32_t getScheduledEvents(void)
{
	return scheduledEvents;
}



