#define __LING_USING_PWM__
#include <ling.h>

void setup() {
    ling.setup();
}

void loop() {
    ling.loop();
}

void loop2() {
    loopFlag = ling.status;
    ling.loop2();
}

void end() {
    ling.stop();
}

