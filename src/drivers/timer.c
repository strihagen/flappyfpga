/* Timer
 *
 * File: timer.c
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * Declaration file: drivers/timer.h
 */

#include "drivers/timer.h"
#include "interrupts/isr.h"


#include <stdint.h>

volatile uint8_t* TMR_STAT = (volatile uint8_t*)_TIMER_STAT;
volatile uint8_t* TMR_CTRL = (volatile uint8_t*)_TIMER_CTRL;
volatile uint8_t* TMR_PER_LO = (volatile uint8_t*)_TIMER_PER_LO;
volatile uint8_t* TMR_PER_HI = (volatile uint8_t*)_TIMER_PER_HI;

static volatile uint32_t timer_ticks = 0;

void timer_init() {
    uint32_t period = _TIMER_DEFAULT_PERIOD;  // 10 Hz / 100 ms
    *TMR_PER_LO = period & 0xFFFF;
    *TMR_PER_HI = (period >> 16) & 0xFFFF;

    timer_enable();
    enable_interrupts();
}

void timer_disable() {
    *TMR_CTRL = 0x0;
    *TMR_STAT = 0x0;
}

void timer_enable() {
    // START timer, enable interrupt
    *TMR_CTRL = 0x5;
}

uint8_t timer_get_time_out_flag() {
    return (*TMR_STAT & 0x1);
}

void timer_clear_time_out_flag() {
    timer_disable();
    timer_enable();
}

void timer_set_period(uint32_t period) {
    *TMR_PER_LO = period & 0xFFFF;
    *TMR_PER_HI = (period >> 16) & 0xFFFF;
}

void timer_set_period_ms(uint32_t ms) {
    timer_set_period(ms * (_TIMER_CLOCK_HZ / 1000));
}
uint32_t timer_get_ticks() {
    return timer_ticks;
}

void timer_reset_ticks() {
    timer_ticks = 0;
}

void timer_increment_ticks() {
    timer_ticks++;
}
