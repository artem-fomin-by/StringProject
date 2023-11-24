#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    const string wordsSourceFilepath = "source.txt";
    constexpr char Separator = ';';

    string filepath, outputFilepath;
    getline(cin, filepath);
    getline(cin, outputFilepath);

    auto file = ifstream(filepath);
    string text = "";
    int i = 0;
    while(!file.eof())
    {
        string line;
        getline(file, line);
        for(char c : line)
        {
            cout << (int)c << '\n';
        }

        text += line;
    }
    file.close();

    auto wordsSourceFile = ifstream(wordsSourceFilepath);
    char normal;
    wordsSourceFile >> normal;
    char special;
    wordsSourceFile >> special;

    auto outputFile = ofstream(outputFilepath);

    while(!wordsSourceFile.eof())
    {
        char beginning;
        wordsSourceFile >> beginning;

        int cur = 0;
        string prep;
        wordsSourceFile >> prep;

        auto index = text.find(prep, 0);
        while(index != string::npos)
        {
            cur++;
            index = text.find(prep, index);
        }

        if(beginning == special)
        {
            wordsSourceFile >> prep;
            auto index = text.find(prep, 0);
            while(index != string::npos)
            {
                cur++;
                index = text.find(prep, index);
            }
        }

        outputFile << prep << Separator << cur << '\n';
    }

    wordsSourceFile.close();
    outputFile.close();

    return 0;
}
