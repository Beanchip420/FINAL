/*
 * Scheduler.h
 *
 *  Created on: Sep 10, 2024
 *      Author: beanchip42
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include <stdint.h>

#define SHIFT_R (1 << 0) // 0th Bit
#define SHIFT_L (1 << 1) // 1st Bit

#define ROTATE_CC (1<< 2)
#define COUNT (1<<3)

#define START (1<<4)

uint32_t getScheduledEvents(void);
void addSchedulerEvent(uint32_t event);
void removeSchedulerEvent(uint32_t event);

#endif /* SCHEDULER_H_ */
