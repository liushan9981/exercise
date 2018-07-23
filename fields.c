#include <stdio.h>
#include "fields.h"
#include <stdbool.h>

const char * colors[8] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"};

void run_fields(void)
{
    struct box_props box = {true, YELLOW, true, GREEN, DASHED};

    printf("original setting: \n");
    show_settings(&box);

    box.opaque = false;
    box.fill_color = WHITE;
    box.border_color = MAGENTA;
    box.border_style = SOLID;

    printf("\nModified box setting: \n");
    show_settings(&box);

}


void show_settings(const struct box_props * pb)
{
    printf("Box is %s\n", pb->opaque == true ? "opaque" : "transparent");
    printf("fill color is: %s\n", colors[pb->fill_color]);
    printf("border is: %s\n", pb->show_border == true ? "shown" : "not shown");
    printf("border color is: %s\n", colors[pb->border_color]);
    printf("border style is: ");

    switch (pb->border_style)
    {
    case SOLID:
        printf("solid\n");
        break;
    case DOTTED:
        printf("dotted\n");
        break;
    case DASHED:
        printf("dashed\n");
        break;
    default:
        printf("unknown type\n");
    }

}


