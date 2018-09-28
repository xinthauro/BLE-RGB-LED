/*******************************************************************************
* rgb.h
* Last updapted 2018-09-27
*
* Carlos Silva
*******************************************************************************/
#ifndef RGB_H
#define RGB_H

#include <project.h>

typedef enum {
    RGB_BREATHE_NOT,
    RGB_BREATHE_MAGENTA,
    RGB_BREATHE_CYAN,
    RGB_BREATHE_MAX
} RGBBreatheMode;

typedef struct {
    uint8 red;
    uint8 green;
    uint8 blue;
} RGBValue;

void RGB_start(void);
void RGB_write(RGBValue *value);
void RGB_setBreathe(RGBBreatheMode mode);
void RGB_process(void);

#endif

