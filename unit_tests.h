/* 
 * unit_tests.h
 * 
 * CS 15 project 2
 * by Chelsie Wei 12/5/2021
 * 
 */
 
 #include "SixDegrees.h"
 #include "CollabGraph.h"
 #include "Artist.h"
 #include "vector"
 
 using namespace std;
 
 //*******************************************
 //  SAMPLE VECTOR
 //*******************************************
 
 // vec.push_back(Artist("Taylor Swift"));
 // vec.back().add_song("End Game");
 // vec.back().add_song("Red");
 // 
 // vec.push_back(Artist("Ed Sheeran"));
 // vec.back().add_song("End Game");
 // vec.back().add_song("Photograph");
 // vec.back().add_song("Dark Times");
 // 
 // vec.push_back(Artist("The Weeknd"));
 // vec.back().add_song("Dark Times");
 // vec.back().add_song("Starboy");
 // 
 // vec.push_back(Artist("Grimes"));
 // vec.back().add_song("Oblivion");

 
 //88888888888888888888888888888
 //    POPULATE GRAPH 
 //88888888888888888888888888888
 void testPopulateGraph()
{
    CollabGraph map;
    
    vector<Artist> vec;
    
    vec.push_back(Artist("Taylor Swift"));
    vec.back().add_song("End Game");
    vec.back().add_song("Red");
    
    vec.push_back(Artist("Ed Sheeran"));
    vec.back().add_song("End Game");
    vec.back().add_song("Photograph");
    vec.back().add_song("Dark Times");
    
    vec.push_back(Artist("The Weeknd"));
    vec.back().add_song("Dark Times");
    vec.back().add_song("Starboy");
    
    vec.push_back(Artist("Grimes"));
    vec.back().add_song("Oblivion");
    
    map.populate_graph(vec);
    map.print_graph(std::cout);
    
}

//88888888888888888888888888888
//    GET_VERTEX_NEIGHBORS 
//88888888888888888888888888888
void testGetNeighbors()
{
    CollabGraph map;
    
    vector<Artist> vec;
    
    vec.push_back(Artist("Taylor Swift"));
    vec.back().add_song("End Game");
    vec.back().add_song("Red");
    
    vec.push_back(Artist("Ed Sheeran"));
    vec.back().add_song("End Game");
    vec.back().add_song("Photograph");
    vec.back().add_song("Dark Times");
    
    vec.push_back(Artist("The Weeknd"));
    vec.back().add_song("Dark Times");
    vec.back().add_song("Starboy");
    
    vec.push_back(Artist("Grimes"));
    vec.back().add_song("Oblivion");
    
    map.populate_graph(vec);
    
    vector<Artist>ts = map.get_vertex_neighbors(Artist("Taylor Swift"));
    vector<Artist>es = map.get_vertex_neighbors(Artist("Ed Sheeran"));
    vector<Artist>tw = map.get_vertex_neighbors(Artist("The Weeknd"));
    vector<Artist>g = map.get_vertex_neighbors(Artist("Grimes"));
    
    cout << "TS neighbor is " << ts.back() << endl;
    
    cout << "Ed's neighbor is " << es.back() << endl;   
    es.pop_back();
    cout << "Ed's neighbor is " << es.back() << endl;
    
    cout << "Weeknd's neighbor is " << tw.back() << endl;

}

//88888888888888888888888888888
//    REPORT_PATH 
//88888888888888888888888888888
// top most element should be the source; bottom is the desti
void testReportPath()
{
    CollabGraph map;
    vector<Artist> vec;
    
    vec.push_back(Artist("Taylor Swift"));
    vec.back().add_song("End Game");
    vec.back().add_song("Red");
    
    vec.push_back(Artist("Ed Sheeran"));
    vec.back().add_song("End Game");
    vec.back().add_song("Photograph");
    vec.back().add_song("Dark Times");
    
    vec.push_back(Artist("The Weeknd"));
    vec.back().add_song("Dark Times");
    vec.back().add_song("Starboy");
    
    map.populate_graph(vec);

    map.set_predecessor(Artist("Ed Sheeran"), Artist("Taylor Swift"));
    map.set_predecessor(Artist("The Weeknd"), Artist("Ed Sheeran"));
    
    stack<Artist>path = 
    map.report_path(Artist("Taylor Swift"), Artist("The Weeknd"));
    
    cout << path.size() << endl;
    cout << path.top() << endl;
    path.pop();
    cout << path.top() << endl;
    path.pop();
    cout << path.top() << endl;
    // path.pop();
    
}
// 
// void testBFS() 
// {
//     SixDegrees map;
//     vector<Artist> vec;
// 
//     vec.push_back(Artist("Taylor Swift"));
//     vec.back().add_song("End Game");
//     vec.back().add_song("Red");
// 
//     vec.push_back(Artist("Ed Sheeran"));
//     vec.back().add_song("End Game");
//     vec.back().add_song("Photograph");
//     vec.back().add_song("Dark Times");
// 
//     vec.push_back(Artist("The Weeknd"));
//     vec.back().add_song("Dark Times");
//     vec.back().add_song("Starboy");
// 
//     map.populate_graph(vec);
// 
// 
// }
// 








