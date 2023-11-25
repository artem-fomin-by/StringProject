#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

const string letters = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿ";
const string gl = "áïâôäòçñæø÷öùãêõìíëğ";

bool is_gl(char c) {
    return gl.find(tolower(c)) != gl.npos;
}

bool is_sogl(char c) {
    return letters.find(c) != letters.npos && !is_gl(c);
}

bool is_word(string word) {
    if (word.size() < 2) {
        return false;
    }

    bool have_letter = false;

    for (int i = 0; i < word.size(); i++) {
        have_letter |= letters.find(word[i]) != letters.npos;
    }
    return have_letter;
}

string parse(string word) {
    while (word.size()) {
        if (letters.find(word.back()) != letters.npos) {
            break;
        }
        word.pop_back();
    }
    reverse(word.begin(), word.end());
    while (word.size()) {
        if (letters.find(word.back()) != letters.npos) {
            break;
        }
        word.pop_back();
    }
    reverse(word.begin(), word.end());
    return word;
}

int check_begin(string word) {
    int result = 0;
    for (int i = 0; i < word.size(); i++) {
        if (!is_sogl(word[i])) {
            break;
        }
        result++;
    }
    return result;
}

int check_end(string word) {
    int result = 0;
    reverse(word.begin(), word.end());
    for (int i = 0; i < word.size(); i++) {
        if (!is_gl(word[i])) {
            break;
        }
        result++;
    }
    return result;
}

void solve(int text_number) {
    string filein = to_string(text_number / 2 + 1) + "_" + (text_number & 1 ? "s" : "l") + ".txt";
    string fileout = to_string(text_number / 2 + 1) + "_" + (text_number & 1 ? "s" : "l") + ".txt";

    cout << "Parsing: " << filein << endl;
    ifstream fin("../TextFiles/" + filein);
    ofstream fout(fileout);

    vector<string> words;
    string word;
    while (fin >> word) {
        string parsed_word = parse(word);
        if (is_word(parsed_word)) {
            words.push_back(parsed_word);
        }
    }
    for (string i : words) {
        fout << i << endl;
    }
    fout << "----------------------------------------------------------" << endl;
    int pairs_count = 0;
    for (int i = 0; i < words.size(); i++) {

        for (int j = i + 1; j < words.size(); j++) {
            int ending = check_end(words[i]), begining = check_begin(words[j]);
            if (ending >= 2 && begining >= 2) {
                fout << "WTF: " << words[i] << ' ' << words[j] << ": " << ending << ' ' << begining << endl;
                pairs_count++;
            }
        }
    }

    fout.close();

    if (words.size() <= 1) {
        cout << "There is no words!!";
        return;
    }
    cout << "Result: " << fixed << setprecision(6) << 1.0 * pairs_count / (words.size() - 1) << endl;

}

int main() {
    setlocale(LC_ALL, "Russian");

    for (int i = 0; i < 8; i++) {
        solve(i);
    }

    return 0;
}
