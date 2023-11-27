#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Krit3.h"

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

vector<StatsElem> GetStats(const string& text, SourceFile& source, int& overallPrepsCount)
{
    char systemSymbol;
    source.Fin >> systemSymbol;

	overallPrepsCount = 0;
    auto prepsCounts = vector<StatsElem>();
    while(systemSymbol != source.FileEnding)
    {
        int cur = 0;
        string prep;
        bool first = true;
        do
        {
            string toFind;
            source.Fin >> toFind;
            if(first)
            {
                prep = toFind;
                first = false;
            }
            toFind = ' ' + toFind;

            auto index = text.rfind(toFind);
        	while(index != string::npos)
        	{
        		if(source.WordEndings.find(text[index + toFind.size()]) != string::npos)
        		{
                    cur++;
        		}
                if(index == 0)
                {
	                break;
                }

                index = text.rfind(toFind, index - 1);
        	}

        	source.Fin >> systemSymbol;
        } while(systemSymbol != source.GroupBeginning && systemSymbol != source.FileEnding);

        overallPrepsCount += cur;
        prepsCounts.push_back({ prep, cur });
    }

    return prepsCounts;
}

int Solve
(
    const string& sourceFilepath, 
    const string& inputFilepath, 
    const string& outputFilepath,
	char separator
){
    auto text = GetTextFromFile(inputFilepath);

    auto source = SourceFile(sourceFilepath);

    int overallPrepsCount;
    auto stats = GetStats(text, source, overallPrepsCount);

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
        outputFile << stat.Word << separator;
        outputFile << (double)stat.Count / overallPrepsCount << separator;
        outputFile << (double)stat.Count / wordsCount << '\n';
    }

    outputFile.close();

    return 0;
}

#ifndef MAIN_EXCLUDED
int main()
{
    const string sourceFilepath = "source.txt";
    constexpr char Separator = ';';

    string inputFilepath, outputFilepath;
    getline(cin, inputFilepath);
    getline(cin, outputFilepath);
    return Solve(sourceFilepath, inputFilepath, outputFilepath, Separator);
}
#endif
