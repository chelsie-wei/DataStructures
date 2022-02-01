/*
 * SixDegrees.cpp 
 * Name: Chelsie Wei 
 * Date: 12/5/2021
 * Purpose: implements and initializes an undirected graph; is able to traverse
 *          the graph and prints out path between artists with breadth first 
 *          search or depth first search. runs input commands and quits the 
 *          program when being asked to. 
 */
 
 #include "SixDegrees.h"
 #include "CollabGraph.h"
 #include "Artist.h"
 #include <stdexcept>
 #include <sstream>
 #include <fstream>
 #include <iostream>
 #include <vector>
 #include <queue>
 #include <stack>
 
 using namespace std;
 
 // Default Constructor 
SixDegrees::SixDegrees() {}

// Destructor
SixDegrees::~SixDegrees() {}

// initializeGraph
// Parameters: an input stream that takes in input from main.cpp
// Purpose: initializes graph and populates it with input stream from main.cpp
// Return: none 
void SixDegrees::initializeGraph(istream& input)
{
    vector<Artist> vec;
    string temp;
    
    while (getline(input, temp)) {
        vec.push_back(Artist(temp));
        string song;
        while (getline(input, song) and (song != "*")) {
            vec.back().add_song(song);
        }
    }

    map.populate_graph(vec);
    
}

// run
// Parameters: an istream of input taken from main.cpp, and output stream 
//             that allows program to print to cout or file 
// Purpose: takes in commands from cin or file and runs the commands
// Return: none, but may print to cout or file 
void SixDegrees::run(istream &input, ostream &output)
{
    string temp;
    
    while (getline(input, temp)) {
        map.clear_metadata();
        string source, dest;
        if (temp == "quit") {
            return;
        } else if (temp == "print") {
            ifPrint(output);
        } else if (temp == "bfs") {
            ifBFS(input, output);
        } else if (temp == "dfs") {
            ifDFS(input, output);
        } else if (temp == "not") {
            getline(input, source);
            getline(input, dest);
            ifNot(input, source, dest, output);
        } else {
            output << temp << " is not a command. Please try again.\n";
        }
    }

}

// ifPrint
// Parameters: an output stream that prints to cout or output file
// Purpose: calls print_graph function from collabgraph and prints the entire
//          graph
// Return: none. however couts or prints into output file 
void SixDegrees::ifPrint(ostream &output)
{
    map.print_graph(output);    
}

// ifBFS
// Parameters: an istream of input taken from main.cpp, and output stream 
//             that allows program to print to cout or file.
// Purpose: if bfs is taken in as command, takes in two more artists names 
//          and calls helper functions that traverse graph with breadth first 
//          search
// Return: none 
void SixDegrees::ifBFS(istream& input, ostream &out)
{
    string source, dest;
    getline(input, source);
    getline(input, dest);
    
    // if source and destination vertex are the same artist
    if (source == dest) {
        output(out, source, dest);
        
    // if one or both vertexes are not in the graph 
    } else if (checkVertex(source, dest) > 0) {
        ifUnknown(source, dest, out);
    } else {
        bfsTraverse(source, dest, out);
    }
}

// bfsTraverse
// Parameters: Two Artist instances, one is the source Artist that we wish 
//             the path to begin from and another is the destination Artist 
//             where we wish the path to end at. 
// Purpose: helper function for ifBFS that traverses the graph using bfs. 
//          prints out appropriate output to cout or output file. Sets 
//          predecessors. 
// Return: none 
void SixDegrees::bfsTraverse(const Artist& source, const Artist& dest, 
                             ostream &out)
{
    queue<Artist> q;
    map.mark_vertex(source);
    q.push(source);
                              // loop over neighbors of the first element on 
    while (not q.empty()) {   // the stack; if stack is empty: the whole graph
                              // has been traversed
        vector<Artist>neigh = map.get_vertex_neighbors(q.front());
        int size = neigh.size();
        
        for (int i = 0; i < size; i++) {
            if ((neigh[i] == dest) and (not map.is_marked(neigh[i]))) {
                map.set_predecessor(neigh[i], q.front());
                output(out, source, dest);
                return; 
            } else if (not map.is_marked(neigh[i])){
                map.mark_vertex(neigh[i]);
                map.set_predecessor(neigh[i], q.front());
                q.push(neigh[i]);
            }
        }
        q.pop();  // pops the current element off the stack once its finished
    }
    
    if (q.empty())
        output(out, source, dest);
}

