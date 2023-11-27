#include<iostream>
#include<fstream>
#include<windows.h>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
string ru_big, ru_small;
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
        int word_amount = 0;
        string s;
        map<string, int>mp;
        while(fin >> s)
        {
            for(auto &x : s)x = ru_tolower(x);
            clear_all_bad_symbols(s);
            if(s.size() <= 3)continue;
            word_amount++;
            mp[s]++;
        }
        vector<pair<int,string>>v;
        for(auto &x : mp) v.push_back({x.second, x.first});
        sort(v.rbegin(), v.rend());
        cout << file_name << ":" << endl;
        for(int i = 0; i < 10; i++)
        {
            cout << i + 1 << ". " << v[i].second << " " << (float)v[i].first / word_amount << endl;
        }
    }
}
