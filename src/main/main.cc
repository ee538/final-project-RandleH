#include <iostream>

#include "mapui.h"
#include "trojanmap.h"
// #define NCURSES
using namespace std;

int main() {
    
    MapUI x;
#ifdef NCURSES
    x.PlotMap();
    x.DynamicPrintMenu();
#else
    x.PlotMap();
    x.PrintMenu();
#endif

    return 0;
}
