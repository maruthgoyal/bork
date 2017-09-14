// "Copyright 2017 Maruth Goyal"

#include <unordered_map>
#include <string>
#include <vector>

#include "../parser/parser.hpp"
#include "../scheme.hpp"
#include "eval.hpp"

bool is_digits(const std::string &str) {
    return str.find_first_not_of(".0123456789") == std::string::npos;
}

eval::value* eval::get_var(std::string s, context& c) {
	if (c.count(s) == 0)
		return NULL;

	return c[s];
}


eval::value eval::eval(parser::thing* thing, context& c) {

	if (thing->t == parser::type::TOKEN) {

		parser::token *t = static_cast<parser::token*>(thing);
		std::string content = t->get_content();

		if(content.compare("true") == 0)
			return eval::boolean(true);

		if(content.compare("false") == 0)
			return eval::boolean(false);

		if (is_digits(content))
			return eval::number(std::stod(content));

		
		eval::value *v = eval::get_var(content, c);
		if(v != NULL) {
			return *v;
		}

		else if (content[0] == '"') {
			return eval::string(content.substr(1, content.length()-2));
		}

	}


	else if (thing->t == parser::type::EXPRESSION) {
		parser::expression *e = static_cast<parser::expression*>(thing);

		eval::value v = eval::eval(&(e->things[0]),c);

		if (v.get_type() != eval::type::FUNC) {
			scheme::exit("FIRST TOKEN IN EXPRESSION MUST BE A FUNCTION.");
		}

		eval::func *f =  static_cast<eval::func*>(&v);

		if (f->get_n_args() != e->things.size()) {
			scheme::exit("INCORRECT NUMBER OF ARGUMENTS.");
		}

		if(f->to_eval_args()) {

			std::vector<eval::value> args;

			for(int i = 0; i < f->get_n_args(); i++) {
				args.push_back(eval::eval(&(e->things[i]), c));
			}

			return eval::func_eval(f, args, c);

		}

		return eval::func_eval(f, e->things, c);
	}

}