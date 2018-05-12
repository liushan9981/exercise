#include <stdio.h>
#include <stdbool.h>
#include "fields.h"
#include "dualview.h"

// const char * colors[8] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"};

extern char * colors[8];

void run_dualview(void)
{
    union Views box = { {true, YELLOW, true, GREEN, DASHED} };

    printf("--original setting: \n");
    show_settings(&(box.st_view) );
    printf("\n");
    show_settings1(box.us_view);

    box.st_view.opaque = false;
    box.st_view.fill_color = WHITE;
    box.st_view.border_color = MAGENTA;
    box.st_view.border_style = SOLID;

    printf("---------------------------------\n");
    printf("\n--Modified box setting: \n");
    show_settings(&box.st_view);
    printf("\n");
    show_settings1(box.us_view);

    box.us_view &= ~FILL_MASK;
    box.us_view |= (FILL_BLUE | FILL_GREEN);
    box.us_view ^= OPAQUE;
    box.us_view &= ~STYLE_MASK;
    box.us_view |= B_DOTTED;

    printf("---------------------------------\n");
    printf("\n--Last modified box setting: \n");
    show_settings(&box.st_view);
    printf("\n");
    show_settings1(box.us_view);

}


void show_settings1(unsigned short us_view)
{
    printf("Box is %s\n", (us_view & OPAQUE) == OPAQUE ? "opaque" : "transparent");
    printf("fill color is: %s\n", colors[(us_view & FILL_MASK) >> 1]);
    printf("border is: %s\n", (us_view & BORDER) == BORDER ? "shown" : "not shown");
    printf("border color is: %s\n", colors[(us_view & BORDER_MASK) >> 9]);
    printf("border style is: ");

    switch (us_view & STYLE_MASK)
    {
    case B_SOLID:
        printf("solid\n");
        break;
    case B_DOTTED:
        printf("dotted\n");
        break;
    case B_DASHED:
        printf("dashed\n");
        break;
    default:
        printf("unknown type\n");
    }


}

