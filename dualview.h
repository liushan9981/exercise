#include <stdbool.h>
#include "fields.h"


#ifndef DUALVIEW_H_
    #define DUALVIEW_H_

    #define OPAQUE 0x1
    #define FILL_BLUE 0x8
    #define FILL_GREEN 0x4
    #define FILL_RED 0x2
    #define FILL_MASK 0xE
    #define BORDER 0x100
    #define BORDER_BLUE 0x800
    #define BORDER_GREEN 0x400
    #define BORDER_RED 0x200
    #define BORDER_MASK 0xE00
    #define B_SOLID 0
    #define B_DOTTED 0x1000
    #define B_DASHED 0x2000
    #define STYLE_MASK 0x3000

    union Views {
        struct box_props st_view;
        unsigned short us_view;
    };

#endif



void show_settings1(unsigned short us_view);
void run_dualview(void);
