#include <project.h>

int main(void)
{
    CyGlobalIntEnable;

    uint8 b = 0;
    uint8 g = 63;
    uint8 r = 127;

    PWM_BLUE_Start();
    PWM_GREEN_Start();
    PWM_RED_Start();

    PWM_BLUE_WriteCompare(0);
    PWM_GREEN_WriteCompare(0);
    PWM_RED_WriteCompare(0);

    for (;;) {
        for (int i = 0; i < 255; ++i) {
            PWM_BLUE_WriteCompare(b++);
            PWM_GREEN_WriteCompare(g++);
            PWM_RED_WriteCompare(r++);
            CyDelay(5);
        }
    }
}

