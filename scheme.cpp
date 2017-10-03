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

int main() {

	std::string s;
	context c;
	init_stdlib(c);

	while (true) {

		std::getline(std::cin, s);
		eval::eval(parser::parse(s), c);
		
	}

	return 0;
	
}