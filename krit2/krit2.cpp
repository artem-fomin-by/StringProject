#include <iostream>
#include <map>
#include <windows.h>

using namespace std;

const string russian = "àáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß";
const string sent_separator = ".!?";
bool isLetter(char c) {
	return russian.find(c) != string::npos;
}
bool isSeparator(char c) {
	return sent_separator.find(c) != string::npos;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	string text;
	string s;
	while (getline(cin, s)) {
		text += " " + s;
	}
	
	map <int, int> word, sent;
	
	string t1 = text;
	while (t1.size()) {
		if (!isLetter(t1[0])) {
			t1.erase(0, 1);
			continue;
		}
		
		int sz = 0;
		while (t1.size() && isLetter(t1[0])) {
			sz++;
			t1.erase(0, 1);
		}
		
		word[sz]++;
	}
	
	int averWord = 0, divWord = 0;
	for (auto &[x, y]: word) {
		averWord += x * y;
		divWord += y;
	}
	averWord /= divWord;
	cout << "Average Word Size: " << averWord << endl;
	
	string t2 = text;
	while (t2.size()) {
		if (isSeparator(t2[0])) {
			t2.erase(0, 1);
			continue;
		}
		
		int sz = 0;
		while (t2.size() && !isSeparator(t2[0])) {
			if (isLetter(t2[0])) sz++;
			t2.erase(0, 1);
		}
		
		sent[sz]++;
	}
	
	int averSent = 0, divSent = 0;
	for (auto &[x, y]: sent) {
		averSent += x * y;
		divSent += y;
	}
	averSent /= divSent;
	cout << "Average Sentence Size: " << averSent << endl;
	
	return 0;
}
