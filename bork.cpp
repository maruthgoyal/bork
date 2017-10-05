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
#include <vector>
#include <fstream>

#include "parser.hpp"
#include "eval.hpp"
#include "stdlib.hpp"
#include "pprint.hpp"

/*
	* REPL: Read-Eval-Print-Loop
	* Reads a line from the console and evaluates it.
*/
void repl() {

    std::string s;
    context c;
    stdlib::init_stdlib(c);

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

    char c;

    f.get(c);
    while (c != '(' && f.good()) f.get(c);

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
void from_file(const std::string &filename) {

    std::ifstream f(filename);
    std::string buf;

    context c;
    stdlib::init_stdlib(c);

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

void pretty_print(const std::string &filename) {

    std::ifstream f(filename);
    std::ofstream of(filename + "___");
    std::string buf;

    while (f.good()) {
        read_exp(f, buf);
        std::string s = util::pprint(buf);
        for (auto d : s) {
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
    } else if (argc == 3) {

        pretty_print(argv[1]);

    } else {
        std::cerr << "SPECIFY 1 FILENAME TO INTERPRET. OR SPECIFY NONE TO START REPL.";
        return 1;
    }

    return 0;

}