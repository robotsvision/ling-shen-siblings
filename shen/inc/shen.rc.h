#ifndef __SHEN_REMOTE_CONTROL_H__
#define __SHEN_REMOTE_CONTROL_H__

#include <shen.defs.h>

void RC_Init(void) { 
    gpio_init(SHEN_RC_GPIO_START);
    gpio_init(SHEN_RC_GPIO_KILL_SWITCH);

    gpio_set_dir(SHEN_RC_GPIO_START, GPIO_IN);
    gpio_set_dir(SHEN_RC_GPIO_KILL_SWITCH, GPIO_IN);
}


void ShenStartWaiting(void) {
    while(gpio_get(SHEN_RC_GPIO_START) != 1) {};
}

#endif // __SHEN_REMOTE_CONTROL_H__