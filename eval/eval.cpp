// "Copyright 2017 Maruth Goyal"

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

#include "../parser/parser.hpp"
#include "../scheme.hpp"
#include "eval.hpp"

bool is_digits(const std::string &str) {
    return str.find_first_not_of(".0123456789") == std::string::npos;
}

void sub_arg(parser::expression* e, parser::token to_replace, eval::value val) {

	for(int i = 0; i < e->things.size(); i++) {

		if (e->things[i]->t == parser::type::TOKEN) {

			parser::token *t = static_cast<parser::token *>(e->things[i]);

			if ( t->get_content().compare(to_replace.get_content()) == 0)
				*(e->things[i]) = val;
		
		}

		else if (e->things[i]->t == parser::type::EXPRESSION) {
			parser::expression *e_prime = static_cast<parser::expression *>(e->things[i]);
			sub_arg(e_prime, to_replace, val);
		}
	
	}

}

eval::value* eval::get_var(std::string s, context& c) {
	if (c.count(s) == 0)
		return NULL;

	return c[s];
}

// eval::value eval::func_eval(eval::func *func, std::vector<eval::value> args, context& c) {

// 	if (func->is_std())
// 		return func->f(args, c);

// 	parser::expression e = func->get_body();
// 	for(int i = 0; i < func->arg_list.size(); i++) {

// 		sub_arg(&e, func->arg_list[i], args[i]);

// 	}

// 	return eval::eval(&e, c);

// }

eval::value eval::func_eval(eval::func *func, std::vector<parser::thing *> args, context& c) {

	if (func->is_std())
		return func->f(args, c);


	std::vector<eval::value> e_args;
	for(int i = 0; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	parser::expression e = func->get_body();
	for(int i = 0; i < func->arg_list.size(); i++) {

		sub_arg(&e, func->arg_list[i], e_args[i]);

	}

	return eval::eval(&e, c);	

}


eval::value eval::eval(parser::thing *thing, context& c) {

	if (thing->t == parser::type::TOKEN) {

		parser::token *t = static_cast<parser::token*>(thing);
		std::string content = t->get_content();

		if(content.compare("true") == 0)
			return eval::boolean(true);

		if(content.compare("false") == 0)
			return eval::boolean(false);

		if (is_digits(content)) {
			std::cout << "CONTENT: " <<  content << std::endl;
			return eval::number(std::stod(content));
		}

		
		eval::value *v = eval::get_var(content, c);
		if(v != NULL) {
			return *v;
		}

		else if (content[0] == '"') {
			return eval::string(content.substr(1, content.length()-2));
		}

	}


	else if (thing->t == parser::type::EXPRESSION) {

		parser::expression *e = static_cast<parser::expression *>(thing);

		eval::value v = eval::eval(e->things[0], c);

		if (v.get_type() != eval::type::FUNC) {
			scheme::exit("FIRST TOKEN IN EXPRESSION MUST BE A FUNCTION.");
		}

		eval::func *f =  static_cast<eval::func *>(&v);

		if (f->get_n_args() != e->things.size()) {
			scheme::exit("INCORRECT NUMBER OF ARGUMENTS.");
		}

		// if (f->to_eval_args()) {

		// 	std::vector<eval::value> args;

		// 	for(int i = 0; i < f->get_n_args(); i++) {
		// 		args.push_back(eval::eval(&(e->things[i]), c));
		// 	}

		// 	return eval::func_eval(f, args, c);

		// }

		return eval::func_eval(f, e->things, c);

	}

	else if (thing->t == parser::type::EVALED) {
		eval::value *v = static_cast<eval::value*>(thing);
		return *v;
	}

}