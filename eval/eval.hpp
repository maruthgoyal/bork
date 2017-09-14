// "Copyright 2017 Maruth Goyal"
#ifndef _USERS_MARUTHGOYAL_SP_EVAL_EVAL_HPP_
#define _USERS_MARUTHGOYAL_SP_EVAL_EVAL_HPP_

#include <string>
#include <unordered_map>
#include "../parser/parser.hpp"


namespace eval {
	enum class type;
	class value;
	class func;
	class number;
	class string;
	class boolean;
	eval::value eval(parser::thing*, std::unordered_map<std::string, eval::value*>&);
	eval::value* get_var(std::string, std::unordered_map<std::string, eval::value*>&);
}

typedef std::unordered_map<std::string, eval::value*> context;
enum class eval::type {NUMBER, STRING, BOO, FUNC};

class eval::value {
	
	eval::type t;

public:

	eval::type get_type() {
		return t;
	}

	void set_type(eval::type ty) {
		t = ty;
	}

};

class eval::func: public eval::value {

	parser::expression body;
	int n_args;
	bool eval_args;

public:

	explicit func(parser::expression func_body, int num_args, bool to_eval_args) {
		body = func_body;
		n_args = num_args;
		eval_args = to_eval_args;
		set_type(eval::type::FUNC);
	}

	parser::expression get_body() {
		return body;
	}

	int get_n_args() {
		return n_args;
	}

	bool to_eval_args() {
		return eval_args;
	}

};

class eval::number: public eval::value {

	double val;

public:

	explicit number(double d) {
		val = d;
		set_type(eval::type::NUMBER);
	}

	double get_val() {
		return val;
	}

};

class eval::string: public eval::value {

	std::string val;

public: 
	
	explicit string(std::string s){
		val = s;
		set_type(eval::type::STRING);
	}

	std::string get_val() {
		return val;
	}

};

class eval::boolean: public eval::value {
	bool val;

public:

	explicit boolean(bool b) {
		val = b;
		set_type(eval::type::BOO);
	}

	bool get_val() {
		return val;
	}
};

#endif  // _USERS_MARUTHGOYAL_SP_EVAL_EVAL_HPP_
