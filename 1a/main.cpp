#include <iostream>
#include <windows.h>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string s, let, let_b;
    ifstream lin("rus_letters.txt");
    lin >> let;
    lin >> let_b;
    vector <string> files = {"1_l", "1_s", "2_l", "2_s", "3_l", "3_s", "4_l", "4_s"};
    for (int i = 0; i < 8; i++){
    cout << files[i] + ".txt\n";
    ifstream fin(files[i] + ".txt");
    ofstream fout(files[i] + "_stat.txt");
    map <char, int> m;
    int c_l = 0;
    while (fin >> s){
        for (auto i : s){
            if (let.find(i) != string::npos)
                m[i]++;
            else{
                int pos = let_b.find(i);
                if(pos != string::npos)
                    m[let[pos]]++;
            }
        }
    }
    vector <pair<char,int>> v;
    for (auto [key, value] : m){
        v.push_back({key, value});
        c_l += value;
    }
    sort(v.begin(), v.end());
    for (auto i : v){
        double pers = i.second * 1. / c_l;
        fout << i.first << ' ' << i.second  << ' ' << pers << '\n';
        cout << i.first << ' ' << i.second  << ' ' << pers << '\n';
    }
    }
    return 0;
}
