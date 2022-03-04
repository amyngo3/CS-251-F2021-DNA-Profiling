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
    ourvector<int> processedDNA;    // STR count for processed command

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
                // loop words in first line
                for(int i = 5; i < line.length(); i++){
                    // if found comma, push vector of DNA sequence
                    if(line[i] == ','){
                        DNAsequence.push_back(v);
                        v.clear();
                    }
                    // if not comma
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

            if(!processedDNA.size())
                cout << "\nNo DNA has been processed.\n";
            else {
                cout << "\nDNA processed, STR counts:\n";
                // loop indices of DNAsequence
                for(int i = 0; i < DNAsequence.size(); i++){
                    // loop letters of DNAsequence
                    for(int j = 0; j < DNAsequence[i].size(); j++){
                        cout << DNAsequence[i][j];
                    }
                    cout << ": ";
                    // print sequence's number
                    cout << processedDNA[i] << endl;
                }
            }
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
            // if database is loaded
            if(DNAsequence.size()){
                // O(n^3)
                // loop number of DNAsequence patterns (not letters yet)
                for(int i = 0; i < DNAsequence.size(); i++){
                    int counter = 0;
                    // frequency of sequence
                    int sequenceNum = 0;
                    // loop DNAsequence letters
                    for(int j = 0; j < DNAstrand.size(); j++){
                        // loop number of DNAstrand to compare with DNAsequence
                        for(int k = 0; k < DNAsequence[i].size(); k++){
                            // if index of DNAstrand has exact letter with index of DNAsequence
                            // j for current index of DNAstrand plus k for index number of DNAsequence
                            if(j+k < DNAstrand.size())
                                if(DNAstrand[j+k] == DNAsequence[i][k])
                                    counter++;
                        }
                        if(counter == DNAsequence[i].size())
                            sequenceNum++;
                        // reset counter to check for next sequence
                        counter = 0;
                    }
                    // push counter in processedDNA
                    processedDNA.push_back(sequenceNum);
                }

                cout << "Processing DNA...\n";
            }
            // no database loaded
            else {
                cout << "No database loaded.\n";
            }

            // if DNA is loaded
            if(!DNAstrand.size())
                cout << "No DNA loaded.\n";
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