// ifDFS
// Parameters: an istream of input taken from main.cpp, and output stream 
//             that allows program to print to cout or file.
// Purpose: if dfs is taken in as command, takes in two more artists names 
//          and calls helper functions that traverse graph with depth first 
//          search
// Return: none. however couts or prints into output file 
void SixDegrees::ifDFS(istream& input, ostream &out)
{
    string source, dest;
    getline(input, source);
    getline(input, dest);
    
    // if source and destination vertex are the same artist
    if (source == dest) {
        output(out, source, dest);

    // if one or both vertexes are not in the graph
    } else if (checkVertex(source, dest) > 0){
        ifUnknown(source, dest, out);
    } else {
        dfsTraverse(source, dest, out);
    }
}

// dfsTraverse
// Parameters: Two Artist instances, one is the source Artist that we wish 
//             the path to begin from and another is the destination Artist 
//             where we wish the path to end at. 
// Purpose: helper function for ifDFS that traverses the graph using dfs. 
//          prints out appropriate output to cout or output file
// Return: none 
void SixDegrees::dfsTraverse(const Artist& source, const Artist& dest,
                             ostream &out)
{
    map.clear_metadata();
    
    dfsHelper(source, source, dest);
    
    output(out, source, dest);
    
}

// dfsHelper
// Parameters: Three Artist instances: curr is the current vertex at which the
//             traversal is currently at, one is the vertex that we with to
//             begin finding a path from, one is the vertex that we wish 
//             to end our traversal at
// Purpose: traverses the graph with dfs recursively. Sets predecessors. 
// Return: none
void SixDegrees::dfsHelper(const Artist& curr, const Artist& source,
                           const Artist& dest)
{
    vector<Artist>neigh = map.get_vertex_neighbors(curr);
    int size = neigh.size();
    
    map.mark_vertex(curr);
    // loops through neighbors of the current artist
    for (int i = 0; i < size; i++) {
        if (neigh[i] == dest) {
            map.set_predecessor(dest, curr);
            return; // end loop if the dest artist is reached 
        
        // if a neighbor artist is not visited, visits it
        } else if (not map.is_marked(neigh[i])) {
            map.set_predecessor(neigh[i], curr);
            dfsHelper(neigh[i], source, dest);
        // go in here only if the last neighbor is visited; back track to 
        // last artist with unvisited neighbors
        } else if (map.is_marked(neigh[i]) and (i == size - 1)) {
            return;
        }    
    }
}

// ifNot
// Parameters: an input stream input taken from file or cin; two instances 
//             of Artists where one is the source Artist and the other is the 
//             destination artist. An output stream "out"
// Purpose: if "not" is taken in through cin or file, checks whether all 
//          inputted vertex are in the graph; if they are, mark the "not" 
//          vertexes as visited, after which the bfs traversal is called
// Return: none
void SixDegrees::ifNot(istream &input, const Artist& source, 
                       const Artist& dest, ostream &out)
{
    string nots;
    ::stack<Artist> stack;
    // push all artist that are to be excluded onto the same stack
    while (getline(input, nots) and (nots != "*")) 
        stack.push(Artist(nots));
        
    // call checkNots which loops through the stack and check if artists exist
    ::stack<Artist> unknown = checkNots(stack);
    // check whether the inputted source and dest artists exist
    int check = checkVertex(source, dest);
    
    if ((unknown.size() > 0) or (check > 0)) {   // go in this conditional if
        ifUnknown(source, dest, out);            // either the stack of 
        while (unknown.size() != 0) {            // excluded artists or 
            printUnknown(unknown.top(), out);    // dest & source artists 
            unknown.pop();                       // do not exist
        }
    } else {
        int size = stack.size();                 // go here if all artists
        for (int i = 0; i < size; i++) {         // inputted exist in graph
            map.mark_vertex(stack.top());
            stack.pop();
        }
        bfsTraverse(source, dest, out);
    }
    
}

