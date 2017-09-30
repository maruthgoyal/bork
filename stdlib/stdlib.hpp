// Copyright 2017 Maruth Goyal
#ifndef STDLIB_STDLIB_HPP_
#define STDLIB_STDLIB_HPP_

#include "../eval/eval.hpp"
namespace stdlib {
	eval::value add(std::vector<parser::thing *> args, context& c);
}





#endif  // STDLIB_STDLIB_HPP_
