// Copyright 2017 Maruth Goyal

#include <vector>
#include <iostream>

#include "../eval/eval.hpp"
#include "stdlib.hpp"

void stdlib::exit(std::string msg) {
	std::cout << msg << std::endl;
	std::exit(1);
}

eval::value *stdlib::add(std::vector<parser::thing *> args, context& c) {

	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() == eval::type::NUMBER) {

		double total = 0;

		for (int i = 0; i < e_args.size(); i++) {

			if (e_args[i]->get_type() != eval::type::NUMBER)
				stdlib::exit("ALL ARGUMENTS TO ADD MUST BE EITHER NUMBERS OR STRINGS");

			eval::number* n = static_cast<eval::number *>(e_args[i]);
			total += n->get_val();

		}

		return new eval::number(total);
	}

	else if (e_args[0]->get_type() == eval::type::STRING) {

		std::string total;

		for(int i = 0; i < e_args.size(); i++) {

			if (e_args[i]->get_type() != eval::type::STRING)
				stdlib::exit("ALL ARGUMENTS TO ADD MUST BE EITHER NUMBERS OR STRINGS");

			eval::string *s = static_cast<eval::string *>(e_args[i]);
			total += s->get_val();
		}

		return new eval::string(total);

	}

	stdlib::exit("ADD ONLY WORKS WITH NUMBERS AND STRINGS.");

}


eval::value *stdlib::subtract(std::vector<parser::thing *> args, context& c) {

	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() == eval::type::NUMBER) {

		double total = (static_cast<eval::number *>(e_args[0]))->get_val();

		for (int i = 1; i < e_args.size(); i++) {

			if (e_args[i]->get_type() != eval::type::NUMBER)
				stdlib::exit("ALL ARGUMENTS TO subtract MUST BE NUMBERS");

			eval::number* n = static_cast<eval::number *>(e_args[i]);
			total -= n->get_val();

		}

		return new eval::number(total);
	}

	stdlib::exit("SUBTRACT ONLY WORKS WITH NUMBERS.");

}

eval::value *stdlib::multiply(std::vector<parser::thing *> args, context& c) {

	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() == eval::type::NUMBER) {

		double total = 1;

		for (int i = 0; i < e_args.size(); i++) {

			if (e_args[i]->get_type() != eval::type::NUMBER)
				stdlib::exit("ALL ARGUMENTS TO multiply MUST BE NUMBERS");

			eval::number* n = static_cast<eval::number *>(e_args[i]);
			total *= n->get_val();

		}

		return new eval::number(total);
	}

	stdlib::exit("MULTIPLY ONLY WORKS WITH NUMBERS.");

}

eval::value *stdlib::divide(std::vector<parser::thing *> args, context& c) {

	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() == eval::type::NUMBER) {

		double total = (static_cast<eval::number *>(e_args[0]))->get_val();

		for (int i = 1; i < e_args.size(); i++) {

			if (e_args[i]->get_type() != eval::type::NUMBER)
				stdlib::exit("ALL ARGUMENTS TO divide MUST BE NUMBERS");

			eval::number* n = static_cast<eval::number *>(e_args[i]);
			total /= n->get_val();

		}

		return new eval::number(total);
	}

	stdlib::exit("DIVIDE ONLY WORKS WITH NUMBERS.");

}

eval::value *stdlib::define(std::vector<parser::thing *> args, context &c) {

	if (args[1]->t == parser::type::TOKEN) { // variable
		parser::token *t = static_cast<parser::token *>(args[1]);
		c[t->get_content()] = eval::eval(args[2], c);
	}

	else if (args[1]->t == parser::type::EXPRESSION) { // func

		parser::expression *e = static_cast<parser::expression *>(args[1]);

		std::vector<parser::token *> *arg_list = new std::vector<parser::token *>();

		for(int i = 1; i < e->things.size(); i++) {
			if (e->things[i]->t != parser::type::TOKEN)
				stdlib::exit("ARGS MUST BE TOKENS.");
			arg_list->push_back(static_cast<parser::token *>(e->things[i]));
		}

		if (e->things[0]->t != parser::type::TOKEN)
			stdlib::exit("NAME MUST BE A TOKEN");

		parser::token *t = static_cast<parser::token *>(e->things[0]);
		parser::expression *exp = static_cast<parser::expression *>(args[2]);
		c[t->get_content()] = new eval::func(exp, arg_list, true, false); 

	}

	return NULL;
}

eval::value *stdlib::ifelse(std::vector<parser::thing *> args, context &c) {

	eval::value *e = eval::eval(args[1], c);

	if (e->get_type() != eval::type::BOO)
		stdlib::exit("FIRST ARGUMENT TO IF MUST BE A BOOLEAN EXPRESSION.");

	eval::boolean *b = static_cast<eval::boolean *>(e);

	if (b->get_val())
		return eval::eval(args[2], c);

	return eval::eval(args[3], c);

}