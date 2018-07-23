#include <stdbool.h>

#ifndef FIELDS_H_
    #define FIELDS_H_
    #define SOLID 0
    #define DOTTED 1
    #define DASHED 2

    #define BLUE 4
    #define GREEN 2
    #define RED 1

    #define BLACK 0
    #define YELLOW (RED | GREEN)
    #define MAGENTA (RED | BLUE)
    #define CYAN (GREEN | BLUE)
    #define WHITE (RED | GREEN | BLUE)



    struct box_props {
        bool opaque : 1;
        unsigned int fill_color : 3;
        unsigned int : 4;
        bool show_border : 1;
        unsigned int border_color : 3;
        unsigned int border_style : 2;
        unsigned int : 2;
    };

#endif

void show_settings(const struct box_props * pb);
void run_fields(void);
