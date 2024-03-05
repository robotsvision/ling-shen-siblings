#ifndef __SHEN_TWINS_H__
#define __SHEN_TWINS_H__

/* Standart SDK libs */
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/uart.h"

#include <stdio.h>

/* Shen includes */
#include <shen.defs.h>
#include <shen.motors.h>
#include <shen.rc.h>
#include <shen.serial.h>

/* Initialization */
shen_serial_c serial(uart0);

class shen_c {
private:

    uint16_t move_speed = SHEN_MAX_SPEED;
    uint16_t stabilized_speed = 10000;
    uint16_t line_sensors[3];
    bool move_direction = true;

    void board_indicator_init(uint16_t brightness = __UINT16_MAX__) {
        gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);
        pwm_config config = pwm_get_default_config();
        pwm_init(pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN), &config, true);
        pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, brightness);
    }

    void rc_init(void) {
        RC_Init();
    }

    void board_uart_init(uint32_t baud = SHEN_UART_BAUD) {
        uart_init(SHEN_UART, SHEN_UART_BAUD);
        gpio_set_function(SHEN_DEBUG_GPIO_TX, GPIO_FUNC_UART);
        gpio_set_function(SHEN_DEBUG_GPIO_RX, GPIO_FUNC_UART);
    }

    void eye_init(void) {
        gpio_init(SHEN_GPIO_LEFT_EYE);
        gpio_init(SHEN_GPIO_RIGHT_EYE);
        gpio_set_dir(SHEN_GPIO_LEFT_EYE, GPIO_IN);
        gpio_set_dir(SHEN_GPIO_RIGHT_EYE, GPIO_IN);
    }

    void line_sensors_init(void) {
        adc_init();
        adc_gpio_init(SHEN_ADC_GPIO_LINE_SENSOR_LEFT_FRONT);
        adc_gpio_init(SHEN_ADC_GPIO_LINE_SENSOR_RIGHT_FRONT);
        adc_gpio_init(SHEN_ADC_GPIO_LINE_SENSOR_LEFT_REAR);
        adc_gpio_init(SHEN_ADC_GPIO_LINE_SENSOR_RIGHT_REAR);
    }

    void motor_init(bool stby) {
        MotorInit();
        /* STBY motor driver or not */
        MotorStby(stby);
        #if !defined(__SHEN_USING_PWM__)
            MotorSwitch(LEFT, stby);
            MotorSwitch(RIGHT, stby);
        #else
            MotorSetSpeed(LEFT, move_speed);
            MotorSetSpeed(RIGHT, move_speed);
        #endif
    }

    bool readLineSensor(uint8_t sensor_channel) {
        switch (sensor_channel) {
        case SHEN_LEFT_FRONT_REC_LINE:
            return (bool)(line_sensors[0] > 800);
            break;
        case SHEN_RIGHT_FRONT_REC_LINE:
            return (bool)(line_sensors[1] > 800);
            break;
        case SHEN_ONE_OF_REAR_REC_LINE:
            return (bool)(line_sensors[2] > 150);
            break;
        case SHEN_ALL_REAR_REC_LINE:
            return (bool)(line_sensors[2] > 200);
            break;
        default:
            return false;
        }
    }

    bool readEyeSensor(uint8_t eye_gpio) {
        return !(bool)(gpio_get(eye_gpio));
    }

    void Move(shen_move_t dir) {
        switch (dir) {

        case MOVE_FORWARD:
            MotorSetSpeed(LEFT, move_speed);
            MotorSetSpeed(RIGHT, move_speed);
            MotorSetDir(LEFT, FORWARD);
            MotorSetDir(RIGHT, FORWARD);
            break;

        case MOVE_BACK:
            MotorSetSpeed(LEFT, move_speed);
            MotorSetSpeed(RIGHT, move_speed);
            MotorSetDir(LEFT, BACK);
            MotorSetDir(RIGHT, BACK);
            break;

        case MOVE_ULEFT:
            MotorSetSpeed(LEFT, move_speed);
            MotorSetSpeed(RIGHT, move_speed);
            MotorSetDir(LEFT, BACK);
            MotorSetDir(RIGHT, FORWARD);
            break;
        case MOVE_URIGHT:
            MotorSetSpeed(LEFT, move_speed);
            MotorSetSpeed(RIGHT, move_speed);
            MotorSetDir(LEFT, FORWARD);
            MotorSetDir(RIGHT, BACK);
            break;

        case MOVE_LEFT:
            MotorSetSpeed(LEFT, 5000);
            MotorSetSpeed(RIGHT, move_speed);
            MotorSetDir(LEFT, BACK);
            MotorSetDir(RIGHT, FORWARD);
            break;
        case MOVE_RIGHT:
            MotorSetSpeed(LEFT, move_speed);
            MotorSetSpeed(RIGHT, 5000);
            MotorSetDir(LEFT, FORWARD);
            MotorSetDir(RIGHT, BACK);
            break;

        default:
            MotorStby(false);
        }
    }

