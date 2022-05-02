#include <iostream>

#include <utility>
#include "mapui.h"
#include "trojanmap.h"

using namespace std;


#include "../../tests/rhqwq_test.hpp"

int main() {
  
//
    TrojanMap tmap;
    
    auto v = tmap.CalculateShortestPath_Dijkstra("Los Angeles & Olympic", "Vermont Elementary School");
    for( auto&i:v )
        cout<<i<<' ';
    cout<<endl;
    
    
//    cout<<tmap.FindClosestName("Adem Fuet");
//    MapUI x;
//#ifdef NCURSES
//    x.PlotMap();
//    x.DynamicPrintMenu();
//#else
//    x.PlotMap();
//    x.PrintMenu();
//#endif

    
}
