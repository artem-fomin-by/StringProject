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
    string s, s_z, s_g, all_let;
    ifstream lin("rus_letters.txt");
    lin >> s_z >> s_g >> all_let;
    vector <string> files = {"1_l", "1_s", "2_l", "2_s", "3_l", "3_s", "4_l", "4_s"};
    for (int i = 0; i < 8; i++){
    cout << files[i] + ".txt\n";
    ifstream fin(files[i] + ".txt");
    ofstream fout(files[i] + "_stat.txt");

    fout << setprecision(10);
    int c_z = 0, c_g = 0, c_s = 0, a_l = 0;
    while (fin >> s){
        for (auto i : s){
            if (all_let.find(i) != string::npos){
                    a_l++;
            if (s_z.find(i) != string::npos){
                c_z++; c_s++;
            }
            else if (s_g.find(i) != string::npos){
                c_g++; c_s++;
            }
            }
        }
    }
    fout << "количество звонких согласных " << c_z << "\nпроцент звонких среди согласных: " << c_z * 1. / c_s * 100 << "\nпроцент среди всех:" << c_z * 1. / a_l * 100 << '\n';
    fout << "количество глухих согласных " << c_g << "\nпроцент глухих среди согласных: " << c_g * 1. / c_s  * 100 << "\nпроцент среди всех:" << c_g * 1. / a_l * 100 << '\n';

    cout << "количество звонких согласных " << c_z << "\nпроцент звонких среди согласных: " << c_z * 1. / c_s * 100 << "\nпроцент среди всех:" << c_z * 1. / a_l * 100 << '\n';
    cout << "количество глухих согласных " << c_g << "\nпроцент глухих среди согласных: " << c_g * 1. / c_s  * 100 << "\nпроцент среди всех:" << c_g * 1. / a_l * 100 << '\n';

}
    return 0;
}
