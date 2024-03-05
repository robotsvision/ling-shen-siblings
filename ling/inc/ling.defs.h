#ifndef __LING_DEFS_H__
#define __LING_DEFS_H__

/*
    sio_hw->gpio_set = (1 << 25);
    sio_hw->gpio_clr = (1 << 25);

    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, adc_read());
*/

enum ling_perph_t {

    /* GPIO */

    LING_DEBUG_GPIO_TX  = 0,
    LING_DEBUG_GPIO_RX  = 1,

    LING_MOTOR_GPIO_STBY    = 2,

    LING_MOTOR_GPIO_AIN2    = 3,
    LING_MOTOR_GPIO_AIN1    = 4,

    LING_MOTOR_GPIO_BIN1    = 5,
    LING_MOTOR_GPIO_BIN2    = 6,

    /* GPIO 7 missed */

    LING_MOTOR_GPIO_PWMA    = 8,
    LING_MOTOR_GPIO_PWMB    = 14,

    LING_RC_GPIO_START      = 10,
    LING_RC_GPIO_STOP       = 11,

    LING_MUX_GPIO_S0        = 12,
    LING_MUX_GPIO_S1        = 13,

    LING_ADC_GPIO_LINE_SENSOR_LEFT_FRONT    = 26,
    LING_ADC_GPIO_LINE_SENSOR_RIGHT_FRONT   = 27,
    LING_ADC_GPIO_LINE_SENSOR_LEFT_REAR     = 28,
    LING_ADC_GPIO_LINE_SENSOR_RIGHT_REAR    = 29,

    LING_GPIO_LEFT_EYE = 15,
    LING_GPIO_RIGHT_EYE = 16,

    /* ADC channels */

    LING_ADC_CHANNEL_LINE_SENSOR_LEFT_FRONT = 0,
    LING_ADC_CHANNEL_LINE_SENSOR_RIGHT_FRONT = 1,
    LING_ADC_CHANNEL_LINE_SENSOR_LEFT_REAR = 2,
    LING_ADC_CHANNEL_LINE_SENSOR_RIGHT_REAR = 3,

    /* For the instructions for recognition*/

    LING_LEFT_FRONT_REC_LINE    = 0,
    LING_RIGHT_FRONT_REC_LINE   = 1,
    LING_LEFT_REAR_REC_LINE     = 2,
    LING_RIGHT_REAR_REC_LINE    = 3,

    LING_MAX_SPEED = __UINT16_MAX__
};

typedef enum {
    LEFT = 0,
    RIGHT = 1
} ling_motor_side_t, ling_dir_t;

typedef enum  {
    FORWARD,
    BACK,
    FAST_STOP
} ling_motor_dir_t;

typedef enum {
    MOVE_FORWARD,
    MOVE_BACK,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_ULEFT,
    MOVE_URIGHT,
    MOVE_STOP_ALL
} ling_move_t;


typedef uint16_t ling_adc_t;

#endif // __LING_DEFS_H__