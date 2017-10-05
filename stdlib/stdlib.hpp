// Copyright 2017 Maruth Goyal
#ifndef STDLIB_STDLIB_HPP_
#define STDLIB_STDLIB_HPP_

#include "../eval/eval.hpp"
#include <iostream>

namespace stdlib {

	eval::value *add(std::vector<parser::thing *> args, context &c);
	eval::value *subtract(std::vector<parser::thing *> args, context &c);
	eval::value *multiply(std::vector<parser::thing *> args, context &c);
	eval::value *divide(std::vector<parser::thing *> args, context &c);
	eval::value *modulus(std::vector<parser::thing *> args, context &c);
	
	eval::value *define(std::vector<parser::thing *> args, context &c);
	eval::value *ifelse(std::vector<parser::thing *> args, context &c);

	eval::value *eq(std::vector<parser::thing *> args, context &c);
	eval::value *neq(std::vector<parser::thing *> args, context &c);
	eval::value *lt(std::vector<parser::thing *> args, context &c);
	eval::value *gt(std::vector<parser::thing *> args, context &c);
	eval::value *lte(std::vector<parser::thing *> args, context &c);
	eval::value *gte(std::vector<parser::thing *> args, context &c);

	eval::value *and_(std::vector<parser::thing *> args, context &c);
	eval::value *or_(std::vector<parser::thing *> args, context &c);
	eval::value *not_(std::vector<parser::thing *> args, context &c);

	eval::value *display(std::vector<parser::thing *> args, context &c);


	void exit(std::string msg);

}





#endif  // STDLIB_STDLIB_HPP_
