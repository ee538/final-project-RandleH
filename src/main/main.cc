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


int main() {
    
    
    TrojanMap          tmap;
//    std::vector<std::string> input{"0","1","2","3"}; // Input location ids
    std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"};
    
    
    auto res = tmap.TravellingTrojan_Brute_force(input);
    
    for( auto &i:res.second ){
        for( auto &j:i )
            cout<< j << ' ';
        cout<<endl;
    }
    
    cout<<"Distance[ans]:"<<res.first<<endl;
    cout<<"Distance[cal]:"<<tmap.CalculatePathLength(res.second.back())<<endl;
    
    RH_RECORD_TIME( tmap.TravellingTrojan_Brute_force(input), printf);
    RH_RECORD_TIME( tmap.TravellingTrojan_Brute_force(input), printf);
    RH_RECORD_TIME( tmap.TravellingTrojan_Brute_force(input), printf);
    RH_RECORD_TIME( tmap.TravellingTrojan_Brute_force(input), printf);
    RH_RECORD_TIME( tmap.TravellingTrojan_Brute_force(input), printf);
    
    return 0;
    
    
    
    
    
    
//    MakeNewTrojanMap_( tmap );
//    auto v = tmap.CalculateShortestPath_Bellman_Ford( "0", "4" );
//    for( auto &i:v ){
//        cout<<i<<"->";
//    }
    
    
//    auto u = tmap.CalculateShortestPath_Dijkstra("Ralphs", "Chick-fil-A");
//    auto v = tmap.CalculateShortestPath_Bellman_Ford("Ralphs", "Chick-fil-A");
    
    
//    std::vector<std::string> res{
//        "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
//        "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
//        "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
//        "6816193786","123152294" ,"4015203136","4015203134","4015203133","21098539"  ,"6389467809",
//        "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
//        "3402887081","6814958394","3402887080","602606656" ,"4872897515","4399697589","6814958391",
//        "123209598" ,"6787673296","122728406" ,"6807762271","4399697304","4399697302","5231967015",
//        "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
//        "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
//        "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
//        "6814916515","6820935910","4547476733"};
    
//    size_t cnt=10;
//    while( cnt-- ){
//        RH_RECORD_TIME( tmap.CalculateShortestPath_Dijkstra( "Dulce", "Arco" ), printf);
//        printf("        ");
//        RH_RECORD_TIME( tmap.CalculateShortestPath_Bellman_Ford( "Dulce", "Arco"), printf);
//    }


//    cout <<"========================="<<endl;
    
    
//    assert (v.size()==res.size());
//    for( size_t i=0; i<std::min(v.size(), res.size()); ++i ){
//        cout << v[i] <<'\t' << res[i]<<'\t'<< (v[i]!=res[i])<<endl;
//    }
    

    
//    MapUI x;
//#ifdef NCURSES
//    x.PlotMap();
//    x.DynamicPrintMenu();
//#else
//    x.PlotMap();
//    x.PrintMenu();
//#endif
    
    




    
}
