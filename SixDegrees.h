/*
 * SixDegrees.h
 * Name: Chelsie Wei 
 * Date: 12/5/2021
 * Purpose: SixDegrees interface with public and private functions that are 
 *          implemented in .cpp file. 
 */
 
 #ifndef _SIXDEGREES_H_
 #define _SIXDEGREES_H_
 
 #include "CollabGraph.h"
 #include "Artist.h"
 
 #include <sstream>
 #include <iostream>
 #include <vector>
 
 using namespace std;
 
 class SixDegrees {
     
    public:
    SixDegrees();
    ~SixDegrees();
    
    void run(istream &input, ostream &output);
    void initializeGraph(istream &input);
     
    private:
    
    void ifBFS(istream &input, ostream &output);
    void bfsTraverse(const Artist& source, const Artist& dest, ostream &out);
    void output(ostream &out, const Artist& source, const Artist& dest);
    void ifPrint(ostream &output);
    void ifDFS(istream& input, ostream &out);
    void dfsTraverse(const Artist& source, const Artist& dest, ostream &out);
    int checkVertex(const Artist& source, const Artist& dest);
    void ifUnknown(const Artist& source, const Artist& dest, ostream &out);
    void printUnknown(const Artist& artist, ostream& out);
    void dfsHelper(const Artist& curr, const Artist& source, 
                   const Artist& dest);
    void ifNot(istream &input, const Artist& source, const Artist& dest, 
               ostream &out);
    stack<Artist> checkNots(const stack<Artist>& stack);
    
    
    CollabGraph map;
     
 };
 
 #endif