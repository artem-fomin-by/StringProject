#include<iostream>
#include<fstream>
#include<windows.h>
#include<time.h>
using namespace std;
long long int mod = 1e16 + 20,k=37;
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
long long int calculate_polynominal_hash(string s)
{
    long long int hash_value = 0;
    long long int current_power = 1;
    for(auto &x : s)
    {
        hash_value += (ru_small.find(x) + 1) * current_power;
        hash_value %= mod;
        current_power = (current_power * k) % mod;
    }
    return hash_value;
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
        __int128 hash_sum = 0;
        string s;
        while(fin >> s)
        {
            for(auto &x : s)x = ru_tolower(x);
            clear_all_bad_symbols(s);
            if(s.size() == 0)continue;
            word_amount++;
            hash_sum += calculate_polynominal_hash(s);
        }
        cout << file_name << " mid hash " << (long long int)(hash_sum / word_amount) << endl;
    }
}
