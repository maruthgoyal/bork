/*
Copyright (c) 2017 Maruth Goyal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

#include "parser.hpp"
#include "stdlib.hpp"

/*
	* Returns whether a string is entirely composed of digits or not.
	* ARGS:
		* const std::string &str --> Reference to the string to check.
	* RETURNS:
		* bool                   --> True if all digits, false otherwise
*/
bool is_digits(const std::string &str) {
    return str.find_first_not_of(".0123456789") == std::string::npos;
}

/*
	* Gets a value from the environment, given a variable name.
	* ARGS:
		* std::string s --> Name of the Variable
		* context &c    --> Reference to the environment
	* RETURNS:
		* eval::value * --> Pointer to the value of the variable (NUMBER, STRING, FUNC, BOO)
		* NULL if no var of that name in the env
*/
eval::value *eval::get_var(std::string s, context &c) {
    if (c.count(s) == 0)
        return NULL;

    return c[s];
}

/*

	* Evaluates a function with given arguments
	* If the function is a part of the STDLIB, leave it to evaluate it.
	* If it is a user defined function:
		* Create a new env local to this function
		* Initialise the env, add all user defined functions to it too from the primary env
		* Evaluate each of the arguments.
		* Add each evaluated argument to the env, corresponding to the argument name
		* Eval the user-defined function with the new context.
		* The new env auto-deletes since it's stack-allocated

	* ARGS:
		* eval::func *func                  --> Pointer to the function object
		* std::vector<parser::thing *> args --> Vector of pointers to "things" (expr or token) which are the args to the fn
		* context &c                        --> The env

	* RETURNS:
		* eval::value *                     --> Pointer to value obtained on evaluating the fn.

*/
eval::value *eval::func_eval(eval::func *func, std::vector<parser::thing *> args, context &c) {

    if (func->is_std())
        return func->f(args, c);


    std::vector<eval::value *> e_args;
    for (int i = 1; i < args.size(); i++) {
        e_args.push_back(eval::eval(args[i], c));
    }

    context c2;
    stdlib::init_stdlib(c2);

    for (auto i : c) {
        if ((i.second)->get_type() == eval::type::FUNC)
            c2[i.first] = i.second;
    }

    parser::expression *e = func->get_body();
    for (int i = 0; i < func->arg_list->size(); i++) {

        c2[((*(func->arg_list))[i])->get_content()] = e_args[i];

    }

    eval::value *val = eval::eval(e, c2);

    return val;

}

/*

	* Evaluates the Parse Tree.
	* If it's a token:
		* If it's "true" or "false", return a corresponding Boolean
		* If it's composed of digits, return a correpsonding Number
		* If it's a variable in the env, return that
		* Else, return a suitable string

	* If it's an expression:
		* Take the first element, verify that it's a function
		* Match the number of remaining entities in the expression to the num of args of the fn
		* Evaluate the function with those arguments, return the value

	* ARGS:
		* parser::thing *thing --> Pointer to root element of sub-tree to evaluate
		* context &c           --> Reference to Env to evaluate the tree within.

	* RETURNS:
		* eval::value *        --> Pointer to the value obtained

*/
eval::value *eval::eval(parser::thing *thing, context &c) {

    if (thing->t == parser::type::TOKEN) {

        parser::token *t = static_cast<parser::token *>(thing);
        std::string content = t->get_content();

        if (content.compare("true") == 0)
            return new eval::boolean(true);

        if (content.compare("false") == 0)
            return new eval::boolean(false);

        if (is_digits(content)) {
            return new eval::number(std::stod(content));
        }


        eval::value *v = eval::get_var(content, c);
        if (v != NULL) {
            return v;
        } else if (content[0] == '"') {
            return new eval::string(content.substr(1, content.length() - 2));
        }

    } else if (thing->t == parser::type::EXPRESSION) {

        parser::expression *e = static_cast<parser::expression *>(thing);

        eval::value *v = eval::eval(e->things[0], c);

        if (v->get_type() != eval::type::FUNC) {
            stdlib::exit("FIRST TOKEN IN EXPRESSION MUST BE A FUNCTION.");
        }

        eval::func *f = static_cast<eval::func *>(v);

        if (!f->has_var_args() && f->get_n_args() != (e->things.size() - 1)) {
            std::cout << f->get_n_args() << ' ' << f->has_var_args() << std::endl;
            stdlib::exit("INCORRECT NUMBER OF ARGUMENTS.");
        }


        return eval::func_eval(f, e->things, c);

    } else if (thing->t == parser::type::EVALED) {
        eval::value *v = static_cast<eval::value *>(thing);
        return v;
    }

}