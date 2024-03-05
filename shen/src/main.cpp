#define __SHEN_USING_PWM__
#include <shen.h>

int main (void) {
    shen.setup();
    while (shen.status) {
        shen.loop2();
        shen.loop();
    }
}