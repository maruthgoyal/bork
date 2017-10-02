#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "parser/parser.hpp"
#include "eval/eval.hpp"
#include "stdlib/stdlib.hpp"
#include "scheme.hpp"


void init_stdlib(context &t) {

	eval::func *add = new eval::func(stdlib::add, NULL, false, true, true);
	eval::func *sub = new eval::func(stdlib::subtract, NULL, false, true, true);
	eval::func *mul = new eval::func(stdlib::multiply, NULL, false, true, true);
	eval::func *div = new eval::func(stdlib::divide, NULL, false, true, true);
	
	eval::func *def = new eval::func(stdlib::define, 
									 new std::vector<parser::token *>({NULL, NULL}),
									 false, true, false
									);



	t[std::string("+")] = add;
	t[std::string("-")] = sub;
	t[std::string("*")] = mul;
	t[std::string("/")] = div;
	t[std::string("define")] = def;

}

int main() {

	std::string s;
	std::getline(std::cin, s);

	context c;
	init_stdlib(c);

	(eval::eval(parser::parse(s), c));

	return 0;
}