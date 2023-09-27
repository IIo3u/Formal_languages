#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

bool Find_letter(string stroke, char letter);

class Grammar
{
private:
    class Rule
    {
    public:
        string Lpart;
        string Rpart;
        Rule(string Lpart, string Rpart)
        {
            this->Lpart = Lpart;
            this->Rpart = Rpart;
        };
    };

public:
    string Terminals;
    string NTerminals;
    vector<Rule> RulesArray;
    Grammar(string folder)
    {
        string buffer;
        ifstream FileInput;
        FileInput.open(folder);


        getline(FileInput, buffer);                     // Терминалы
        for (int i = 5; i < buffer.length(); i++)
        {
            if (!(buffer[i] == ','))
            {
                Terminals += buffer[i];
            }
        }


        getline(FileInput, buffer);                     // Нетерминалы
        for (int i = 5; i < buffer.length(); i++)
        {
            if ((64 < buffer[i] < 91) && (buffer[i] != ','))
            {
                NTerminals += buffer[i];
            }
        }


        while (!FileInput.eof())                        // Правила
        {
            getline(FileInput, buffer);
            string Lpart;
            string Rpart;
            int j = buffer.length();

            for (int i = 0; i < j; i++)                 // Левая часть
            {
                if (!(buffer[i] == ' '))
                {
                    Lpart += buffer[i];
                }
                else
                {
                    j = i + 4;
                    break;
                }
            }
            buffer.push_back('|');
            for (int i = j; i < buffer.length(); i++)   // Правая часть
            {
                if (buffer[i] == '|')
                {
                    Rule NewRule(Lpart, Rpart);
                    this->RulesArray.push_back(NewRule);
                    Rpart.clear();
                }
                else
                {
                    Rpart += buffer[i];
                }
            }

        }
    };
    int DefineGrammarType(Grammar NewGram)
    {
        int GrammarType = 0;
        for (int i = 0; i < NewGram.RulesArray.size(); i++)
        {
            string defLpart = NewGram.RulesArray[i].Lpart;
            string defRpart = NewGram.RulesArray[i].Rpart;
            int LLen = defLpart.length();
            int RLen = defRpart.length();
            if (LLen > RLen)
            {
                return GrammarType = 0;
            }
            for (int j = 0; j < LLen; j++)
            {
                if (defLpart[j] == 'E')
                {
                    return GrammarType = 0;
                }
                else
                {
                    if (Find_letter(NewGram.Terminals, defLpart[j]))
                    {
                        return GrammarType = 1;
                    }
                    else
                    {
                        GrammarType = 2;
                    }
                }
            }
            if (RLen < 3)
            {
                if ((RLen == 1) && Find_letter(NewGram.Terminals, defRpart[0]))
                {
                    GrammarType = 3;
                }
                else
                {
                    if ((Find_letter(NewGram.Terminals, defRpart[0]) && Find_letter(NewGram.NTerminals, defRpart[1])) || (Find_letter(NewGram.Terminals, defRpart[1]) && Find_letter(NewGram.NTerminals, defRpart[0])))
                    {
                        GrammarType = 3;
                    }
                    else
                    {
                        GrammarType = 2;
                    }
                }
            }

        }
        return GrammarType;
    };
};

bool Find_letter(string stroke, char letter)
{
    bool statement = false;
    for (int i = 0; i < stroke.length(); i++)
    {
        if (stroke[i] == letter)
        {
            statement = true;
        }
    }
    return statement;
}

int main()
{
    string folder;

    cout << "-----------------------------------------------\n";
    cout << "Language: L(G) = {a^n * b^m * c^k | n,m,k > 0}\n";
    cout << "-----------------------------------------------\n";

    cout << "Example:\n" << "Vt = a,b,c\n" << "Vn = A,B,C,S\n" << "A -> aA|E\n" << "AB -> bBa\n" << "etc.\n";
    cout << "-----------------------------------------------\n";
    cout << "Input Grammatics file folder: ";
    cin >> folder;

    Grammar NewGram(folder);


    cout << "-----------------------------------------------\n";
    cout << "Yours grammatics:\n";

    string out;

    cout << "Vt = ";
    for (int i = 0; i < NewGram.Terminals.length(); i++)
    {
        out += NewGram.Terminals[i];
        out += ",";
    }
    out.pop_back();
    cout << out << endl;
    out = "";

    cout << "Vn = ";
    for (int i = 0; i < NewGram.NTerminals.length(); i++)
    {
        out += NewGram.NTerminals[i];
        out += ",";
    }
    out.pop_back();
    cout << out << endl;


    for (int i = 0; i < NewGram.RulesArray.size(); i++)
    {
        cout << NewGram.RulesArray[i].Lpart << " -> " << NewGram.RulesArray[i].Rpart << endl;
    }

    cout << "-----------------------------------------------\n";
    cout << "Your grammar type: " << NewGram.DefineGrammarType(NewGram) << endl;
    cout << "-----------------------------------------------\n";
}