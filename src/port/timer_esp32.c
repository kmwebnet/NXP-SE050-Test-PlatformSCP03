#include <sm_timer.h>
#include <stdint.h>
#include "rom/ets_sys.h"

void sm_usleep(uint32_t microsec) {
    ets_delay_us(microsec);
}
