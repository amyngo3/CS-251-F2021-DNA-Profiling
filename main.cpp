//
//  Project 1 Starter Code - DNA Profiling
//  TODO:  Put your header info here.  Update line above.
//  
//

#include "ourvector.h"
#include <iostream>
#include <fstream> // read files
#include <sstream>
#include <string>

using namespace std;

struct Person{
    string name;
    ourvector<int> frequency;
};

int main(/*int argc, char *argv[]*/) {
    //TODO:  Write your code here.  You should have LOTS of function decomposition.
    ifstream myfile;   // read file input
    string uCommand, filename;
    ourvector<char> DNAstrand;
    ourvector<ourvector<char>> DNAsequence;    // DNA pattern from small.txt or large.txt
    ourvector<Person> people;   // list of people in text file

    cout << "Welcome to the DNA Profiling Application.\n";

    while(uCommand != "#"){
        cout << "Enter command or # to exit: ";
        // ask user for command
        cin >> uCommand;

        // Command: load_db <filename>
        if(uCommand == "load_db"){
            // get specific file name
            cin >> filename;

            myfile.open(filename);
            // when called again, must clear userDB to repopulate
            DNAsequence.clear();

            // file error
            if(!myfile){
                cout << "\n\tError: unable to open \'" << filename << "\'" << endl;
            }
            // open file
            else {
                string line;
                getline(myfile, line);  // gets only first line in text file
                ourvector<char> v;
                for(int i = 5; i < line.length(); i++){
                    if(line[i] == ','){
                        DNAsequence.push_back(v);
                        v.clear();
                    }
                    if(line[i] != ','){
                        // push letter
                        v.push_back(line[i]);
                    }
                }
                DNAsequence.push_back(v);

                // for(int i = 0; i < DNAsequence.size(); i++){
                //     for(int j = 0; j < DNAsequence[i].size(); j++){
                //         cout << DNAsequence[i][j];
                //     }
                //     cout << endl;
                // }

                // store people in database
                string buffer;
                while(getline(myfile, line)){
                    Person p;
                    // cout << "line: " << line << endl;   // whole single line
                    stringstream ss(line);  // gets 1 line of (name, number[s])

                    getline(ss, buffer, ','); // get name
                    p.name = buffer;
                    
                    // cout << buffer << endl; // names
                    while(getline(ss, buffer, ',')){
                        p.frequency.push_back(stoi(buffer));    // push int
                    }
                    people.push_back(p);    // store person in ourvector
                }
                cout << "Loading database...\n";
            }
            myfile.close();
        }
        // Command: display
        else if(uCommand == "display"){
            //
            if(people.size()){
                cout << "Database loaded:\n";
                for(int i = 0; i < people.size(); i++){
                    cout << people[i].name << " "; 
                    for(int j = 0; j < people[i].frequency.size(); j++){
                        cout << people[i].frequency[j] << " ";
                    }
                    cout << endl;
                }
            } else {
                cout << "\nNo database loaded.\n";
            }

            if(!DNAstrand.size())
                cout << "\nNo DNA loaded.\n";
            else {
                cout << "\nDNA Loaded:\n";
                for(char c : DNAstrand){
                    cout << c;
                }
                cout << endl;
            }

            // cout << "\nNo DNA has been processed\n";
        }
        // Command: load_dna
        else if(uCommand == "load_dna"){
            // get specific file name
            cin >> filename;

            myfile.open(filename);
            if(!myfile){
                cout << "\n\tError: unable to open \'" << filename << "\'"<< endl;
            } else {
                string line;
                getline(myfile, line);
                for(char c : line){
                    DNAstrand.push_back(c);
                }
                cout << "Loading DNA...\n";
            }
            myfile.close();
        }
        // Command: process
        else if(uCommand == "process"){
            //
        }
        // Command: search
        // else if(){
        //     //
        // }
        else if(uCommand == "#"){
            break;
        }
        else {
            // Unknown command
            cout << "Unknown command. Please try either:\nload_db <filename>\ndisplay\nload_dna\nprocess\nsearch\n";
            cout << "\tNote: The filename should be typed as named in the folder.\n";
        }
    }

    return 0;
}
