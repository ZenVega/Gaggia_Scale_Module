#ifndef SCALE_H
    #define SCALE_H

    #include "constants.h"
    #include <HX711.h>

    void    init_scale();
    void    tare_scale();
    float   get_weight();

#endif