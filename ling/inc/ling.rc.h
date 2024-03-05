#ifndef __LING_REMOTE_CONTROL_H__
#define __LING_REMOTE_CONTROL_H__

#include <ling.defs.h>

void RC_Init(void) { 
    gpio_init(LING_RC_GPIO_START);
    gpio_init(LING_RC_GPIO_STOP);

    gpio_set_dir(LING_RC_GPIO_START, GPIO_IN);
    gpio_set_dir(LING_RC_GPIO_STOP, GPIO_IN);
}


void LingStartWaiting(void) {
    while(gpio_get(LING_RC_GPIO_START) != 1) {};
}

#endif // __LING_REMOTE_CONTROL_H__