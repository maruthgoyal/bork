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

eval::value *eval(parser::thing *, std::unordered_map<std::string, eval::value *> &);

eval::value *get_var(std::string, std::unordered_map<std::string, eval::value *> &);

eval::value *
func_eval(eval::func *, std::vector<parser::thing *>, std::unordered_map<std::string, eval::value *> &);

}

typedef std::unordered_map<std::string, eval::value *> context;
enum class eval::type {
  NUMBER, STRING, BOO, FUNC
};

class eval::value : public parser::thing {

  eval::type ty;

 public:

  value() {
    t = parser::type::EVALED;
  }

  eval::type get_type() {
    return ty;
  }

  void set_type(eval::type typ) {
    ty = typ;
  }

  virtual std::string to_string() { return std::string(""); };

};

class eval::func : public eval::value {

  parser::expression *body;
  bool eval_args, var_args;
  bool is_std_fn;

 public:

  eval::value *(*f)(std::vector<parser::thing *>, context &);

  std::vector<parser::token *> *arg_list;

  explicit func(parser::expression *func_body, std::vector<parser::token *> *args_list, bool to_eval_args,
                bool std_fn) {
    body = func_body;
    arg_list = args_list;
    eval_args = to_eval_args;
    is_std_fn = std_fn;
    set_type(eval::type::FUNC);
  }

  explicit func(eval::value *(*g)(std::vector<parser::thing *>, context &),
                std::vector<parser::token *> *args_list, bool to_eval_args,
                bool std_fn, bool v_args) {
    f = g;
    arg_list = args_list;
    eval_args = to_eval_args;
    is_std_fn = std_fn;
    var_args = v_args;
    set_type(eval::type::FUNC);
  }

  parser::expression *get_body() {
    return body;
  }

  int get_n_args() {
    return arg_list->size();
  }

  bool has_var_args() {
    return var_args;
  }

  bool to_eval_args() {
    return eval_args;
  }

  bool is_std() {
    return is_std_fn;
  }

  std::string to_string() {
    return std::string("");
  }

};

class eval::number : public eval::value {

  double val;

 public:

  explicit number(double d) {
    val = d;
    set_type(eval::type::NUMBER);
  }

  double get_val() {
    return val;
  }

  std::string to_string() {
    return std::to_string(val);
  }

};

class eval::string : public eval::value {

  std::string val;

 public:

  explicit string(std::string s) {
    val = s;
    set_type(eval::type::STRING);
  }

  std::string get_val() {
    return val;
  }

  std::string to_string() {
    return val;
  }

};

class eval::boolean : public eval::value {
  bool val;

 public:

  explicit boolean(bool b) {
    val = b;
    set_type(eval::type::BOO);
  }

  bool get_val() {
    return val;
  }

  void negate() {
    val = !val;
  }

  std::string to_string() {

    if (val)
      return std::string("true");

    return std::string("false");

  }
};

#endif  // _USERS_MARUTHGOYAL_SP_EVAL_EVAL_HPP_
