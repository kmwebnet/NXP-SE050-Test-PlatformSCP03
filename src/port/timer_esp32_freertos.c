

#include <sm_timer.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern volatile uint32_t gtimer_msticks; // counter for 1ms SysTicks


/* initializes the system tick counter
 * return 0 on succes, 1 on failure */
uint32_t sm_initSleep() {
    return 0;
}

/**
 * Implement a blocking (for the calling thread) wait for a number of milliseconds.
 */
void sm_sleep(uint32_t msec) {
    vTaskDelay(msec / portTICK_RATE_MS);
}

