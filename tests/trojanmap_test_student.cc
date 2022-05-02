#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapStudentTest, shortest_path) {

    TrojanMap tmap;
    
    std::string l1 = tmap.v_Name_node_[rand()%tmap.v_Name_node_.size()].first;
    std::string l2 = tmap.v_Name_node_[rand()%tmap.v_Name_node_.size()].first;
    
    auto v1 = tmap.CalculateShortestPath_Dijkstra( l1, l2);
    auto v2 = tmap.CalculateShortestPath_Bellman_Ford( l1, l2);
    
    EXPECT_EQ( tmap.CalculatePathLength(v1) == tmap.CalculatePathLength(v2), true );
}


TEST(TrojanMapStudentTest, tsp) {
    TrojanMap tmap;
    std::vector<std::string> ids;
    for( size_t i=0; i<10; ++i ){
        ids.push_back(tmap.v_Name_node_[ rand()%tmap.v_Name_node_.size() ].second->id );
    }
    
    auto v1 = tmap.TravellingTrojan_Brute_force(ids);
    auto v2 = tmap.TravellingTrojan_Backtracking(ids);
    auto v3 = tmap.TravellingTrojan_2opt(ids);
    EXPECT_EQ(v2.first <= v3.first, true);
}


TEST(TrojanMapTest, Autocomplete) {
    TrojanMap m;
    // Test the simple case
    auto names = m.Autocomplete("ar");
    std::unordered_set<std::string> gt = {"Arco"}; // groundtruth for "Ch"
    int success = 0;
    for (auto& n: names) {
        EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
        if (gt.count(n) > 0){
          success++;
        }
    }
}

