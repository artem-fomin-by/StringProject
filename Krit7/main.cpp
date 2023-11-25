#include <fstream>

using namespace std;

const int N = 2 * 1e5;

int main()
{
    ofstream cout("output.txt");
    for (int i = 1; i <= 4; i++){
        for (auto ch : {"s", "l"}){
            string file_name = to_string(i) + "_" + ch + ".txt";
            ifstream cin(file_name);
            string g = "óåûàîýÿèþ";
            string sg = "éöêíãøùçõôâïðëäæ÷ñìòá";
            int all = 0, good1 = 0, good2 = 0;
            string s;
            while (getline(cin, s)){
                int sz = (int)s.size() - 2;
                for (int i = 0; i < sz; i++){
                    s[i] = tolower(s[i]);
                    if (g.find(s[i]) == string::npos && sg.find(s[i]) == string::npos)continue;
                    all++;
                    if (g.find(s[i]) != string::npos && g.find(s[i + 1]) != string::npos && g.find(s[i + 2]) != string::npos)good1++;
                    else if (sg.find(s[i]) != string::npos && sg.find(s[i + 1]) != string::npos && sg.find(s[i + 2]) != string::npos)good2++;
                }
            }
            cout << file_name << ": " << double(good1) / double(all) * 100 << '%' << "      " << double(good2) / double(all) * 100 << "%" << endl;
            cin.close();
        }
    }
	return 0;
}
