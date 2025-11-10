#ifndef __DRIVERS_SWITCH_H__
#define __DRIVERS_SWITCH_H__

/*
 * Switch driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 */

#include <stdint.h>

#define _SWITCH_BASE 0x04000010

uint32_t sw_get(void);


#endif // __DRIVERS_SWITCH_H__
