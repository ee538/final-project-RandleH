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

    return std::make_pair( false, l );
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
//        m_id_dijkstra_[ i.first ] = rhqwq::DijkstraInfo_t( i.first, INFINITY, &i.second );
        
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

#if 1 // 合并未访问节点
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
    
    Node &root = *this->v_Name_node_[ rhqwq::binary_search_( v_Name_node_, location1_name).second ].second;
    Node &dst  = *this->v_Name_node_[ rhqwq::binary_search_( v_Name_node_, location2_name).second ].second;
    
    // Data Initilization
    auto cmp = []( const rhqwq::DijkstraInfo_t&a, const rhqwq::DijkstraInfo_t&b){return a.distance>b.distance;};
    std::vector<rhqwq::DijkstraInfo_t> container;
    container.reserve( data.size() );
    std::priority_queue<rhqwq::DijkstraInfo_t, std::vector<rhqwq::DijkstraInfo_t>, decltype(cmp)>   table_unvisited_(cmp, std::move(container));
    
    std::unordered_map < rhqwq::NodeId_t, rhqwq::DijkstraInfo_t >                                   table_;
    table_.reserve(data.size());
    
    {
        for( auto &i:data){
            if( i.first==root.id ){
                table_.insert( std::make_pair( i.first, rhqwq::DijkstraInfo_t( i.first, 0.0, &i.second ) ) );
                table_unvisited_.push( rhqwq::DijkstraInfo_t( i.first, 0.0, &i.second ));
            }else{
                table_.insert( std::make_pair( i.first, rhqwq::DijkstraInfo_t( i.first, INFINITY, &i.second ) ) );
                table_unvisited_.push( rhqwq::DijkstraInfo_t( i.first, INFINITY, &i.second ));
            }
            
        }

    }

    size_t visitedCnt = 0;
    while( visitedCnt < data.size() ){
        auto &dij_cur = table_[ table_unvisited_.top().id ];
        table_unvisited_.pop();
        assert( !dij_cur.id.empty() );
        
        for( auto &i:dij_cur.node->neighbors ){
            rhqwq::DijkstraInfo_t &dij_neighbor = table_[i];
            
            if( dij_neighbor.visited ) continue;
//            if(relax_(dij_cur, dij_neighbor)){
//                table_unvisited_.push(dij_neighbor);
//            }
            double distance = CalculateDistance( dij_cur.id, i );
            if( dij_cur.distance + distance < dij_neighbor.distance ){
                // 查找 pNeighbor在数组中的位置
                dij_neighbor.distance = dij_cur.distance + distance;
                dij_neighbor.prev_id  = dij_cur.id;
                
                table_unvisited_.push(dij_neighbor);

            }
            
        }
        dij_cur.visited = true;
        ++visitedCnt;
    }
    
    // Collect result
    std::vector<std::string> path;
    path.reserve(1024);
    auto tmp = dst.id;
    while( tmp != root.id ){
        path.push_back(tmp);
        tmp = table_[tmp].prev_id;
    }
    path.push_back(root.id);
    
    std::reverse(path.begin(), path.end());
    return path;
}
#else // 分裂未访问节点
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
    
    Node &root = *this->v_Name_node_[ rhqwq::binary_search_( v_Name_node_, location2_name).second ].second;
    Node &dst  = *this->v_Name_node_[ rhqwq::binary_search_( v_Name_node_, location1_name).second ].second;
    
    // Data Initilization
    auto cmp = []( const rhqwq::DijkstraInfo_t*a, const rhqwq::DijkstraInfo_t*b){return a->distance>b->distance;};
    std::vector<rhqwq::DijkstraInfo_t*> container;
    container.reserve( data.size() );
    std::priority_queue<rhqwq::DijkstraInfo_t*, std::vector<rhqwq::DijkstraInfo_t*>, decltype(cmp)> table_unvisited_referenced_    (cmp, std::move(container));
    std::unordered_map < rhqwq::NodeId_t, rhqwq::DijkstraInfo_t*>                                   table_unvisited_unreferenced_;
    table_unvisited_unreferenced_.reserve(data.size());
    
    std::unordered_map < rhqwq::NodeId_t, rhqwq::DijkstraInfo_t >                                   table_;
    table_.reserve(data.size());
    
    {
        for( auto &i:data){
            if( i.first==root.id ){
                table_.insert( std::make_pair(i.first, rhqwq::DijkstraInfo_t( i.first, 0.0, &i.second )) );
                table_unvisited_referenced_.push( &table_[ i.first ] );
            }else{
                table_.insert( std::make_pair(i.first, rhqwq::DijkstraInfo_t( i.first, INFINITY, &i.second )) );
                table_unvisited_unreferenced_[ i.first ] = &table_[ i.first ];
            }
            
        }
    }
    
    size_t visitedCnt = 0;
    while( visitedCnt < data.size() ){
        auto &dij_cur = table_unvisited_referenced_.empty() ? *(table_unvisited_unreferenced_.begin()->second) : table_[ table_unvisited_referenced_.top()->id ];
        
        if( !table_unvisited_referenced_.empty() )
            table_unvisited_referenced_.pop();
         
        assert( !dij_cur.id.empty() );
        
        for( auto &i:dij_cur.node->neighbors ){
            rhqwq::DijkstraInfo_t &dij_neighbor = table_[i];
            
            if( dij_neighbor.visited ) continue;
            
            double distance = CalculateDistance( dij_cur.id, i );
            if( dij_cur.distance + distance < dij_neighbor.distance ){

                dij_neighbor.distance = dij_cur.distance + distance;
                dij_neighbor.prev_id  = dij_cur.id;

                table_unvisited_referenced_.push(&dij_neighbor);
                table_unvisited_unreferenced_.erase( dij_neighbor.id );
            }
            
        }
        dij_cur.visited = true;
        
        
        ++visitedCnt;
    }

    
    // BackTracking
    std::vector<std::string> path;
    
    path.reserve(1024);
    auto tmp = dst.id;
    while( tmp != root.id ){
        path.push_back(tmp);
        tmp = table_[tmp].prev_id;
    }
    path.push_back(root.id);

    return path;
}
#endif


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

    Node &root = *this->v_Name_node_[ rhqwq::binary_search_( v_Name_node_, location1_name).second ].second;
    Node &dst  = *this->v_Name_node_[ rhqwq::binary_search_( v_Name_node_, location2_name).second ].second;

    std::unordered_map< rhqwq::NodeId_t, rhqwq::BellmanInfo_t> table_;
    {
        /* Initialization */                        for( auto &i : data ){
        /* Initialization */                            table_.insert(std::make_pair( i.first, rhqwq::BellmanInfo_t( i.first, INFINITY, &i.second)) );
        /* Initialization */                        }
        /* Initialization */                        table_[root.id].distance = 0.0;
        /* Initialization */                        assert( table_.size()==data.size() );
    }

    queue<rhqwq::NodeId_t> id_updated;
    id_updated.push(root.id);

    while( !id_updated.empty() ){

        auto & table_i = table_[ id_updated.front() ];   id_updated.pop();
//        assert( table_i.distance!=INFINITY );
        
        for( auto &j : table_i.node->neighbors ){
            if( relax_( table_i, table_[j]) )
                id_updated.push(j);
        }
        
    }

    
    std::vector<std::string> path;
    auto tmp = dst.id;
    while( tmp != root.id ){
        path.push_back(tmp);
        tmp = table_[tmp].prev_id;
    }
    path.push_back(root.id);
    std::reverse(path.begin(), path.end());
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
    std::pair<double, std::vector<std::vector<std::string>>> results;
      if(location_ids.size() <= 1){
        std::vector<std::vector<std::string>> path;
        return make_pair(0,path);
      }
      double min = DBL_MAX;
      std::vector<std::string> temp;
      std::vector<std::string> cur;
      temp.assign(location_ids.begin()+1,location_ids.end());
      std::sort(temp.begin(),temp.end());
      do{
        cur.push_back(location_ids[0]);
        for(auto id:temp) cur.push_back(id);
        cur.push_back(location_ids[0]);
        double cur_length = CalculatePathLength(cur);
        cur.clear();
        if(cur_length < min){
          min = cur_length;
          results.first = min;
          std::vector<std::string> path;
          path.push_back(location_ids[0]);
          for(auto id:temp) path.push_back(id);
          path.push_back(location_ids[0]);
          results.second.push_back(path);
        }
      }while(next_permutation(temp.begin(),temp.end()));
      return results;
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
    std::vector<std::string> cur_path={location_ids[0]};
    std::vector<std::string> min_path;
    // std::vector<std::vector<std::string>> result_path;
    std::pair<double, std::vector<std::vector<std::string>>> results;
    std::vector<std::vector<double>> weights(location_ids.size(),std::vector<double>(location_ids.size()));
    double min_cost=DBL_MAX;
    if(location_ids.size() <= 1){
        std::vector<std::vector<std::string>> path;
        return make_pair(0,path);
      }
    for(int i=0;i<location_ids.size();i++){
      for(int j=0;j<location_ids.size();j++){
        weights[i][j]=CalculateDistance(location_ids[i],location_ids[j]);
      }
    }
    backtracking_helper(0,weights,0,0,cur_path,min_cost,min_path,location_ids);
    min_path.push_back(location_ids[0]);
    // for(int k=0;k<min_path.size()-1;k++){
    //   std::vector<std::string> tmp={min_path[k],min_path[k+1]};
    //   result_path.push_back(tmp);
    // }
    // result_path.push_back({min_path[min_path.size()-2],min_path[min_path.size()-1]});
    results.first=min_cost;
    results.second.push_back(min_path);
    return results;
}

