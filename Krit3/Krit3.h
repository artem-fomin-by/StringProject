#pragma once

#include <fstream>
#include <string>

struct StatsElem
{
    std::string Word;
    int Count;
};

class SourceFile
{
	public:
    std::string Path;
    std::string WordEndings;
    std::string WordBeginnings;
    char GroupBeginning;
    char WordsSeparator;
    char FileEnding;
    std::ifstream Fin;

    SourceFile(const std::string& path)
    {
        Path = path;
        Fin = std::ifstream(path);
        std::getline(Fin, WordBeginnings);
        std::getline(Fin, WordEndings);
        Fin >> GroupBeginning >> WordsSeparator >> FileEnding;
    }

    SourceFile(const SourceFile& file) : SourceFile(file.Path) { }

    void Close()
    {
        Fin.close();
    }

    ~SourceFile()
    {
        Close();
    }
};
