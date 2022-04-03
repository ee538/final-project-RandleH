#include <iostream>

#include "mapui.h"
#include "trojanmap.h"
// #define NCURSES
using namespace std;

int main() {
    TrojanMap trojanmap;

    
    
//    cout<< trojanmap.data["123706432"].name.empty() <<endl;
//    cout<< trojanmap.data["150934188"].name <<endl;
    
//    for( auto &i : trojanmap.v_name_node_ ){
//        cout<<i.first<<endl;
//    }
//    cout<<"===================================="<<endl;
//    auto v = trojanmap.Autocomplete("Ch");
//
//    for( auto &i : v ){
//        cout<<i<<endl;
//    }

    
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
