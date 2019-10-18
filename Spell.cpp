#include "Spell.h"

Spell::Spell()
{
    // words.resize(0);
    // unknown = false;
    // whichRow = 1;
}

void Spell::readInFile(string fileName)
{
    ifstream inFile;
    inFile.open(fileName);
    
    string right;
    string s;
    string holdMis;
    vector<string> wrong;
    int countWords = 0;
    
    if (inFile.is_open())
    {
        while (getline(inFile, right, ','))
        {
            countWords++;
            getline(inFile, s);
            for (int i = 0; i < s.length(); i++)
            {
                if (s[i] == '|')
                {
                    wrong.push_back(holdMis);
                    holdMis = "";
                }
                else
                {
                    holdMis = holdMis + s[i];    
                }
            }
            wrong.push_back(holdMis);
            holdMis = "";
            holdMap.insert(make_pair(right, wrong));
            wrong.resize(0);
        }
        cout << "Read " << countWords << " words from " << fileName << endl;
    }
    else
    {
        cout << "<" << fileName << "> does not exist" << endl;   
    }
}

void Spell::readVFile(string fileName)
{
    ifstream inFile;
    inFile.open(fileName);
    
    string s;
    int countWords = 0;
    
    if (inFile.is_open())
    {
        while (getline(inFile, s))
        {
            vocab.push_back(s);
            countWords++;
        }
        cout << "Read " << countWords << " words from " << fileName << endl;
    }
    else
    {
        cout << "<" << fileName << "> does not exist" << endl;    
    }
}

void Spell::readOutFile(string fileName, string input)
{
    ofstream outFile;
    outFile.open(fileName, ios::out | ios::app);
    
    if (outFile.is_open())
    {
        outFile << input;
    }
    else
    {
        cout << "<" << fileName << "> does not exist" << endl;  
    }
}

void Spell::spellChecker()
{
    string s, hold, punc;
    vector<string> sentence;
    vector<string> updated;
    bool pass = false;
    bool onList = false;
    cout << "Enter the phrase you would like to correct:" << endl;
    getline(cin, s);
    
    for (int i = 0; i < s.length(); i++)
    {
        if (((s[i] > 9 && s[i] < 48) || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || (s[i] > 122)) && sentence.size() != 0)
        {
            sentence.push_back(hold);
            if (s[i] == ' ' && punc[punc.size()-1] != ' ')
            {
                punc = punc + s[i];
            }
            else if (s[i] != ' ')
            {
                punc = punc + s[i];
            }
            hold = "";
        }
        else if ((s[i] <= 'Z' && s[i] >= 'A') || (s[i] <= 'z' && s[i] >= 'a') || (s[i] > 47 && s[i] < 58))
        {
            sentence.push_back(punc);
            s[i] = tolower(s[i]);
            hold = hold + s[i];
            punc = "";
        }
    }
    sentence.push_back(hold);
    sentence.push_back(punc);
    for (int indx = 0; indx < sentence.size(); indx++)
    {
        pass = false;
        for (auto it = holdMap.cbegin() ; it != holdMap.cend() ; it++)
        {
            if (sentence[indx] == it->first)
            {
                updated.push_back(sentence[indx]);
                pass = true;
                for (int i = 0; i < vocab.size(); i++)
                {
                    if (sentence[indx] == vocab[i])
                    {
                        onList = true;
                    }
                }
                if (onList == false)
                {
                    readOutFile("vocabulary.txt", sentence[indx]);
                }
            }
            for (auto vec_it = it->second.cbegin() ; vec_it != it->second.cend() ; vec_it++)
            {
                if (sentence[indx] == *vec_it)
                {
                    updated.push_back(it->first);
                    pass = true;
                }
            }
        }
        if (pass == false)
        {
            for (int i = 0; i < vocab.size(); i++)
            {
                if (sentence[indx] == vocab[i])
                {
                    updated.push_back(sentence[indx]);
                    pass = true;
                }
            }
        }
        if (pass == false && ((sentence[indx][0] <= 'Z' && sentence[indx][0] >= 'A') || (sentence[indx][0] <= 'z' && sentence[indx][0] >= 'a')))
        {
            updated.push_back("unknown");
        }
        else if (pass == false)
        {
            updated.push_back(sentence[indx]);
        }
    }
    for (int i = 0; i < updated.size(); i++)
        cout << updated[i];
}
