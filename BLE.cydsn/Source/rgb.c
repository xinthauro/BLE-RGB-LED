#include <rgb.h>

/* Local-scope ---------------------------------------------------------------*/
#define RGB_START_VALUE 0u

/*............................................................................*/
void RGB_start(void)
{
    /* Initializes and start PWM channels */
    PWM_RED_Start();
    PWM_GREEN_Start();
    PWM_BLUE_Start();
    /* All PWM channels off */
    PWM_RED_WriteCompare(RGB_START_VALUE);
    PWM_GREEN_WriteCompare(RGB_START_VALUE);
    PWM_BLUE_WriteCompare(RGB_START_VALUE);

}
/*............................................................................*/
void RGB_write(uint8 red, uint8 green, uint8 blue)
{
    PWM_RED_WriteCompare(red);
    PWM_GREEN_WriteCompare(green);
    PWM_BLUE_WriteCompare(blue);
}

