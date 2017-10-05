// Copyright 2017 Maruth Goyal

#include <vector>
#include <iostream>
#include <cmath>

#include "../eval/eval.hpp"
#include "stdlib.hpp"

void stdlib::exit(std::string msg) {
	std::cout << msg << std::endl;
	std::exit(1);
}

/********************************************
	* ARITHMETIC FUNCTIONS BEGIN
********************************************/

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

eval::value *stdlib::modulus(std::vector<parser::thing *> args, context& c) {

	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() == eval::type::NUMBER) {

		double total = (static_cast<eval::number *>(e_args[0]))->get_val();

		for (int i = 1; i < e_args.size(); i++) {

			if (e_args[i]->get_type() != eval::type::NUMBER)
				stdlib::exit("ALL ARGUMENTS TO mod MUST BE NUMBERS");

			eval::number* n = static_cast<eval::number *>(e_args[i]);
			total = fmod(total, n->get_val());

		}

		return new eval::number(total);
	}

	stdlib::exit("MODULUS ONLY WORKS WITH NUMBERS.");

}

/********************************************
	* ARITHMETIC FUNCTIONS END
********************************************/




/********************************************
	* COMPARISON FUNCTIONS BEGIN
********************************************/

eval::value *stdlib::eq(std::vector<parser::thing *> args, context &c) {

	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() != e_args[1]->get_type())
		stdlib::exit("Cannot compare vars of 2 diff types");

	if (e_args[0]->get_type() == eval::type::NUMBER) {
		
		eval::number *n1 = static_cast<eval::number *>(e_args[0]);
		eval::number *n2 = static_cast<eval::number *>(e_args[1]);

		return new eval::boolean(n1->get_val() == n2->get_val());

	}

	else if (e_args[0]->get_type() == eval::type::BOO) {

		eval::boolean *b1 = static_cast<eval::boolean *>(e_args[0]);
		eval::boolean *b2 = static_cast<eval::boolean *>(e_args[1]);

		return new eval::boolean(b1->get_val() == b2->get_val());

	}

	else if (e_args[0]->get_type() == eval::type::STRING) {

		eval::string *s1 = static_cast<eval::string *>(e_args[0]);
		eval::string *s2 = static_cast<eval::string *>(e_args[1]);

		return new eval::boolean(s1->get_val() == s2->get_val());

	}

	stdlib::exit("CANNOT COMPARE EQUALITY OF NON INTEGER/STRING/BOOL");

}

eval::value *stdlib::neq(std::vector<parser::thing *> args, context &c) {
	eval::boolean *b = static_cast<eval::boolean *>(eq(args, c));
	b->negate();
	return b;
}

eval::value *stdlib::lt(std::vector<parser::thing *> args, context &c) {


	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() != e_args[1]->get_type())
		stdlib::exit("Cannot compare vars of 2 diff types");

	if (e_args[0]->get_type() == eval::type::NUMBER) {
		
		eval::number *n1 = static_cast<eval::number *>(e_args[0]);
		eval::number *n2 = static_cast<eval::number *>(e_args[1]);

		return new eval::boolean(n1->get_val() < n2->get_val());

	}

	stdlib::exit("CANNOT COMPARE EQUALITY OF NON NUMBER");

}

eval::value *stdlib::gt(std::vector<parser::thing *> args, context &c) {
	eval::boolean *b = static_cast<eval::boolean *>(lt(args, c));
	b->negate();
	return b;
}

eval::value *stdlib::lte(std::vector<parser::thing *> args, context &c) {


	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() != e_args[1]->get_type())
		stdlib::exit("Cannot compare vars of 2 diff types");

	if (e_args[0]->get_type() == eval::type::NUMBER) {
		
		eval::number *n1 = static_cast<eval::number *>(e_args[0]);
		eval::number *n2 = static_cast<eval::number *>(e_args[1]);

		return new eval::boolean(n1->get_val() <= n2->get_val());

	}

	stdlib::exit("CANNOT COMPARE EQUALITY OF NON NUMBER");

}

eval::value *stdlib::gte(std::vector<parser::thing *> args, context &c) {


	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() != e_args[1]->get_type())
		stdlib::exit("Cannot compare vars of 2 diff types");

	if (e_args[0]->get_type() == eval::type::NUMBER) {
		
		eval::number *n1 = static_cast<eval::number *>(e_args[0]);
		eval::number *n2 = static_cast<eval::number *>(e_args[1]);

		return new eval::boolean(n1->get_val() >= n2->get_val());

	}

	stdlib::exit("CANNOT COMPARE EQUALITY OF NON NUMBER");

}


/********************************************
	* COMPARISON FUNCTIONS END
********************************************/



/********************************************
	* BINARY FUNCTIONS BEGIN
********************************************/

eval::value *stdlib::and_(std::vector<parser::thing *> args, context &c) {

	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() == eval::type::BOO) {

		bool final = (static_cast<eval::boolean *>(e_args[0]))->get_val();

		for (int i = 1; i < e_args.size(); i++) {

			if (e_args[i]->get_type() != eval::type::BOO)
				stdlib::exit("ALL ARGUMENTS TO and MUST BE booleans");

			eval::boolean* n = static_cast<eval::boolean *>(e_args[i]);
			final = n->get_val() && final;

		}

		return new eval::boolean(final);

	}

	stdlib::exit("AND ONLY WORKS WITH BOOLEANS.");

}
eval::value *stdlib::or_(std::vector<parser::thing *> args, context &c) {

	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	if (e_args[0]->get_type() == eval::type::BOO) {

		bool final = (static_cast<eval::boolean *>(e_args[0]))->get_val();

		for (int i = 1; i < e_args.size(); i++) {

			if (e_args[i]->get_type() != eval::type::BOO)
				stdlib::exit("ALL ARGUMENTS TO and MUST BE booleans");

			eval::boolean* n = static_cast<eval::boolean *>(e_args[i]);
			final = n->get_val() || final;

		}

		return new eval::boolean(final);

	}

	stdlib::exit("OR ONLY WORKS WITH BOOLEANS.");

}

eval::value *stdlib::not_(std::vector<parser::thing *> args, context &c) {
	
	eval::value *v = eval::eval(args[1], c);

	if (v->get_type() == eval::type::BOO) {
		eval::boolean *b = static_cast<eval::boolean *>(v);
		b->negate();
		return b;
	}

	stdlib::exit("NOT ONLY WORKS WITH BOOLEANS");
}

/********************************************
	* BINARY FUNCTIONS END
********************************************/

eval::value *stdlib::display(std::vector<parser::thing *> args, context &c) {
	
	std::vector<eval::value *> e_args;
	for(int i = 1; i < args.size(); i++) {
		e_args.push_back(eval::eval(args[i], c));
	}

	for(int i = 0; i < e_args.size(); i++) {
		std::cout << (e_args[i])->to_string() << std::endl;
	}

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