// checkNots
// Parameters: a constant stack of Artists that contains the vertex (artist)
//             that are to be removed from path and premarked as visited
// Purpose: check whether the inputted "not" vertexes are in the graph. 
// Return: return a stack of artists that are not in the graph; returns an
//         empty stack if all artists are in the graph
stack<Artist> SixDegrees::checkNots(const stack<Artist>& stack) 
{
    ::stack<Artist> unknown;
    ::stack<Artist> s = stack;
    int size = s.size();
    
    for (int i = 0; i < size; i++) {
        if (not map.is_vertex(s.top())) {
            unknown.push(s.top());
        }
        s.pop();
    }
    
    return unknown;

}

// checkVertex
// Parameters: two instances of Artist. one is the source Artist that we wish 
//             the path to begin from and another is the destination Artist 
//             where we wish the path to end at. 
// Purpose: check whether the inputted source Artist and dest Artist are 
//          in the graph 
// Return: an integer number indicting whether both artist are not in the 
//         graph, or one of them is not in the graph, or both are IN the graph
int SixDegrees::checkVertex(const Artist& source, const Artist& dest)
{
    if (not map.is_vertex(source) or not map.is_vertex(dest)) {
        return 1;
    } else if (not map.is_vertex(source) and not map.is_vertex(dest)) {
        return 2;
    }
    
    return 0;
}

// ifUnknown
// Parameters: two instances of Artist. one is the source Artist that we wish 
//             the path to begin from and another is the destination Artist 
//             where we wish the path to end at. An output stream "out"
// Purpose: calls helper function printUnknown if source/dest or both source 
//          and dest Artists are not in the graph.  
// Return: none
void SixDegrees::ifUnknown(const Artist& source, const Artist& dest,
                             ostream& out)
{    
    if (not map.is_vertex(source) and map.is_vertex(dest)) {
        printUnknown(source, out);
    } else if (map.is_vertex(source) and not map.is_vertex(dest)) {
        printUnknown(dest, out);
    } else if (not map.is_vertex(source) and not map.is_vertex(dest)){
        printUnknown(source, out);
        printUnknown(dest, out);
    } 
}

// printUnknown
// Parameters: An instance of artist that is NOT in the graph. An output stream
//             "out"
// Purpose: couts or prints to output file the appropriate message for which 
//          a vertex is not in the graph 
// Return: none
void SixDegrees::printUnknown(const Artist& artist, ostream& out) 
{
    string quote = "\"";
    string face = ":(";
    
    out << quote << artist.get_name() << quote << " was not found in the" <<
           " dataset " << face << endl;
}

// output
// Parameters: two instances of Artist. one is the source Artist that we wish 
//             the path to begin from and another is the destination Artist 
//             where we wish the path to end at. An output stream "out"
// Purpose: takes care of printing paths between vertexes. if path does not 
//          exist between vertexes, appropriate message is being printed. 
// Return: none
void SixDegrees::output(ostream &out, const Artist& source, 
                        const Artist& dest)
{   
    string quote = "\"";
    stack<Artist> path = map.report_path(source, dest);
    
    if (path.size() == 1) {
        
        out << "A path does not exist between " << quote << source.get_name() 
            << quote << " and " << quote << dest.get_name() << quote << ".\n";
            
    } else {
            
        while (path.size() != 1) {
            Artist topArtist = path.top();
            string topName = topArtist.get_name();   
            path.pop();
            Artist nextName = path.top();
            
            out << quote << topName << quote << " collaborated with "
                << quote << nextName << quote << " in " << quote << 
                map.get_edge(topName, nextName) << quote << ".\n";
            
            if (path.size() == 1)
                out << "***\n";
        }
        
    }
}


