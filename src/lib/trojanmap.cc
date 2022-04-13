#include "trojanmap.h"

// ========================================================================================================
// Self-defined Function
// ========================================================================================================
namespace rhqwq{
static std::string tolowercase_(const std::string &str){
    std::string tmp = str;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    return tmp;
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

    return std::make_pair( false, m );
}

static void strip_(std::string& str){
    if (str.length() == 0) return;

    auto start_it = str.begin();
    auto end_it   = str.rbegin();
    while (std::isspace(*start_it)) {
        ++start_it;
        if (start_it == str.end()) break;
    }
    while (std::isspace(*end_it)) {
        ++end_it;
        if (end_it == str.rend()) break;
    }
    auto start_pos = start_it - str.begin();
    auto end_pos   = end_it.base() - str.begin();
    str = (start_pos <= end_pos) ? std::string(start_it, end_it.base()) : "";
}

}


TrojanMap::TrojanMap(){
    CreateGraphFromCSVFile();

    // Added by RandleH and QWQ.
    for( auto &i : this->data){
        
        if( i.second.name.empty()==false ){
            v_Name_node_.push_back( std::make_pair(                      i.second.name, &i.second) );
            v_name_node_.push_back( std::make_pair( rhqwq::tolowercase_(i.second.name), &i.second) );
        }
    }
    std::stable_sort( v_Name_node_.begin(), v_Name_node_.end(), [](const rhqwq::NameNode_t &a,const rhqwq::NameNode_t &b){ return (a.first)<(b.first);} );
    
    
    std::stable_sort( v_name_node_.begin(), v_name_node_.end(), [](const rhqwq::NameNode_t &a,const rhqwq::NameNode_t &b){ return rhqwq::tolowercase_(a.first) < rhqwq::tolowercase_(b.first);} );
    
};

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string& id) {
    auto it = data.find(id);
    return  it!=data.end() ? it->second.lat : (double)(-1);
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string& id) {
    auto it = data.find(id);
    return  it!=data.end() ?  it->second.lon : (double)(-1);
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return "NULL".
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string& id) { 
    auto it = data.find(id);
    return  it!=data.end() ? it->second.name : nullptr ;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return an empty vector.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string& id) {
    auto it = data.find(id);
    return  it!=data.end() ? it->second.neighbors : std::vector<std::string> {};
}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(const std::string& name) {
    if( name.empty() ) return std::string("");
    
    auto res = rhqwq::binary_search_( v_Name_node_, name );
    return (res.first==true)? v_Name_node_[res.second].second->id: std::string("");
}

/**
 * GetPosition: Given a location name, return the position. If id does not exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
    auto res = rhqwq::binary_search_(v_Name_node_, name);
    return (res.first==true)? \
        std::make_pair( v_Name_node_[res.second].second->lat, v_Name_node_[res.second].second->lon):
        std::make_pair(   (double)(-1),   (double)(-1));
}


/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * 
 */
int TrojanMap::CalculateEditDistance(std::string w1, std::string w2){
    const size_t dp_size = (w1.size()+1)*(w2.size()+1)*sizeof(int);
    int *dp = (int*)alloca( dp_size );
    
    const size_t w = w2.size()+1;
    const size_t h = w1.size()+1;
    
    int *ptr = (int *)memset( dp, -1, dp_size);
    
    w1 = " "+w1;
    w2 = " "+w2;
    
    for( size_t j=0; j<w; ++j) *(ptr  +j) = (int)j; // 初始化dp[0][:]
    for( size_t i=0; i<h; ++i) *(ptr+i*w) = (int)i; // 初始化dp[:][0]
    ptr += w+1; // 从dp[1][1]开始

    for (size_t i=1; i<w1.size(); ++i, ++ptr) {
        for( size_t j=1; j<w2.size(); ++j, ++ptr ){
            if( w1[i] == w2[j] )
                *ptr = *(ptr-w-1);
            else
                *ptr = std::min( *(ptr  -w) , std::min(*(ptr  -1), *(ptr-w-1)) ) + 1;
        }
    }
    return *(ptr-2); // 返回dp[-1][-1]
}

/**
 * FindClosestName: Given a location name, return the name with smallest edit distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : similar name
 */
std::string TrojanMap::FindClosestName(std::string name) {
    
#if 1 // Distance order
    name = rhqwq::tolowercase_(name);

    int min = INT_MAX;

    auto &res = this->v_name_node_[0];
    for (auto &i:this->v_name_node_) {
        auto tmp = CalculateEditDistance(i.first, name);
        if( tmp < min ){
            min = tmp;
            res = i;
        }
    }
    assert( min!=INT_MAX );  // Problems in <v_name_node>.
    return res.second->name;
#else // Prefix order
    return v_Name_node_[rhqwq::binary_search_(v_Name_node_, name).second].second->name;
#endif
}


/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
    std::vector<std::string> results;
    
    if( name.empty() ) return results;
    rhqwq::strip_(name);
    
    // Convert to lower case
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    
    const std::string name_largest  (name+'z'); // Biggest valid name with prefix order.
    const std::string name_smallest (name+' '); // (Same)

    auto a = v_name_node_.begin() + rhqwq::binary_search_(v_name_node_, name_smallest).second;
    while( a->first.find( name )!=0 &&  a->first < name && a!=v_name_node_.end() ) ++a;

    auto b = v_name_node_.begin() + rhqwq::binary_search_(v_name_node_, name_largest).second;
    while( b->first.find( name )!=0 && b>=a ) --b;
    
    for( auto &i=a; i<=b; ++i){
        results.push_back(i->second->name);
    }
    return results;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < int(path.size())-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */


