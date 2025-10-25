#ifndef __DRIVERS_BUTTON_H__
#define __DRIVERS_BUTTON_H__


/*
 * Button driver
 *
 * Author: Eric Strihagen
 * Date: 2025-10-25
 *
 */


#define _BUTTON_BASE 0x040000d0

int get_btn(void);

#endif // __DRIVERS_BUTTON_H__


