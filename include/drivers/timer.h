#ifndef __DRIVERS_TIMER_H__
#define __DRIVERS_TIMER_H__

/*
 * Timer driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 */

#include <stdint.h>

#define _TIMER_BASE     (0x04000020)
#define _TIMER_STAT     (_TIMER_BASE)
#define _TIMER_CTRL     (_TIMER_BASE + 0x04)
#define _TIMER_PER_LO   (_TIMER_BASE + 0x08)
#define _TIMER_PER_HI   (_TIMER_BASE + 0x0C)
#define _TIMER_SNAP_LO  (_TIMER_BASE + 0x10)
#define _TIMER_SNAP_HI  (_TIMER_BASE + 0x14)

#define _TIMER_CLOCK_HZ 30000000
#define _TIMER_DEFAULT_HZ 10
#define _TIMER_DEFAULT_PERIOD ((_TIMER_CLOCK_HZ / _TIMER_DEFAULT_HZ) - 1) // 100Hz / 10ms


void timer_init(void);
void timer_disable(void);
void timer_enable(void);
uint8_t timer_get_time_out_flag(void);
void timer_clear_time_out_flag(void);
void timer_set_period(uint32_t period);
void timer_set_period_ms(uint32_t ms);
uint32_t timer_get_ticks(void);
void timer_reset_ticks(void);
void timer_increment_ticks(void);



/*
 * Timer
 * To enable the timer, call timer_init()
 *
 * To change period, you need to disable the timer, change the period, and then re-enable the timer
 */

#endif /* __DRIVERS_TIMER_H__ */
