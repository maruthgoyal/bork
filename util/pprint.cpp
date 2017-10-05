/*
Copyright (c) 2017 Maruth Goyal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <string>
#include <iostream>
#include "../parser/parser.hpp"
#include "pprint.hpp"


std::string pprint_(parser::thing *t, int i) {

	std::string s;

	for (int j = 0; j < i; j++) {
		s.push_back('\t');
	}

	if (t->t == parser::type::TOKEN) {
		s += ((static_cast<parser::token *>(t))->get_content());
	}

	else if (t->t == parser::type::EXPRESSION) {
		
		s.push_back('(');
		s.push_back('\n');

		parser::expression *e = static_cast<parser::expression *>(t);

		for (int j = 0; j < e->things.size(); j++) {
			s += pprint_(e->things[j], i+1);
			s.push_back('\n');
		}

		for (int j = 0; j < i; j++) {
			s.push_back('\t');
		}

		s.push_back(')');
		s.push_back('\n');

	}

	return s;

}

std::string util::pprint(std::string s) {
	return pprint_(parser::parse(s), 0);
}