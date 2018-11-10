#pragma once

#include <string>
#include <map>
#include <algorithm>

class soundex
{
public:
	static std::string get_soundex_index_of(const std::string&);
private:
	static char get_code(char letter);
};

inline std::string soundex::get_soundex_index_of(const std::string& termin)
{
	std::string::size_type lenght = termin.size();
	if (0 == lenght) {
		return "";
	}
	std::string soundex_index;
	soundex_index.reserve(4);
	soundex_index.push_back(termin[0]);
	char prev = 0;
	for (unsigned i = 1; soundex_index.size() < 4 && i != lenght; ++i) {
		if (!isalpha(termin[i])) {
			continue;
		}
		char code = get_code(termin[i]);
		if (0 != code && code != prev) {
			soundex_index.push_back(code);
		}
		prev = code;
	}
	while (soundex_index.size() < 4) {
		soundex_index.push_back('0');
	}
	return soundex_index;
}

char soundex::get_code(char letter)
{
	static const int size = 26;
	static char codes[size] = {0};
	if (0 == codes[0]) {
		codes['a' - 'a'] = '0';
		codes['b' - 'a'] = '1';
		codes['c' - 'a'] = '2';
		codes['d' - 'a'] = '3';
		codes['e' - 'a'] = '0';
		codes['f' - 'a'] = '1';
		codes['g' - 'a'] = '2';
		codes['h' - 'a'] = '0';
		codes['i' - 'a'] = '0';
		codes['j' - 'a'] = '2';
		codes['k' - 'a'] = '2';
		codes['l' - 'a'] = '4';
		codes['m' - 'a'] = '5';
		codes['n' - 'a'] = '5';
		codes['o' - 'a'] = '0';
		codes['p' - 'a'] = '1';
		codes['q' - 'a'] = '2';
		codes['r' - 'a'] = '6';
		codes['s' - 'a'] = '2';
		codes['t' - 'a'] = '3';
		codes['u' - 'a'] = '0';
		codes['v' - 'a'] = '1';
		codes['w' - 'a'] = '0';
		codes['x' - 'a'] = '2';
		codes['y' - 'a'] = '0';
		codes['z' - 'a'] = '2';
	}
	int index = (letter | 0x20) - 'a';
	return (index >= 0 && index < size)
		? ('0' != codes[index] ? codes[index] : 0)
		: letter;
}