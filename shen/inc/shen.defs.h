#ifndef __SHEN_DEFS_H__
#define __SHEN_DEFS_H__

/*
    sio_hw->gpio_set = (1 << 25);
    sio_hw->gpio_clr = (1 << 25);

    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, adc_read());
*/

enum shen_perph_t {

    /* GPIO */

    SHEN_DEBUG_GPIO_TX  = 0,
    SHEN_DEBUG_GPIO_RX  = 1,

    SHEN_MOTOR_GPIO_STBY    = 2,

    SHEN_MOTOR_GPIO_AIN2    = 3,
    SHEN_MOTOR_GPIO_AIN1    = 4,

    SHEN_MOTOR_GPIO_BIN1    = 5,
    SHEN_MOTOR_GPIO_BIN2    = 6,

    /* GPIO 7 missed */

    SHEN_MOTOR_GPIO_PWMA    = 8,
    SHEN_MOTOR_GPIO_PWMB    = 14,

    SHEN_RC_GPIO_START          = 10,
    SHEN_RC_GPIO_KILL_SWITCH    = 11,

    SHEN_MUX_GPIO_S0        = 12,
    SHEN_MUX_GPIO_S1        = 13,

    SHEN_ADC_GPIO_LINE_SENSOR_LEFT_FRONT    = 26,
    SHEN_ADC_GPIO_LINE_SENSOR_RIGHT_FRONT   = 27,
    SHEN_ADC_GPIO_LINE_SENSOR_LEFT_REAR     = 28,
    SHEN_ADC_GPIO_LINE_SENSOR_RIGHT_REAR    = 29,

    SHEN_GPIO_LEFT_EYE = 16,
    SHEN_GPIO_RIGHT_EYE = 15,

    /* ADC channels */

    SHEN_ADC_CHANNEL_LINE_SENSOR_LEFT_FRONT         = 0,
    SHEN_ADC_CHANNEL_LINE_SENSOR_RIGHT_FRONT        = 1,
    SHEN_ADC_CHANNEL_LINE_SENSOR_LEFT_RIGHT_REAR    = 2,
    
    /* Temperature sensor */
    SHEN_ADC_CHANNEL_INT_TEMP_SENSOR    = 3,

    /* For the instructions for recognition*/
    SHEN_LEFT_FRONT_REC_LINE    = 0,
    SHEN_RIGHT_FRONT_REC_LINE   = 1,
    SHEN_ONE_OF_REAR_REC_LINE   = 2,
    SHEN_ALL_REAR_REC_LINE      = 3,

    SHEN_MAX_SPEED = __UINT16_MAX__
};

typedef enum {
    LEFT = 0,
    RIGHT = 1
} shen_motor_side_t, shen_dir_t;

enum shen_motor_dir_t {
    FORWARD,
    BACK,
    FAST_STOP
};

typedef enum {
    MOVE_FORWARD,
    MOVE_BACK,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_ULEFT,
    MOVE_URIGHT,
    MOVE_STOP_ALL
} shen_move_t;

typedef uint16_t shen_adc_t;

#endif // __SHEN_DEFS_H__