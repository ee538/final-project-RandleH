<center><h3>EE 538 - Computing Principles for Electrical Engineers</h3></center>

<center><h1>Trojan Map Report</h1></center>

<center><h4>Team Member: Yuanji Qiu(USC ID:707421454)  Weiqiang Qian(USC ID:5555112745)</h4></center>

<h3>Content</h3>
1.Autocomplete the location name
2.Find the place's Coordinates in the map
3.Calculate shortest path between two places
4.The traveling Trojan problem(AKA Traveling Salesman!)
5.Cycle Detection
6.Topological sort
7.Find Nearby
8.Summary



## Document Symbol Dercription

| Symbol | Description        |
| :----: | ------------------ |
|   ®️    | Reference variable |
|   🟢    | Input parameters   |
|   🔴    | Output parameters  |
|   🔒    | Read-only variable |





## Data Structure 



Each point on the map is represented by the class **Node** shown below and defined in trojanmap.h

```c++
class Node {
public:
    Node(){};
    Node(const Node &n){id = n.id; lat = n.lat; lon = n.lon; name = n.name; neighbors = n.neighbors; attributes = n.attributes;};
    std::string id;                              // A unique id assign to each point
    double lat;                                  // Latitude
    double lon;                                  // Longitude
    std::string name;                            // Name of the location. E.g. "Bank of America".
    std::vector<std::string> neighbors;          // List of the ids of all neighbor points.
    std::unordered_set<std::string> attributes;  // List of the attributes of the location.
};
```

​	Also, in order to realise these functions conveniently, we created our own namespace rhqwq and some data structures in trojanmap.h

```c++
// Self-defined implimentation
namespace rhqwq{
// Data Structure
typedef std::pair<std::string, Node*>   NameNode_t;     // A pair binding the location name with its node information.
typedef std::vector< NameNode_t >       V_NameNode_t;   // A vector contains a bunch of such combinations.
typedef std::string NodeId_t;
class DijkstraInfo_t{
public:
    NodeId_t  id;
    NodeId_t  prev_id;
    Node     *node;
    bool      visited;
    double    distance;
    DijkstraInfo_t(){}
    DijkstraInfo_t( NodeId_t node_id                         ) :id(node_id),distance(INFINITY)    ,visited(false)       ,node(nullptr ){}
    DijkstraInfo_t( NodeId_t node_id, double dis, Node* node ) :id(node_id),distance(     dis)    ,visited(false)       ,node(node    ){}
    DijkstraInfo_t( const DijkstraInfo_t& rhs                ) :id(rhs.id) ,distance(rhs.distance),visited(rhs.visited) ,node(rhs.node){}
```





### `rhqwq::DijkstraInfo_t` 	

| Member | Type       | Initialization Value | Description |
| ------ | ---------- | -------------------- | ----------- |
| `id`   | `NodeId_t` | qwq                  | qwq         |
| qwq    | qwq        | qwq                  | qwq         |
| qwq    | qwq        | qwq                  | qwq         |
|        |            |                      |             |





## Auxiliary Function Method

### `rhqwq::tolowercase_`

| Params     | Attributes | Type                  | Description                                |
| ---------- | :--------: | --------------------- | ------------------------------------------ |
| `str`      | 🟢 \| 🔒\|®️  | `const std::string &` | The input string to be converted           |
| `$return$` |     🔴      | `std::string`         | The lower case version of the input string |



### `rhqwq::binary_search_`

| Params | Attributes | Type  | Description |
| ------ | :--------: | ----- | ----------- |
| qwq    |    qwq     | `qwq` | qwq         |
| qwq    |    qwq     | `qwq` | qwq         |



### `rhqwq::strip_`

| Params | Attributes | Type  | Description |
| ------ | :--------: | ----- | ----------- |
| qwq    |    qwq     | `qwq` | qwq         |
| qwq    |    qwq     | `qwq` | qwq         |



We also do some pre-processing on our dataset in trojanmap.cc  to make it faster when we use this app.

```c++
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
```

















# 把上面填了吧 求求了 by RandleH





















<h3>1.Autocomplete the location name</h3>

<h4>1.1 Function</h4>

```c++
std::vector<std::string> TrojanMap::Autocomplete(std::string name);
```

​	Type the partial name of the location and return a list of possible locations with partial name as prefix. It's also not a case-sensitive function, so we just turn all of the name to the lowercase.
It will take a long time if we just search a name in an unordered dataset. So we decided to sorted the dataset when we load the app. And use binary search to decrease the time comlexity to O(log(n)).

<h4>1.2 Results</h4>

```c++
**************************************************************
Please input a partial location:chi
*************************Results******************************
Chick-fil-A
Chinese Street Food
Chipotle
**************************************************************
Time taken by function: 0 ms
```

​	Because we sorted the data during the loading time. so it’s very fast to get the result(0ms) when we use this function. Also when I type the lowercase string it still return the original name in the dataset.
​	The time complexity of this function is:

<h3>2.Find the place’s Coordianes in the Map </h3>

<h4>2.1 Function</h4>

```c++
std::pair<double, double> TrojanMap::GetPosition(std::string name); 
```

It’s similar to the previous function, we sort the dataset firstly and use binary search to compare the name with the input.

Also we need to give the most similar word if we have a typo in our input , so we implement these two functions.

```c++
int TrojanMap::CalculateEditDistance(std::string w1, std::string w2);
std::string TrojanMap::FindClosestName(std::string name);
```

​	First we use dynamic programming on the EditDistance, and do it twice by taking pointer and vector. Then we decided to take the fastest method——iteration. Then we find the closest name by taking rules of the smallest edit distance. (It’s case sensitive)

<h4>2.2 Results</h4>

```c++
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:arco
*************************Results******************************
No matched locations.
Did you mean Arco instead of arco? [y/n]y
Latitude: 34.0354 Longitude: -118.284
**************************************************************
Time taken by function: 0 ms
```

![image-20220413225732110](/Users/weiqiangqian/Library/Application Support/typora-user-images/image-20220413225732110.png)

```c++
**************************************************************
Please select 1 - 8: 2

**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:Ralphs
*************************Results******************************
Latitude: 34.0318 Longitude: -118.291
**************************************************************
Time taken by function: 0 ms
```

![image-20220413232038689](/Users/weiqiangqian/Library/Application Support/typora-user-images/image-20220413232038689.png)

​	From the results we can see the run time is pretty fast(0ms)
​	The time complexity of GetPosition is O(log(n));
​	The time complexity of CalculateEditDistance is O();
​	The time complexity of FindClosestName is O().











⭕️⛔️🟩🟥❌✅🔴🟢🔘☑️🔒🔓🔗®️

