//
//  Project 1 Starter Code - DNA Profiling
//  TODO:  Put your header info here.  Update line above.
//  
//

#include "ourvector.h"
#include <iostream>
#include <fstream> // read files
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    //TODO:  Write your code here.  You should have LOTS of function decomposition.
    ifstream myfile;   // read file input from Linux commands
    string uCommand, line;
    ourvector<string> DNAstrand;

    cout << "Welcome to the DNA Profiling Application.\n";

    while(uCommand != "#"){
        // ask user for command
        cout << "Enter command or # to exit: ";
        cin >> uCommand;

        // Command: load_db <filename>
        if(){
            // file error
            // if(argc != 2){
            //     cout << "usage: ./freq <filename>\nFile error\n";
            //     return 1;
            // }

            // can not open file
            if(!myfile.is_open()){
                cout << "Error: could not open file '" << argv[1] << "'\n";
                return 1;
            }

            // open file
            if(myfile.is_open()){
                getline(myfile, line);
                myfile.close();
            }
            
            cout << "Loading database...\n";
        }
        // Command: display
        else if(){
            //
        }
        // Command: load_dna
        else if(){
            //
        }
        // Command: process
        else if(){
            //
        }
        // Command: search
        else if(){
            //
        }
        else {
            // Unknown command
            cout << "Unknown command. Please try either:\nload_db <filename>\ndisplay\nload_dna\nprocess\nsearch\n";
        }
        
    }

    return 0;
}
