#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "parser/parser.hpp"
#include "eval/eval.hpp"
#include "stdlib/stdlib.hpp"
#include "scheme.hpp"


void scheme::exit(std::string msg) {
	std::cout << msg << std::endl;
	std::exit(1);
}

void init_stdlib(context &t) {

	eval::func *add = new eval::func(stdlib::add, std::vector<parser::token>(), false, true);
	t[std::string("+")] = add;

}

int main() {

	std::string s;
	std::getline(std::cin, s);

	context c;
	init_stdlib(c);

	eval::eval(parser::parse(s), c);

	return 0;
}