public:
    bool status = false;

    void setup(void) {
        board_indicator_init();
        board_uart_init();
        rc_init();
        eye_init();
        line_sensors_init();
        motor_init(true);
        MotorSetDir(LEFT, FAST_STOP);
        MotorSetDir(RIGHT, FAST_STOP);
        ShenStartWaiting();
        status = true;
        MotorSetDir(LEFT, FORWARD);
        MotorSetDir(RIGHT, FORWARD);
        for(uint8_t i = 0; i < 100; ++i){
            move_direction = readEyeSensor(SHEN_GPIO_RIGHT_EYE);
            sleep_ms(2);
        }
    }
    
    void loop2(void) {
        status = gpio_get(SHEN_RC_GPIO_KILL_SWITCH);
        adc_select_input(0);
        line_sensors[0] = adc_read();
        adc_select_input(1);
        line_sensors[1] = adc_read();
        adc_select_input(2);
        line_sensors[2] = adc_read();
    }

    void loop(void) {
        if ((readLineSensor(SHEN_LEFT_FRONT_REC_LINE) || readLineSensor(SHEN_RIGHT_FRONT_REC_LINE)) 
            && readLineSensor(SHEN_ONE_OF_REAR_REC_LINE)){
            if (move_direction) {
                MotorSetDir(LEFT, FORWARD);
                MotorSetDir(RIGHT, BACK);
            } else {
                MotorSetDir(LEFT, BACK);
                MotorSetDir(RIGHT, FORWARD);
            }
        } else if (readLineSensor(SHEN_LEFT_FRONT_REC_LINE) || readLineSensor(SHEN_RIGHT_FRONT_REC_LINE)) {
            Move(MOVE_BACK);
            move_direction = readLineSensor(SHEN_RIGHT_FRONT_REC_LINE); // i am genius, right?))
        } else if (readLineSensor(SHEN_ONE_OF_REAR_REC_LINE)) {
            Move(MOVE_FORWARD);
        } else {
            if (readEyeSensor(SHEN_GPIO_LEFT_EYE) && readEyeSensor(SHEN_GPIO_RIGHT_EYE)) {
                Move(MOVE_FORWARD);
            } else if (readEyeSensor(SHEN_GPIO_LEFT_EYE)) {
                Move(MOVE_LEFT);
                if (move_direction != LEFT){
                    if (stabilized_speed >= 200) {
                        stabilized_speed -= 200;
                    }  
                }
                move_direction = LEFT;
            } else if (readEyeSensor(SHEN_GPIO_RIGHT_EYE)) {
                Move(MOVE_RIGHT);
                if (move_direction != RIGHT){
                    if (stabilized_speed >= 200) {
                        stabilized_speed -= 200;
                    } 
                }
                move_direction = RIGHT;
            } else {
                if (move_direction) {
                    Move(MOVE_RIGHT);
                } else {
                    Move(MOVE_LEFT);
                }
            }
        }
        if (stabilized_speed < (5000 - 10)) {
            stabilized_speed += 10;
        }
    }
};

shen_c shen;

#endif // __SHEN_TWINS_H__