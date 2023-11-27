#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string s, glas, sogl;
    ifstream lin("rus_letters.txt");
    lin >> glas;
    lin >> sogl;
    vector <string> files = {"1_l", "1_s", "2_l", "2_s", "3_l", "3_s", "4_l", "4_s"};
    for (int i = 0; i < 8; i++){
    cout << files[i] + ".txt\n";
    ifstream fin(files[i] + ".txt");
    ofstream fout(files[i] + "_stat.txt");

    fout << setprecision(10);
    int c_g = 0, c_s = 0, c_l = 0;
    while (fin >> s){
        for (auto i : s){
            if (glas.find(i) != string::npos){
                c_g++; c_l++;
            }
            else if (sogl.find(i) != string::npos){
                c_s++; c_l++;
            }
        }
    }
    fout << "процент гласных: " << c_g * 1. / c_l * 100 << '\n';
    fout << "процент согласных: " << c_s * 1. / c_l  * 100 << '\n';

    cout << "процент гласных: " << c_g * 1. / c_l * 100 << '\n';
    cout << "процент согласных: " << c_s * 1. / c_l * 100 << '\n';
    }
    return 0;
}