void TrojanMap::backtracking_helper(int start, std::vector<std::vector<double>> &weights,
int cur_node, double cur_cost, std::vector<std::string> &cur_path, double &min_cost,
std::vector<std::string> &min_path, std::vector<std::string> &location_ids){
if(cur_path.size()==weights.size()){
  double final_cost=cur_cost+weights[cur_node][start];
  if(final_cost<min_cost){
    min_cost=final_cost;
    min_path=cur_path;
  }
  return;
}
if(cur_cost>=min_cost){
  return;
}
for(int i=0;i<weights.size();i++){
  if(std::find(cur_path.begin(),cur_path.end(),location_ids[i])==cur_path.end()){
    cur_path.push_back(location_ids[i]);
    backtracking_helper(start,weights,i,cur_cost+weights[cur_node][i],cur_path,min_cost,min_path,location_ids);
    cur_path.pop_back();
  }
}
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> location_ids){
    std::pair<double, std::vector<std::vector<std::string>>> results;
     std::vector<std::string> cur_point = location_ids;
     cur_point.push_back(location_ids[0]);
     auto nums = location_ids.size();
     bool judge = true;
     while(judge){
       start_again:
       judge=false;
       double cur_pathlen = CalculatePathLength(cur_point);
       for(int i=1;i<nums-1;i++){
         for(int k=i+1;k<nums;k++){
           auto route = Opt2swap(cur_point,i,k);
           double pathlen = CalculatePathLength(route);
           if(pathlen<cur_pathlen){
             cur_point = route;
             cur_pathlen = pathlen;
             results.first = cur_pathlen;
             results.second.push_back(cur_point);
             judge=true;
             goto start_again;
           }
         }
       }
     }
     return results;
}


