#include <project.h>
#include <rgb.h>

/*............................................................................*/
int main(void)
{
    CyGlobalIntEnable;

    uint8 b = 0;
    uint8 g = 63;
    uint8 r = 127;

    RGB_start();
    RGB_write(r, g, b);

    for (;;) {
        for (int i = 0; i < 255; ++i) {
            RGB_write(r++, g++, b++);
            CyDelay(5);
        }
    }
}

