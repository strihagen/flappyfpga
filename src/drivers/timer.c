/* Timer
 *
 * File: timer.c
 * Author: Eric Strihagen
 * Date: 2025-11-13
 *
 * Declaration file: drivers/timer.h
 */

#include "drivers/timer.h"
#include "interrupts/isr.h"
#include "system/system.h"

#include <stdint.h>


static volatile timer_t* const TIMER = (volatile timer_t*)_TIMER_BASE;
//#define TIMER ((volatile timer_t *) _TIMER_BASE) // Becomes the same as above

/*
 * Timer Tick Counter
 * Used to count the number of timer ticks
 * The interrupt handler increments this counter every time it is called,
 * via timer_increment_ticks()
 */
static volatile uint32_t timer_ticks = 0;



/* Timer Initialization
 *
 * @brief Initialize the timer to a default period of 10 Hz / 100 ms,
 *               and enable timer interrupts, and system interrupts
*/
void timer_init() {
    timer_set_period(_TIMER_DEFAULT_PERIOD);

    timer_enable();
    system_enable_irq(INTERRUPT_TIMER_IRQ);
    system_enable_mie_interrupts();
}

/* Timer Disable
*
* @brief Stop the timer and disable timer interrupts
*/
void timer_disable() {
    // Disable interrupts, stop timer, clear timeout flag
    TIMER->control.ITO = 0;
    TIMER->control.STOP = 1;
    TIMER->status.TO = 0;
}

/* Timer Enable
*
* @brief Start the timer and enable timer interrupts
*/
void timer_enable() {
    // START timer, enable interrupt
    TIMER->control.START = 1;
    TIMER->control.ITO = 1;
}

/* Timer Get Timeout Flag
*
* @brief Get the timeout flag
* @return 1 if timeout flag is set, 0 if not
*/
uint8_t timer_get_timeout_flag() {
    return TIMER->status.TO;
}

/* Timer Clear Timeout Flag
*
* @brief Clear the timeout flag
*/
void timer_clear_timeout_flag() {
    timer_disable();
    timer_enable();
}


/* Timer Set Period
*
* @brief Set the timer period
* @param period The period to set the timer to
* @note Requires the timer to be disabled, and a conversion for CPU frequency
*/
void timer_set_period(uint32_t period) {
    TIMER->period_lo = period & 0xFFFF;
    TIMER->period_hi = (period >> 16) & 0xFFFF;
}

/* Timer Set Period ms
*
* @brief Set the timer period in milliseconds
* @param ms The period to set the timer to in milliseconds
* @note Requires the timer to be disabled
*/
void timer_set_period_ms(uint32_t ms) {
    timer_set_period(ms * (_TIMER_CLOCK_HZ / 1000));
}

/* Timer Get Ticks
*
* @brief Get the number of timer ticks
* @return The number of timer ticks
*/
uint32_t timer_get_ticks() {
    return timer_ticks;
}

/* Timer Reset Ticks
*
* @brief Reset the number of timer ticks
*/
void timer_reset_ticks() {
    timer_ticks = 0;
}

/* Timer Increment Ticks
*
* @brief Increment the number of timer ticks
*/
void timer_increment_ticks() {
    timer_ticks++;
}
