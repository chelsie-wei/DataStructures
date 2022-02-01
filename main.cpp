/*
 * main.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * by chelsie wei, 2021/12/1
 *
 * Purpose: interactive implementation for SixDegrees program where it opens 
 *          and closes input files through command line. If file cannot be 
 *          opened, appropriate message is printed and program terminates 
 *          Calls SixDegrees run command and initialize graph command. 
 */

 #include <iostream>
 #include <fstream>
 #include <string>

 #include "SixDegrees.h"

using namespace std;
template<typename streamtype>
void openOrDie(streamtype &stream, string fileName);

int main(int argc, char *argv[])
{
    ifstream artist_txt, commandName;
    ofstream outstream;    
    SixDegrees start;
    
    if ((argc < 2) or (argc > 4)) {
        cerr << "Usage: SixDegrees dataFile [commandFile] [outputFile]\n";
    } else if (argc == 2) {
        openOrDie(artist_txt, argv[1]);
        start.initializeGraph(artist_txt);
        start.run(cin, cout);
    } else if (argc == 3) {
        openOrDie(artist_txt, argv[1]);
        openOrDie(commandName, argv[2]);
        start.initializeGraph(artist_txt);
        start.run(commandName, cout);
        commandName.close();
    } else if (argc == 4) {
        openOrDie(artist_txt, argv[1]);
        openOrDie(commandName, argv[2]);
        openOrDie(outstream, argv[3]);
        start.initializeGraph(artist_txt);
        start.run(commandName, outstream);
        commandName.close();
    }
    
    artist_txt.close();
    outstream.close();
    
    return 0;
}

template<typename streamtype>
void openOrDie(streamtype &stream, string fileName)
{
    stream.open(fileName);

    if (not stream.is_open()) {
        cerr << fileName << " cannot be opened." << endl;
        exit(EXIT_FAILURE);
    }
}
