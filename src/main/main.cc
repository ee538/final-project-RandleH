#include <iostream>

#include "mapui.h"
#include "trojanmap.h"
// #define NCURSES
//.1111.//
int main() {
    TrojanMap trojanmap;
    MapUI x;
#ifdef NCURSES
    x.PlotMap();
    x.DynamicPrintMenu();
#else
    x.PlotMap();
    x.PrintMenu();
#endif
    //...//
    return 0;
}
