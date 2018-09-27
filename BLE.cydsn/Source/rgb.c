#include <rgb.h>

/* Local-scope ---------------------------------------------------------------*/
#define RGB_START_VALUE 0u

static RGBValue const rgbStartValue = {
    . red = RGB_START_VALUE,
    . green = RGB_START_VALUE,
    . blue = RGB_START_VALUE
};

/*............................................................................*/
void RGB_start(void)
{
    RGBValue value;
    /* Initializes and start PWM channels */
    PWM_RED_Start();
    PWM_GREEN_Start();
    PWM_BLUE_Start();
    /* All PWM channels off */
    PWM_RED_WriteCompare(rgbStartValue.red);
    PWM_GREEN_WriteCompare(rgbStartValue.green);
    PWM_BLUE_WriteCompare(rgbStartValue.blue);

}
/*............................................................................*/
void RGB_write(RGBValue *value)
{
    PWM_RED_WriteCompare(value->red);
    PWM_GREEN_WriteCompare(value->green);
    PWM_BLUE_WriteCompare(value->blue);
}

