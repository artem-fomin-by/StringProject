#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Krit4.h"

using namespace std;

string GetTextFromFile(const string& filepath)
{
    auto fin = ifstream(filepath);
    string text = " ";
    int i = 0;
    while(!fin.eof())
    {
        string line;
        getline(fin, line);
        text += line + ' ';
    }
    fin.close();

    return text;
}

vector<StatsElem> GetStats(const string& text, SourceFile& source)
{
    char systemSymbol;
    source.Fin >> systemSymbol;

    auto stats = vector<StatsElem>();
    while(systemSymbol != source.FileEnding)
    {
        int cur = 0;
        string letters;
        bool first = true;
        do
        {
            string toFind;
            source.Fin >> toFind;
            if(first)
            {
                letters = toFind;
                first = false;
            }

            auto index = text.find(toFind);
        	while(index != string::npos)
        	{
                index = text.find(toFind, index + 1);
                cur += systemSymbol == source.Negator ? -1 : 1;
        	}

        	source.Fin >> systemSymbol;
        } while(systemSymbol != source.GroupBeginning && systemSymbol != source.FileEnding);

        stats.push_back({ letters, cur });
    }

    return stats;
}

int Solve
(
    const string& sourceFilepath, 
    const string& inputFilepath, 
    const string& outputFilepath, 
    const char separator
){
	auto text = GetTextFromFile(inputFilepath);

    auto source = SourceFile(sourceFilepath);

    auto stats = GetStats(text, source);

    auto outputFile = ofstream(outputFilepath);

    int wordsCount = 0;
    for(auto beginning : source.WordBeginnings)
    {
	    auto index = text.find(beginning);
		while(index != string::npos)
		{
			wordsCount++;
			index = text.find(beginning, index + 1);
		}
    }
    wordsCount--;

    for(auto& stat : stats)
    {
        outputFile << stat.Word << separator << (double)stat.Count / wordsCount << '\n';
    }

    outputFile.close();

    return 0;
}

#ifndef MAIN_EXCLUDED
int main()
{
    const string sourceFilepath = "source.txt";
    constexpr char separator = ';';

    string inputFilepath, outputFilepath;
    getline(cin, inputFilepath);
    getline(cin, outputFilepath);

    return Solve(sourceFilepath, inputFilepath, outputFilepath, separator);
}
#endif
