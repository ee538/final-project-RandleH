#include <iostream>

#include "mapui.h"
#include "trojanmap.h"
// #define NCURSES
using namespace std;

static std::string tolowercase_(const std::string &str){
    std::string tmp = str;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    return tmp;
}

#define RH_RECORD_TIME(func, print_func)({ clock_t cs = clock();func;clock_t ce = clock();print_func("RECORD_TIME:%ld\n",ce-cs); })

int main() {
    TrojanMap tmap;

    RH_RECORD_TIME(tmap.Autocomplete("fu"), printf);
//    for( auto&i:v )
//        cout<< i<<endl;
    
    RH_RECORD_TIME(tmap.Autocomplete("mi"), printf);
    
    
//    for( auto&i:v )
//        cout<< i<<endl;
    
//    std::string str1("arc");
//    std::string str2("Arco");

//    vector<string> v_str = {

//       /* 0 */ "Adams Fuel",
//       /* 1 */ "Adams Normandie Historic District",
//       /* 2 */ "Adams-Normandie",
//       /* 3 */ "Ahmanson Commons",
//       /* 4 */ "All Peoples Christian Center",
//       /* 5 */ "Amazon Hub Locker",
//       /* 6 */ "American Hungarian Baptist Church",
//       /* 7 */ "Annas Store",
//       /* 8 */ "Antioch Temple Baptist Church",
//       /* 9 */ "Apostolic Holy Cross Church",
//       /* 10 */ "Arco",
//       /* 11 */ "Axis on Twelfth",
//       /* 12 */ "Bacari W Adam?",
//       /* 13 */ "Bank of America",
//       /* 14 */ "Basketball Co",
//    };
    
    
    
//    auto a = v_str.begin()+9;
//    auto b = v_str.begin()+13;
//    while( tolowercase_(*a).find( tolowercase_("arc") )==string::npos ) ++a;
//    while( tolowercase_(*b).find( tolowercase_("arc") )==string::npos ) --b;
//
//    cout<<*a<<endl;
//    cout<<*b<<endl;
    
    
    
    

//    for( auto&i:tmap.v_name_node_ ){
//        cout<<i.first<<endl;
//    }

//    cout<<tmap.CalculateEditDistance("Rol", "Ralphs")<<endl;
    
    
    
//    MapUI x;
//#ifdef NCURSES
//    x.PlotMap();
//    x.DynamicPrintMenu();
//#else
//    x.PlotMap();
//    x.PrintMenu();
//#endif

    return 0;
}
