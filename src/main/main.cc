#include <iostream>

#include <utility>
#include "mapui.h"
#include "trojanmap.h"

using namespace std;


#include "../../tests/rhqwq_test.hpp"



int sort_shell  (void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)){
    size_t inc = nel-1; // 希尔增量
    
    inc |= inc>>1;
    inc |= inc>>2;
    inc |= inc>>4;
    inc |= inc>>8;
    inc |= inc>>16;
    
    while( inc>1 ){
        inc = ((inc+1)>>1)-1;                             // 希尔增量递推关系式子(自行设定) 此处为 a[n] = 2^n - 1
        // 以下为对步长为 inc 所得到的子数组进行插入排序
        size_t   step     = inc*width;                    // 字节步长 = 单个元素字节数 x 数组步长
        uint8_t* ptr_iter = ((uint8_t*)base);             // 子数组首地址
        for( long i=inc; i<nel; i++, ptr_iter+=width ){
            uint8_t* ptr_tar = (uint8_t*)alloca(width);
            uint8_t* ptr_tmp = ptr_iter;
            memmove(ptr_tar, ptr_iter+step, width);       // 临时存放选中的元素值
            
            for (long j=i-inc; j>=0; j-=inc, ptr_tmp-=step){
                if( (*compar)( ptr_tmp, ptr_tar )>=0 ){        // compare base[j] & base[i]
                    memmove( ptr_tmp+step, ptr_tmp, width );
                    continue;
                }
                break;
            }
            memmove( ptr_tmp+step, ptr_tar, width );
        }
    }
    
    return 0;
}


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

void   MakeNewTrojanMap_( TrojanMap& tmap ){
    Node tmp;

    tmap.data.clear();

    tmp.id        = "0";
    tmp.neighbors = { "1", "2", "5" };
    tmap.data[ "0" ] = tmp;

    tmp.id        = "1";
    tmp.neighbors = { "0", "2", "3" };
    tmap.data[ "1" ] = tmp;

    tmp.id        = "2";
    tmp.neighbors = { "0", "1", "3" };
    tmap.data[ "2" ] = tmp;

    tmp.id        = "3";
    tmp.neighbors = { "1", "2", "6", "4" };
    tmap.data[ "3" ] = tmp;

    tmp.id        = "4";
    tmp.neighbors = { "3" };
    tmap.data[ "4" ] = tmp;

    tmp.id        = "5";
    tmp.neighbors = { "0", "6" };
    tmap.data[ "5" ] = tmp;

    tmp.id        = "6";
    tmp.neighbors = { "3", "5" };
    tmap.data[ "6" ] = tmp;
}






void permutate( vector<int> &v, size_t cs, size_t ce){
    if( cs==ce ){
        for( auto &i:v ) cout<<i;
        cout<<endl;
        return;
    }
    
    for( size_t i=cs; i<=ce; ++i ){
        std::swap( v[cs], v[i] );
        permutate( v, cs+1, ce );
        std::swap( v[cs], v[i] );
    }
}




template<class T, class N>
static std::pair<bool,size_t> binary_search_(const vector<std::pair<T,N> >& list, const T& tar ){
    if( list.empty() ) return std::make_pair( false, 0 );

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

    return std::make_pair( false, l );
}




int main() {
    
    
    TrojanMap tmap;
    auto a = tmap.FindNearby("supermarket", "Ralphs", 10, 10);
    
    RH_RECORD_TIME(tmap.FindNearby("supermarket", "Ralphs", 10, 10), printf);
    RH_RECORD_TIME(tmap.FindNearby("supermarket", "Ralphs", 10, 10), printf);
    RH_RECORD_TIME(tmap.FindNearby("supermarket", "Ralphs", 10, 10), printf);
    
    for( auto&i:a ){
        cout<<i<<endl;
    }
    
//    MapUI x;
//#ifdef NCURSES
//    x.PlotMap();
//    x.DynamicPrintMenu();
//#else
//    x.PlotMap();
//    x.PrintMenu();
//#endif
    


    
}