std::vector<std::string> TrojanMap::Opt2swap(const std::vector<std::string> &route,int i,int k){
  std::vector<std::string> res(route);
  std::reverse(res.begin()+i,res.begin()+k+1);
  return res;
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
    
    std::fstream fin;
    fin.open( dependencies_filename, std::ios::in);
    std::string line, word;
    assert(fin.is_open());
    getline(fin, line);
    while (getline(fin, line)) {
        std::stringstream s(line);
        
        int count = 0;
        std::vector<std::string> tmp;
        while (getline(s, word, ',')) {
            word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
            word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
            word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
            word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
                
            if (count == 0){ // Source
                tmp.push_back(word);
            }else { // Destination
                tmp.push_back(word);
            }
            count++;
        }
        dependencies_from_csv.push_back(tmp);
  }
  fin.close();
    
    
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
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &V,
                                                     std::vector<std::vector<std::string>> &E){
    std::vector<std::string> res;
    
    struct Info_t{
        size_t              n_Incom;
        vector<std::string> neighbors;
        Info_t():n_Incom(0){}
    };
    
#define src 0
#define dst 1
    std::map<std::string, Info_t> table_;
    {
     /* Initialization */                          for( auto &i : V ){
     /* Initialization */                              table_.insert(std::make_pair(i, Info_t()));
     /* Initialization */                          }
     /* Initialization */                          for( auto &e : E ){
     /* Initialization */                              table_[ e[dst] ].n_Incom++;
     /* Initialization */                              table_[ e[src] ].neighbors.push_back( e[dst] );
     /* Initialization */                          }
    }
    
    std::queue< rhqwq::NodeId_t > no_incom_edge;
    {
    /* Initialization */                           for( auto &i : V ){
    /* Initialization */                               if( table_[i].n_Incom==0 ){
    /* Initialization */                                   no_incom_edge.push(i);
    /* Initialization */                               }
    /* Initialization */                           }
    }
    
    while (!no_incom_edge.empty()){
        auto i = no_incom_edge.front(); no_incom_edge.pop();
        res.push_back(i);
        for( auto &s : table_[ i ].neighbors ){
            --table_[s].n_Incom;
            if( table_[s].n_Incom==0 )
                no_incom_edge.push(s);
        }
        
    }
    
    if( res.size()!= V.size() )
        return std::vector<std::string>();
    
    return res;
    
#undef src
#undef dst
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
    if(GetLon(id)>=square[0] && GetLon(id)<=square[1] && GetLat(id)<=square[2] && GetLat(id)>=square[3]){
        return true;
    }
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
    double left_lon = square[0];
    double right_lon = square[1];
    double upper_lat = square[2];
    double lower_lat = square[3];
    for(auto it = data.begin(); it != data.end(); ++it){
        if(it->second.lon >= left_lon && it->second.lon <= right_lon && it->second.lat <= upper_lat && it->second.lat >= lower_lat){
            subgraph.push_back(it->first);
        }
    }
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<std::string>} subgraph: list of location ids in the square
 * @param {std::vector<double>} square: four vertexes of the square area  lon_L, lon_R, lat_N, lat_S
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
    std::unordered_map<std::string, bool> table_;
    {
        for ( auto & i: data ) {
            table_.insert(std::make_pair( i.first, false));
        }
    }
    
    std::string foo = "";
    for( auto &id : subgraph ){
        
        if( Cycle_helper( id, foo, table_, square) ){
            return true;
        }
        for( auto &i : table_ ){
            i.second = false;
        }
    }
        
    return false;
}