std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
    std::vector<std::string> path;
    
    Node &root = *this->v_Name_node_[ rhqwq::binary_search_( v_Name_node_, location1_name).second ].second;
    Node &dst  = *this->v_Name_node_[ rhqwq::binary_search_( v_Name_node_, location2_name).second ].second;
    
    // Data Initilization
    std::vector <rhqwq::DijkstraInfo_t >                  table(data.size());               // Dijkstra 算法表格
    std::map    <rhqwq::NodeId_t, rhqwq::DijkstraInfo_t*> table_map;                        // 制作一份map table 方便根据id查找数据
    std::vector <rhqwq::DijkstraInfo_t*>                  table_unvisited(data.size());     // 拷贝一份引用(指针)table 用于遍历计算路径值
    {
        size_t idx = 0;
        for( auto &i:data){
            if( i.first == root.id )
                continue;
            else
                table[idx] = rhqwq::DijkstraInfo_t( i.first, INFINITY, &i.second, idx );
            ++idx;
        }
        table[idx] = rhqwq::DijkstraInfo_t( root.id, 0.0, &root, idx ) ;        // 将跟节点放置末尾使得table sorted.
        
        auto *ptr = (&table.front());                                           // 拷贝一份引用(指针)table 用于遍历计算路径值
        for( size_t i=0; i<table.size(); ++i, ++ptr ){                          // 制作一份map table 方便根据id查找数据
            assert( ptr );
            table_map[ table[i].id ] = ptr;
            table_unvisited[i]       = ptr;
        }
    }

    while( !table_unvisited.empty() ){
        rhqwq::DijkstraInfo_t &cur = *table_unvisited.back();                   // 在所有未遍历过的节点中查找里起始点最近距离的节点
                                                                                // 由于自身处于sorted状态, 仅需访问末尾元素即可
        table_unvisited.pop_back();
        assert( !cur.id.empty() );
        
        for( auto &i:cur.node->neighbors ){
            rhqwq::DijkstraInfo_t *pNeighbor = table_map[i];
            
            if( pNeighbor->visited ) continue;
            
            double distance = CalculateDistance( cur.id, i );
            if( cur.distance + distance < pNeighbor->distance ){
                // 查找 pNeighbor在数组中的位置
//                table_unvisited.erase( table_unvisited.begin()+pNeighbor->pos  );
                
                for( size_t i=0; i<table_unvisited.size(); ++i ){
                    if( table_unvisited[i] == pNeighbor ){
                        table_unvisited.erase( table_unvisited.begin()+i  );
                        break;
                    }
                }
                
                
                pNeighbor->distance = cur.distance + distance;
                pNeighbor->prev_id  = cur.id;
                
                // 由于修改了 pNeighbor 的距离, 因此要对其重新排序
                // 两分查找最近的位置插入
                if( table_unvisited.empty() || pNeighbor->distance <= table_unvisited.back()->distance ){
                    table_unvisited.push_back(pNeighbor);
                    pNeighbor->pos = table_unvisited.size()-1;
                }else{
                    int l=0, r=(int)(table_unvisited.size()-1);
                    int m = ((l+r)>>1);
                    
                    while( l<=r ){
                        m = ((l+r)>>1);
                        if( table_unvisited[m]->distance == pNeighbor->distance ){
                            break;
                        }else if( table_unvisited[m]->distance > pNeighbor->distance ){
                            l = m+1;
                        }else{
                            r = m-1;
                        }
                    }
                    table_unvisited.insert( table_unvisited.begin()+m, pNeighbor);
                    pNeighbor->pos = m;
                }

            }
            
        }
        cur.visited = true;
        
    }
    
    // BackTracking
    assert( table_unvisited.size()==0 );
    
    auto tmp = dst.id;
    while( table_map[tmp]->id != root.id ){
        path.push_back(tmp);
        tmp = table_map[tmp]->prev_id;
    }
    path.push_back(root.id);

    return path;
}



/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Do the early termination when there is no change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){
    
    std::vector<std::string> path;
    location1_name = this->FindClosestName(location1_name);
    location2_name = this->FindClosestName(location2_name);
    
    
    
    return path;
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies. If there is no way to do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;
  return result;                                                     
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  return false;
}

/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<std::string>} subgraph: list of location ids in the square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r, 
 * find all locations in class C on the map near L with the range of r and return a vector of string ids
 * 
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {int} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
  return res;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
    std::fstream fin;
    fin.open("./src/lib/data.csv", std::ios::in);
    std::string line, word;
    assert(fin.is_open());
    getline(fin, line);
    while (getline(fin, line)) {
        std::stringstream s(line);
        
        Node n;
        int count = 0;
        while (getline(s, word, ',')) {
            word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
            word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
            word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
            word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
            if (count == 0)
                n.id = word;
            else if (count == 1)
                n.lat = stod(word);
            else if (count == 2)
                n.lon = stod(word);
            else if (count == 3)
                n.name = word;
            else {
                word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
            if (isalpha(word[0]))
                n.attributes.insert(word);
            if (isdigit(word[0]))
                n.neighbors.push_back(word);
            }
            count++;
        }
        data[n.id] = n;
  }
  fin.close();
}
