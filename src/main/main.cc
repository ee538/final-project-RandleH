#include <iostream>

#include "mapui.h"
#include "trojanmap.h"

using namespace std;




#include "../../tests/rhqwq_test.hpp"



int main() {

//    TrojanMap tmap;
//    RH_RECORD_TIME( tmap.FindClosestName("Rolphs"), printf);
//    cout<<tmap.FindClosestName("shplar")<<endl;
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
