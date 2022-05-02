#include <iostream>

#include <utility>
#include "mapui.h"
#include "trojanmap.h"

using namespace std;


#include "../../tests/rhqwq_test.hpp"

int main() {
     
    
    
    TrojanMap tmap;
//    std::vector<std::string> ids;
//    for( size_t i=0; i<10; ++i ){
//        ids.push_back(tmap.v_Name_node_[ rand()%tmap.v_Name_node_.size() ].second->id );
//    }
//
//    auto ids_copy = ids;
//
//    auto v1 = tmap.TravellingTrojan_Brute_force(ids);
//    assert( ids_copy==ids );
//    auto v2 = tmap.TravellingTrojan_Backtracking(ids);
//    auto v3 = tmap.TravellingTrojan_2opt(ids);
//    assert(v1.first == v2.first);
//    assert(v1.first <= v3.first);

    
    
    
    MapUI x;
#ifdef NCURSES
    x.PlotMap();
    x.DynamicPrintMenu();
#else
    x.PlotMap();
    x.PrintMenu();
#endif

    
}

