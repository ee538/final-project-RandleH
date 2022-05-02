#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"


// Phase 1
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

// Test CalculateEditDistance function
TEST(TrojanMapTest, CalculateEditDistance) {
    TrojanMap m;
    EXPECT_EQ(m.CalculateEditDistance("horse", "ros"), 3);
    EXPECT_EQ(m.CalculateEditDistance("intention", "execution"), 5);
}

// Test FindClosestName function
TEST(TrojanMapTest, FindClosestName) {
    TrojanMap m;
    EXPECT_EQ(m.FindClosestName("Rolphs"), "Ralphs");
    EXPECT_EQ(m.FindClosestName("Targeety"), "Target");
}


// Phase 2
TEST(TrojanMapStudentTest, shortest_path) {

    TrojanMap tmap;
    
    std::string l1 = tmap.v_Name_node_[rand()%tmap.v_Name_node_.size()].first;
    std::string l2 = tmap.v_Name_node_[rand()%tmap.v_Name_node_.size()].first;
    
    auto v1 = tmap.CalculateShortestPath_Dijkstra( l1, l2);
    auto v2 = tmap.CalculateShortestPath_Bellman_Ford( l1, l2);
    
    EXPECT_EQ( tmap.CalculatePathLength(v1) == tmap.CalculatePathLength(v2), true );
}

TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Chick-fil-A");
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
      "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
      "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
      "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
      "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
      "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
      "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
      "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
      "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
      "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
      "6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Chick-fil-A");
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
      "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
      "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
      "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
      "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
      "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
      "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
      "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
      "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
      "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
      "6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Bellman_Ford("Chick-fil-A", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}






// Phase 3
TEST(TrojanMapStudentTest, TSP1) {
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

 TEST(TrojanMapTest, TSP2) {
   TrojanMap m;
  
   std::vector<std::string> input{"7864610982","6512300966","1855145665","7424270456","6818427895","4276259789","6814769287","1614922706"}; // Input location ids
   auto result = m.TravellingTrojan_Backtracking(input);
   std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
   std::vector<std::string> gt{"7864610982","6814769287","6818427895","4276259789","6512300966","1855145665","7424270456","1614922706","7864610982"}; // Expected order
   std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
   bool flag = false;
   if (gt == result.second[result.second.size()-1]) // clockwise
     flag = true;
   std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
   if (gt == result.second[result.second.size()-1])
     flag = true;
  
   EXPECT_EQ(flag, true);
 }

 TEST(TrojanMapTest, TSP3) {
   TrojanMap m;
  
   std::vector<std::string> input{"7864610982","6512300966","1855145665","7424270456","6818427895","4276259789","6814769287","1614922706"}; // Input location ids
   auto result = m.TravellingTrojan_2opt(input);
   std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
   std::vector<std::string> gt{"7864610982","6814769287","6818427895","4276259789","6512300966","1855145665","7424270456","1614922706","7864610982"}; // Expected order
   std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
   bool flag = false;
   if (gt == result.second[result.second.size()-1]) // clockwise
     flag = true;
   std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
   if (gt == result.second[result.second.size()-1])
     flag = true;
  
   EXPECT_EQ(flag, true);
 }





 // Test cycle detection function
 TEST(TrojanMapTest, CycleDetection) {
   TrojanMap m;
  
   // Test case 1
   std::vector<double> square1 = {-118.289, -118.288, 34.029, 34.028};
   auto sub1 = m.GetSubgraph(square1);
   bool result1 = m.CycleDetection(sub1, square1);
   EXPECT_EQ(result1, false);

   // Test case 2
   std::vector<double> square2 = {-118.295, -118.265, 34.033, 34.010};
   auto sub2 = m.GetSubgraph(square2);
   bool result2 = m.CycleDetection(sub2, square2);
   EXPECT_EQ(result2, true);
   // Test case 3
   std::vector<double> square3 = {-118.293, -118.263, 34.031, 34.012};
   auto sub3 = m.GetSubgraph(square3);
   bool result3 = m.CycleDetection(sub3, square3);
   EXPECT_EQ(result3, true);
 }



 // Test cycle detection function
 TEST(TrojanMapTest, TopologicalSort) {
   TrojanMap m;
  
   std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC"};
   std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"KFC","Chick-fil-A"}};
   auto result = m.DeliveringTrojan(location_names, dependencies);
   std::vector<std::string> gt ={"Ralphs", "KFC","Chick-fil-A"};
   EXPECT_EQ(result, gt);
 }


// Phase 3
// Test TSP function
TEST(TrojanMapTest, TSP1) {
  TrojanMap m;
  
  std::vector<std::string> input{"7864610982","6512300966","1855145665","7424270456","6818427895","4276259789","6814769287","1614922706"}; // Input location ids
  auto result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"7864610982","6814769287","6818427895","4276259789","6512300966","1855145665","7424270456","1614922706","7864610982"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1])
    flag = true;
  
  EXPECT_EQ(flag, true);
}



 // Test FindNearby points
 TEST(TrojanMapTest, FindNearby) {
   TrojanMap m;
  
   auto result = m.FindNearby("school", "Ralphs", 5, 5);
   std::vector<std::string> ans{"358791507", "358794109", "358850043", "358794351", "358793678"};
   EXPECT_EQ(result, ans);
 }
