#ifndef __SHEN_MOTORS_H__
#define __SHEN_MOTORS_H__

#include <shen.defs.h>

/* MOTORS */

static inline void MotorInit(void) {
    gpio_init(SHEN_MOTOR_GPIO_AIN1);
    gpio_init(SHEN_MOTOR_GPIO_AIN2);

    gpio_set_dir(SHEN_MOTOR_GPIO_AIN1, GPIO_OUT);
    gpio_set_dir(SHEN_MOTOR_GPIO_AIN2, GPIO_OUT);

    gpio_init(SHEN_MOTOR_GPIO_BIN1);
    gpio_init(SHEN_MOTOR_GPIO_BIN2);

    gpio_set_dir(SHEN_MOTOR_GPIO_BIN1, GPIO_OUT);
    gpio_set_dir(SHEN_MOTOR_GPIO_BIN2, GPIO_OUT);
    
    gpio_init(SHEN_MOTOR_GPIO_STBY);
    gpio_set_dir(SHEN_MOTOR_GPIO_STBY, GPIO_OUT);

    #if defined(__SHEN_USING_PWM__)

        gpio_set_function(SHEN_MOTOR_GPIO_PWMA, GPIO_FUNC_PWM);
        gpio_set_function(SHEN_MOTOR_GPIO_PWMB, GPIO_FUNC_PWM);

        pwm_config config = pwm_get_default_config();
        pwm_init(pwm_gpio_to_slice_num(SHEN_MOTOR_GPIO_PWMA), &config, true);
        pwm_init(pwm_gpio_to_slice_num(SHEN_MOTOR_GPIO_PWMB), &config, true);

        pwm_set_gpio_level(SHEN_MOTOR_GPIO_PWMA, 40000);
        pwm_set_gpio_level(SHEN_MOTOR_GPIO_PWMB, 40000);

    #else // Else use a binary logic in PWMA/PWMB

        gpio_init(SHEN_MOTOR_GPIO_PWMA);
        gpio_init(SHEN_MOTOR_GPIO_PWMB);

        gpio_set_dir(SHEN_MOTOR_GPIO_PWMA, GPIO_OUT);
        gpio_set_dir(SHEN_MOTOR_GPIO_PWMB, GPIO_OUT);

    #endif 
}

static inline void MotorStby(bool pos) {
    gpio_put(SHEN_MOTOR_GPIO_STBY, pos);
}

static inline void MotorSetDir(shen_motor_side_t side, shen_motor_dir_t dir) {
    if (side == LEFT) {
        if (dir == FORWARD) {
            gpio_put(SHEN_MOTOR_GPIO_AIN1, 1);
            gpio_put(SHEN_MOTOR_GPIO_AIN2, 0);
        } else if (dir == BACK) {
            gpio_put(SHEN_MOTOR_GPIO_AIN1, 0);
            gpio_put(SHEN_MOTOR_GPIO_AIN2, 1);
        } else {
            gpio_put(SHEN_MOTOR_GPIO_AIN1, 0);
            gpio_put(SHEN_MOTOR_GPIO_AIN2, 0);
        }
    } else {
        if (dir == FORWARD) {
            gpio_put(SHEN_MOTOR_GPIO_BIN1, 1);
            gpio_put(SHEN_MOTOR_GPIO_BIN2, 0);
        } else if (dir == BACK) {
            gpio_put(SHEN_MOTOR_GPIO_BIN1, 0);
            gpio_put(SHEN_MOTOR_GPIO_BIN2, 1);
        } else {
            gpio_put(SHEN_MOTOR_GPIO_BIN1, 0);
            gpio_put(SHEN_MOTOR_GPIO_BIN2, 0);
        }
    }
}

static inline void MotorSwitch(shen_motor_side_t side, bool pos) {
    if (side == LEFT) {
        gpio_put(SHEN_MOTOR_GPIO_PWMA, pos);
    } else {
        gpio_put(SHEN_MOTOR_GPIO_PWMB, pos);
    }
}

#if defined(__SHEN_USING_PWM__)

static inline void MotorSetSpeed(shen_motor_side_t side, uint16_t speed) {
    if (side == LEFT) {
        pwm_set_gpio_level(SHEN_MOTOR_GPIO_PWMA, speed);
    } else {
        pwm_set_gpio_level(SHEN_MOTOR_GPIO_PWMB, speed);
    }
}

#endif // __SHEN_USING_PWM__

#endif // __SHEN_MOTORS_H__