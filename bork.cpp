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


#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

#include "parser/parser.hpp"
#include "eval/eval.hpp"
#include "stdlib/stdlib.hpp"
#include "util/pprint.hpp"
#include "bork.hpp"

/* Initializes Environment
	* context --> std::unordered_map<std::string, eval::value *>
	* Adds all the standard functions to the env
*/
void bork::init_stdlib(context &t) {

	eval::func *add = new eval::func(stdlib::add, NULL, false, true, true);
	eval::func *sub = new eval::func(stdlib::subtract, NULL, false, true, true);
	eval::func *mul = new eval::func(stdlib::multiply, NULL, false, true, true);
	eval::func *div = new eval::func(stdlib::divide, NULL, false, true, true);
	eval::func *mod = new eval::func(stdlib::modulus, NULL, false, true, true);

	eval::func *def = new eval::func(stdlib::define, 
									 new std::vector<parser::token *>({NULL, NULL}),
									 false, true, false
									);

	eval::func *ifelse = new eval::func(stdlib::ifelse,
										new std::vector<parser::token *>({NULL, NULL, NULL}),
										false, true, false
										);

	

	eval::func *eq = new eval::func(stdlib::eq,
									new std::vector<parser::token *>({NULL, NULL}),
									false, true, false
									);

	eval::func *neq = new eval::func(stdlib::neq,
								new std::vector<parser::token *>({NULL, NULL}),
								false, true, false
								);

	eval::func *lt = new eval::func(stdlib::lt,
								new std::vector<parser::token *>({NULL, NULL}),
								false, true, false
								);

	eval::func *gt = new eval::func(stdlib::gt,
								new std::vector<parser::token *>({NULL, NULL}),
								false, true, false
								);

	eval::func *lte = new eval::func(stdlib::lte,
								new std::vector<parser::token *>({NULL, NULL}),
								false, true, false
								);

	eval::func *gte = new eval::func(stdlib::gte,
								new std::vector<parser::token *>({NULL, NULL}),
								false, true, false
								);


	eval::func *and_ = new eval::func(stdlib::and_, NULL, false, true, true);
	eval::func *or_ = new eval::func(stdlib::or_, NULL, false, true, true);
	eval::func *not_ = new eval::func(stdlib::not_, new std::vector<parser::token *>{NULL}, false, true, false);

	eval::func *display = new eval::func(stdlib::display, NULL, false, true, true);


	t[std::string("+")] = add;
	t[std::string("-")] = sub;
	t[std::string("*")] = mul;
	t[std::string("/")] = div;
	t[std::string("mod")] = mod;

	t[std::string("define")] = def;
	t[std::string("if")    ] = ifelse;

	t[std::string("=") ] = eq;
	t[std::string("!=")] = neq;
	t[std::string("<") ] = lt;
	t[std::string(">") ] = gt;
	t[std::string("<=")] = lte;
	t[std::string(">=")] = gte;

	t[std::string("and")] = and_;
	t[std::string("or") ] = or_;
	t[std::string("not")] = not_;

	t[std::string("display")] = display;

}


/*
	* REPL: Read-Eval-Print-Loop
	* Reads a line from the console and evaluates it.
*/
void repl() {

	std::string s;
	context c;
	bork::init_stdlib(c);

	while (true) {

		std::cout << ">>> ";

		std::getline(std::cin, s);
		eval::eval(parser::parse(s), c);
		
	}

}

/*
	* Reads one expression from a file
	* ARGS:
		* std::ifstream &f --> Reference to Input file
		* std::String buf --> Reference to String to store the expression in
*/
void read_exp(std::ifstream &f, std::string &buf) {

	bool started_exp = false;
	char c;

	f.get(c);
	while( c != '(' && f.good()) f.get(c);

	buf.push_back(c);
	int stack = 1;

	while (f.good() && stack) {

		f.get(c);
		buf += c;

		if (c == ')') stack--;
		if (c == '(') stack++;

	}

}


/* 
	* Read Program from file and eval
	* ARGS:
		* std::string filename --> Name of the file to read.
*/
void from_file(std::string filename) {

	std::ifstream f(filename);
	std::string buf;

	context c;
	bork::init_stdlib(c);

	while (f.good()) {
		
		read_exp(f, buf);
		eval::eval(parser::parse(buf), c);
		buf.clear();

	}

	f.close();

}

/*
	* Read program and pretty-print it to a new file
	* ARGS:
		* std::string filename --> Name of the file to read.

	* Reads the file and pprints expression-by-expression.
*/

void pretty_print(std::string filename) {

	std::ifstream f(filename);
	std::ofstream of(filename + "___");
	std::string buf;

	while (f.good()) {
		read_exp(f, buf);
		std::string s = util::pprint(buf);
		for(auto d : s) {
			of.put(d);
		}
	}

	f.close();
	of.close();

}

int main(int argc, char *argv[]) {

	if (argc == 1)
		repl();

	else if (argc == 2) {
		from_file(std::string(argv[1]));
	}

	else if (argc == 3) {

		pretty_print(argv[1]);

	}

	else {
		std::cerr << "SPECIFY 1 FILENAME TO INTERPRET. OR SPECIFY NONE TO START REPL.";
		return 1;
	}
	
	return 0;
	
}