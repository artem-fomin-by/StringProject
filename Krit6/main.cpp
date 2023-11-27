#include<iostream>
#include<fstream>
#include<windows.h>
#include<vector>
using namespace std;
string ru_big, ru_small, vowels={-32,-27,-24,-18,-13,-5,-3,-2,-1,-72};
char ru_tolower(char c)
{
    int x = ru_big.find(c);
    if(x == string::npos)return c;
    else return ru_small[x];
}
void clear_all_bad_symbols(string &s)
{
    string result;
    for(auto &x : s)
    {
        if(ru_small.find(x) != string::npos)result += x;
    }
    s = result;
}
int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  for(int i = -64; i <= -33; i++) ru_big += i;
  ru_big+=-88;
  for(int i = -32; i <= -1; i++) ru_small += i;
  ru_small += -72;
  for(int i = 1; i <= 4; i++)
    for(auto &x : {"s", "l"})
    {
        string file_name = to_string(i) + "_" + x + ".txt";
        ifstream fin(file_name);
        vector<int> result(4);
        int word_amount = 0;
        string s;
        while(fin >> s)
        {
            for(auto &x : s)x = ru_tolower(x);
            clear_all_bad_symbols(s);
            if(s.size() == 0)continue;
            word_amount++;
            result[(vowels.find(s[0]) != string::npos) + (vowels.find(s.back()) != string::npos) * 2]++;
        }
        //СС ГС СГ ГГ
        cout << file_name << ": " << (float)result[0] / word_amount
        << " " << (float)result[1] / word_amount << " " << (float)result[2] / word_amount <<
        " " << (float)result[3] / word_amount << endl;
    }
}
