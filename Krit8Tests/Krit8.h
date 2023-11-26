#pragma once

#include <string>

extern bool is_gl(char c);

extern bool is_sogl(char c);

extern bool is_word(std::string word);

extern std::string parse(std::string word);

extern int check_begin(std::string word);

extern int check_end(std::string word);

extern void solve(int text_number);

extern std::string Letters();

extern std::string Sogl();
