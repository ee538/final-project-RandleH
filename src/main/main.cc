#include <iostream>

#include "mapui.h"
#include "trojanmap.h"

using namespace std;


#include "../../tests/rhqwq_test.hpp"


double CalculateDistance_(const std::string &a, const std::string &b){
    
    int a_ = stoi(a);
    int b_ = stoi(b);
    
    if( a_ > b_ ) std::swap( a_, b_);
    switch(a_){
        case 0:{
            switch(b_){
                case 1: return 3;
                case 2: return 10;
                case 5: return 1;
                default: return INFINITY;
            }
        }
        case 1:{
            switch (b_) {
                case 2: return 6;
                case 3: return 1;
                default: return INFINITY;
            }
        }
        case 2: return 1;
        case 3:{
            switch(b_) {
                case 4: return 1;
                case 6: return 4;
                default: return INFINITY;
            }
        }
        case 5: return 1;
        default: return INFINITY;
    }
}


template<class T, class N>
static std::pair<bool,size_t> binary_search_(const vector<std::pair<T,N> >& list, const T& tar ){
    if( list.empty() ) return std::make_pair( false, -1 );

    int l=0, r=(int)(list.size()-1);
    auto m = ((l+r)>>1);
    while( l<=r ){
        m = ((l+r)>>1);
        if( list[m].first == tar ){
            return std::make_pair( true, m );
        }else if( list[m].first > tar ){
            r = m-1;
        }else{
            l = m+1;
        }
    }
}



int main() {
    
    
//    vector<int> v={0};
//
//    const int tar = 0;
//    if(  v.empty() || tar <= v.back() )
//        v.push_back(tar);
//    else{
//        int l=0, r=(int)(v.size()-1);
//        int m = ((l+r)>>1);
//
//        while( l<=r ){
//            m = ((l+r)>>1);
//            if( v[m] == tar ){
//                break;
//            }else if( v[m] > tar ){
//                l = m+1;
//            }else{
//                r = m-1;
//            }
//        }
//        cout<< m <<endl;
//
//        v.insert( v.begin()+m, tar);
//    }
//    for( auto &i:v ){
//        cout<<i<<" ";
//    }

//    TrojanMap tmap;
//    auto v = tmap.CalculateShortestPath_Dijkstra( "Arco", "Dulce");
//
//    for( auto &i:v ){
//        cout<<i<<"->"<<endl;
//    }
    
    MapUI x;
#ifdef NCURSES
    x.PlotMap();
    x.DynamicPrintMenu();
#else
    x.PlotMap();
    x.PrintMenu();
#endif
    
    
    
//    vector<int> a = {0,3,6,2,7,2,89};
//
//    std::make_heap(a.begin(), a.end(), []( const int& a,const int &b ){return a>b;} );
//
//    std::pop_heap(a.begin(), a.end(), []( const int& a,const int &b ){return a>b;} );
//
//    cout<< a.back() << endl;
//    a.pop_back();
//
//    a.push_back(-1);
//    std::push_heap(a.begin(), a.end(), []( const int& a,const int &b ){return a>b;} );
//
//    a.push_back(-2);
//    std::push_heap(a.begin(), a.end(), []( const int& a,const int &b ){return a>b;} );
//
//    a.push_back(-3);
//    std::push_heap(a.begin(), a.end(), []( const int& a,const int &b ){return a>b;} );
//
//    std::pop_heap(a.begin(), a.end(), []( const int& a,const int &b ){return a>b;} );
//
//    cout<< a.back() << endl;
    





    return 0;
}
