#ifndef __DRIVERS_BUTTON_H__
#define __DRIVERS_BUTTON_H__


/*
 * Button driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 */

#include <stdint.h>

#define _BUTTON_BASE 0x040000d0

uint32_t btn_get(void);

#endif // __DRIVERS_BUTTON_H__


