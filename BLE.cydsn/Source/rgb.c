/*******************************************************************************
* rgb.c
* Last updapted 2018-09-27
*
* Carlos Silva
*******************************************************************************/
#include <rgb.h>

/* Local-scope ---------------------------------------------------------------*/
#define RGB_START_VALUE 0u

typedef struct {
    struct {
        RGBBreatheMode mode;
        RGBValue value;
        uint8 dir;
    } breathe;
} Me;

static RGBValue const rgbStartValue = {
    .red = RGB_START_VALUE,
    .green = RGB_START_VALUE,
    .blue = RGB_START_VALUE
};

static Me me = { .breathe.mode = RGB_BREATHE_NOT };

/*............................................................................*/
void RGB_start(void)
{
    /* Initializes and start PWM channels */
    PWM_RED_Start();
    PWM_GREEN_Start();
    PWM_BLUE_Start();
    /* All PWM channels off */
    PWM_RED_WriteCompare(rgbStartValue.red);
    PWM_GREEN_WriteCompare(rgbStartValue.green);
    PWM_BLUE_WriteCompare(rgbStartValue.blue);
    /* Pins at startup are configured as HIGH-Z, this avoid the initial glitch */
    PIN_RED_SetDriveMode(PIN_RED_DM_STRONG);
    PIN_GREEN_SetDriveMode(PIN_GREEN_DM_STRONG);
    PIN_BLUE_SetDriveMode(PIN_BLUE_DM_STRONG);

}
/*............................................................................*/
void RGB_write(RGBValue *value)
{
    PWM_RED_WriteCompare(value->red);
    PWM_GREEN_WriteCompare(value->green);
    PWM_BLUE_WriteCompare(value->blue);
}
/*............................................................................*/
void RGB_setBreathe(RGBBreatheMode mode)
{
    /* Reset values */
    me.breathe.value.red = 0;
    me.breathe.value.green = 0;
    me.breathe.value.blue = 0;
    /* Set mode */
    me.breathe.mode = mode;
}
/*............................................................................*/
void RGB_process(void)
{
    switch (me.breathe.mode) {
        case RGB_BREATHE_NOT:
            return;
        case RGB_BREATHE_MAGENTA:
            if (me.breathe.value.red == 0u) {
                me.breathe.dir = 1u;
            } else if (me.breathe.value.red == 255u) {
                me.breathe.dir = 0u;
            } else {
            }
            if (me.breathe.dir) {
                me.breathe.value.red = ++me.breathe.value.blue;
            } else {
                me.breathe.value.red = --me.breathe.value.blue;
            }
            break;
        case RGB_BREATHE_CYAN:
            if (me.breathe.value.blue == 0u) {
                me.breathe.dir = 1u;
            } else if (me.breathe.value.blue == 255u) {
                me.breathe.dir = 0u;
            } else {
            }
            if (me.breathe.dir) {
                me.breathe.value.blue = ++me.breathe.value.green;
            } else {
                me.breathe.value.blue = --me.breathe.value.green;
            }
            break;
        default:
            break;
    }
    RGB_write(&me.breathe.value);
}

