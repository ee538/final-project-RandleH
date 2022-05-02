#include <iostream>

#include <utility>
#include "mapui.h"
#include "trojanmap.h"

using namespace std;


#include "../../tests/rhqwq_test.hpp"

int main() {
  
//
//    TrojanMap tmap;
    
    
//    cout<<tmap.FindClosestName("Adem Fuet");
    MapUI x;
#ifdef NCURSES
    x.PlotMap();
    x.DynamicPrintMenu();
#else
    x.PlotMap();
    x.PrintMenu();
#endif

    
}



$ -118.291
$ -118.289
$ 34.030
$ 34.020
