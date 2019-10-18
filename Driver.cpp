#include <iostream>
#include "Spell.h"

using namespace std;

int main()
{
    Spell Sp;
    
    // Spell();
    Sp.readVFile("vocabulary.txt");
    Sp.readInFile("misspelling.csv");
    Sp.spellChecker();
    return 0;
}
