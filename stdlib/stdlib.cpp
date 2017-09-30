// Copyright 2017 Maruth Goyal

#include <vector>

#include "../eval/eval.hpp"
#include "../scheme.hpp"
#include "stdlib.hpp"

eval::value stdlib::add(std::vector<parser::thing *> args, context& c) {

	std::vector<eval::value> e_args;
	for(int i = 0; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0].get_type() == eval::type::NUMBER) {

		double total = 0;

		for (int i = 0; i < e_args.size(); i++) {

			if (e_args[i].get_type() != eval::type::NUMBER)
				scheme::exit("ALL ARGUMENTS TO ADD MUST BE EITHER NUMBERS OR STRINGS");

			eval::number* n = static_cast<eval::number*>(&(e_args[i]));
			total += n->get_val();
		}

		return eval::number(total);
	}

	else if (e_args[0].get_type() == eval::type::STRING) {

		std::string total;

		for(int i = 0; i < e_args.size(); i++) {

			if (e_args[i].get_type() != eval::type::STRING)
				scheme::exit("ALL ARGUMENTS TO ADD MUST BE EITHER NUMBERS OR STRINGS");

			eval::string *s = static_cast<eval::string*>(&(e_args[i]));
			total += s->get_val();
		}

		return eval::string(total);

	}

	scheme::exit("ADD ONLY WORKS WITH NUMBERS AND STRINGS.");

}


eval::value subtract(std::vector<parser::thing> args, context& c) {

	std::vector<eval::value> e_args;
	for(int i = 0; i < args.size(); i++) {
		e_args.push_back(eval::eval(&(args[i]), c));
	}

	if (e_args[0].get_type() == eval::type::NUMBER) {

		eval::number* t = static_cast<eval::number*>(&(e_args[0]));
		double total = t->get_val();

		for (int i = 1; i < e_args.size(); i++) {

			if (e_args[i].get_type() != eval::type::NUMBER)
				scheme::exit("ALL ARGUMENTS TO ADD MUST BE EITHER NUMBERS OR STRINGS");

			eval::number* n = static_cast<eval::number*>(&(e_args[i]));
			total -= n->get_val();
		}

		return eval::number(total);
	}

	scheme::exit("SUBTRACT ONLY WORKS WITH NUMBERS.");
}