bool TrojanMap::Cycle_helper(std::string &id_curr, std::string &id_prev, std::unordered_map<std::string, bool> &table_, std::vector<double> &square){
    
    if(!inSquare( id_curr, square)) return false;
    
    bool &isVisited = table_[id_curr];
    if( isVisited==true ){
        return true;
    }

    isVisited = true;
    
    for( auto &i : data[ id_curr ].neighbors ){
        if( id_prev!="" && id_prev==i ) continue;
        if( true==Cycle_helper( i, id_curr, table_, square) )
            return true;
    }
    
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
     struct record
     {
       std::string id;
       double dis;
       bool operator<(const record &rhs) const
       {
         return dis < rhs.dis;
       }
     };
     std::priority_queue<record> records;
     std::string cur_id = GetID(name);
     // O(N + KlogK)
     for (const auto &it : data)
     {
       if (it.second.id == cur_id)
         continue;
       if (it.second.attributes.count(attributesName) > 0)
       {
         double dis = CalculateDistance(it.second.id, cur_id);
         if (dis <= r && (records.size() < k || dis < records.top().dis))
         {
           if (records.size() >= k)
           {
             records.pop();
           }
           records.push({it.second.id, dis});
         }
       }
     }
     // O(KlogK)
     while (records.size() != 0)
     {
       auto top = records.top();
       records.pop();
       res.push_back(top.id);
     }
     std::reverse(res.begin(), res.end());
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
