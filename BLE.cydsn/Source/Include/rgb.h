#ifndef RGB_H
#define RGB_H

#include <project.h>

typedef struct {
    uint8 red;
    uint8 green;
    uint8 blue;
} RGBValue;

void RGB_start(void);
void RGB_write(RGBValue *value);

#endif

