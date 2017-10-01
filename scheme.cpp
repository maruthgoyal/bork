#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "parser/parser.hpp"
#include "eval/eval.hpp"
#include "stdlib/stdlib.hpp"
#include "scheme.hpp"


void init_stdlib(context &t) {

	eval::func *add = new eval::func(stdlib::add, std::vector<parser::token>(), false, true, true);
	eval::func *sub = new eval::func(stdlib::subtract, std::vector<parser::token>(), false, true, true);
	eval::func *mul = new eval::func(stdlib::multiply, std::vector<parser::token>(), false, true, true);
	eval::func *div = new eval::func(stdlib::divide, std::vector<parser::token>(), false, true, true);

	t[std::string("+")] = add;
	t[std::string("-")] = sub;
	t[std::string("*")] = mul;
	t[std::string("/")] = div;

}

int main() {

	std::string s;
	std::getline(std::cin, s);

	context c;
	init_stdlib(c);

	eval::number *n = static_cast<eval::number *>(eval::eval(parser::parse(s), c));
	std::cout << n->get_val() << std::endl;

	return 0;
}