#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#ifndef Spell_H
#define Spell_H

using namespace std;


class Spell
{
public:
    Spell();
    void readInFile(string fileName);
    void readVFile(string fileName);
    void readOutFile(string fileName, string input);
    void spellChecker();
    void setWords(string fresh);
    string getWords(int indx);
    
private:
    // bool unknown;
    unordered_map<string , vector<string> > holdMap;
    vector<string> vocab;
};

#endif
