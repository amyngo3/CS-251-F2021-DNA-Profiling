//
//  Project 1 Starter Code - DNA Profiling
//  TODO:  Put your header info here.  Update line above.
//  Amy Ngo - This project is from UIC's CS 251 Fall 2021. I was given this
//  code is only for practice without using GradeScope, DO NOT plagarize my work!

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

int main() {
    //TODO:  Write your code here.  You should have LOTS of function decomposition.
    ifstream myfile;   // read file input
    string uCommand, filename;
    ourvector<char> DNA;
    ourvector<ourvector<char>> strand;    // DNA pattern from small.txt or large.txt
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

            // file error
            if(!myfile){
                cout << "\n\tError: unable to open \'" << filename << "\'" << endl;
            }
            // open file
            else {
                // when called again, must clear DNAsequence to repopulate
                strand.clear();

                string line;
                getline(myfile, line);  // gets only first line in text file
                ourvector<char> v;
                // loop words in first line
                for(int i = 5; i < line.length(); i++){
                    // if found comma, push vector of DNA sequence
                    if(line[i] == ','){
                        strand.push_back(v);
                        v.clear();
                    }
                    // if not comma
                    if(line[i] != ','){
                        // push letter
                        v.push_back(line[i]);
                    }
                }
                strand.push_back(v);

                // clear people vector, must clear people to repopulate
                people.clear();

                // store people in database
                string buffer;
                while(getline(myfile, line)){
                    Person p;
                    stringstream ss(line);  // gets 1 line of (name, number[s])

                    getline(ss, buffer, ','); // get name
                    p.name = buffer;
                    
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

            if(!DNA.size())
                cout << "\nNo DNA loaded.\n";
            else {
                cout << "\nDNA Loaded:\n";
                for(char c : DNA){
                    cout << c;
                }
                cout << endl;
            }

            if(!processedDNA.size())
                cout << "\nNo DNA has been processed.\n";
            else {
                // check if DNAsequence size matches processedDNA size
                if(strand.size() != processedDNA.size())
                    cout << "\nError: database and/or processed DNA are not loaded properly.\n";
                else {
                    cout << "\nDNA processed, STR counts:\n";
                    // loop indices of DNAsequence
                    for(int i = 0; i < strand.size(); i++){
                        // loop letters of DNAsequence
                        for(int j = 0; j < strand[i].size(); j++){
                            cout << strand[i][j];
                        }
                        cout << ": ";
                        // print sequence's number
                        cout << processedDNA[i] << endl;
                    }
                    cout << endl;
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
                // when called again, must clear DNAstrand to repopulate
                DNA.clear();

                string line;
                getline(myfile, line);
                for(char c : line){
                    DNA.push_back(c);
                }
                cout << "Loading DNA...\n";
            }
            myfile.close();
        }
        // Command: process
        else if(uCommand == "process"){
            // if DNA is not loaded
            if(!DNA.size())
                cout << "No DNA loaded.\n";
            else {
                // if database is loaded
                if(strand.size()){
                    // when called again, must clear userDB to repopulate
                    processedDNA.clear();
                    // O(n^3)
                    // loop number of DNAsequence patterns (not letters yet)
                    for(int i = 0; i < strand.size(); i++){
                        int currentStrandCount = 0;
                        int maxStrandCount = 0;
                        // loop DNAstrand letters
                        for(int j = 0; j <= DNA.size()-strand[i].size(); j++){
                            int counter = 0;
                            // loop number of DNAsequence to compare with DNAstrand
                            for(int k = 0; k < strand[i].size(); k++){
                                // if index of DNAstrand has exact letter with index of DNAsequence
                                // j for current index of DNAstrand plus k for index number of DNAsequence
                                if(DNA[j+k] == strand[i][k])
                                    counter++;
                            }
                            if(counter == strand[i].size()){
                                currentStrandCount++;
                                j += strand[i].size() - 1;
                            }
                            else
                                currentStrandCount = 0;
                            if(currentStrandCount > maxStrandCount)
                                maxStrandCount = currentStrandCount;
                        }
                        // push counter in processedDNA
                        processedDNA.push_back(maxStrandCount);
                    }
                    cout << "Processing DNA...\n";
                }
                // no database not loaded
                else {
                    cout << "No database loaded.\n";
                }
            }
        }
        // Command: search
        else if(uCommand == "search"){
            // if DNAsequence is not loaded
            if(!strand.size())
                cout << "No database loaded.\n";

            // if DNA is not loaded
            if(!DNA.size())
                cout << "No DNA loaded.\n";
            
            if(!processedDNA.size())
                cout << "No DNA processed.\n";
            else{
                cout << "Searching database...\n";
                int counter = 0;
                // search processedDNA and people that matches the processed DNA
                // loop people vector
                for(int i = 0; i < people.size(); i++){
                    // loop processedDNA vector
                    for(int j = 0; j < processedDNA.size(); j++){
                        // if processedDNA count is the same as the current person's DNA count
                        if(processedDNA[j] == people[i].frequency[j])
                            counter++;
                    }
                    // if found person in database
                    if(counter == processedDNA.size()){
                        cout << "Found in database!  DNA matches: " << people[i].name << endl;
                        break;
                    }
                    // reset counter
                    counter = 0;
                }
                if(counter != processedDNA.size())
                    // if person not in database
                    cout << "Not found in database\n";
            }
        }
        // Exit command
        else if(uCommand == "#"){
            break;
        }
        // Unknown command
        else {
            cout << "Unknown command. Please try either:\nload_db <filename>\ndisplay\nload_dna\nprocess\nsearch\n";
            cout << "\tNote: The filename should be typed as named in the folder.\n";
        }
    }

    return 0;
}
