#ifndef __DRIVERS_TIMER_H__
#define __DRIVERS_TIMER_H__

/*
 * Timer driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-11
 *
 */

#include <stdint.h>

#define _TIMER_BASE     (0x04000020)
#define _TIMER_CLOCK_HZ 30000000
#define _TIMER_DEFAULT_TICK_HZ 10
#define _TIMER_DEFAULT_PERIOD ((_TIMER_CLOCK_HZ / _TIMER_DEFAULT_TICK_HZ) - 1) // 10Hz / 100ms


/*
 * Timer Register map
 *
 * Address          | Access| 15 14 13 12 11 10 9 8 7 6 5 |  3  |  2 |  1 | 0  |
 * 0 STATUS         |  R/W  |        -RESERVED-           |     |    |RUN |TO  |
 * 1 CONTROL        |  R/W  |        -RESERVED-           |START|STOP|CONT|ITO |
 * 2 PERIOD LO      |  R/W  |     TIMEOUT PERIOD1 15:0
 * 3 PERIOD HI      |  R/W  |     TIMEOUT PERIOD1 31:16
 * 4 SNAPSHOT LO    |  R/W  |     COUNTER SNAPSHOT 15:0
 * 5 SNAPSHOT HI    |  R/W  |     COUNTER SNAPSHOT 31:16
 *
 *
 * To enable the timer, call timer_init()
 *
 * To change period, you need to disable the timer, change the period, and then re-enable the timer
 */

/*
 * Timer status register
 *
 * TO - Timeout,
 * RUN - Running,
 */
typedef struct {
    uint32_t TO : 1;       // Timeout (bit 0)
    uint32_t RUN : 1;      // Running (bit 1)
    uint32_t reserved0 : 14; // Reserved bits (bit 2-15)
    uint32_t reserved1 : 16; // Reserved bits (bit 16-31)
} status_t;


/*
 * Timer control register
 *
 * ITO - Interrupt,
 * CONT - Continuous,
 * STOP - Stop,
 * START - Start,
 */
typedef struct {
    uint32_t ITO : 1;      // Interrupt timeout (bit 0)
    uint32_t CONT : 1;     // Continuous (bit 1)
    uint32_t STOP : 1;     // Stop (bit 2)
    uint32_t START : 1;    // Start (bit 3)
    uint32_t reserved0 : 12; // Reserved bits (bit 4-15)
    uint32_t reserved1 : 16; // Reserved bits (bit 16-31)
} control_t;

/*
 * Timer structure
 *
 * Each timer has 6 16-bit registers,
 * that are 4 byte aligned
 */
typedef struct __attribute__ ((packed)) {
    volatile status_t status;        // STATUS register (2 bytes)
    volatile control_t control;      // CONTROL register (2 bytes)
    volatile uint32_t period_lo;     // PERIOD LO register (16 bits)
    volatile uint32_t period_hi;     // PERIOD HI register (16 bits)
    volatile uint32_t snap_lo;       // SNAPSHOT LO register (16 bits)
    volatile uint32_t snap_hi;       // SNAPSHOT HI register (16 bits)
} timer_t;


void timer_init(void);
void timer_disable(void);
void timer_enable(void);
uint8_t timer_get_timeout_flag(void);
void timer_clear_timeout_flag(void);
void timer_set_period(uint32_t period);
void timer_set_period_ms(uint32_t ms);
uint32_t timer_get_ticks(void);
void timer_reset_ticks(void);
void timer_increment_ticks(void);

#endif /* __DRIVERS_TIMER_H__ */
