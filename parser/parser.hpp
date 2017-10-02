// "Copyright 2017 Maruth Goyal"
#ifndef _USERS_MARUTHGOYAL_SP_PARSER_PARSER_HPP_
#define _USERS_MARUTHGOYAL_SP_PARSER_PARSER_HPP_

#include <string>
#include <vector>

namespace parser {

  class thing;
  class token;
  class expression;
  enum class type;
  parser::thing *parse(std::string);

} // namespace parser

enum class parser::type { 

  TOKEN, EXPRESSION, EVALED

};

class parser::thing {

public:
  type t;

};

class parser::token : public parser::thing {
 
  std::string content;

public:
 
  explicit token(const std::string &s) {
 
    content.assign(s);
    t = parser::type::TOKEN;
 
  }

  std::string get_content() { 
    return content;
  }
 
  void set_content(std::string s) { 
    content = s;
  }

};

class parser::expression : public parser::thing {

public:
 
  std::vector<parser::thing *> things;
 
  expression() {

    t = parser::type::EXPRESSION;

  }

  bool insert_thing(thing *t) {

    if (t != NULL) {
      things.push_back(t);
      return true;
    }

    return false;
    
  }

};

#endif // _USERS_MARUTHGOYAL_SP_PARSER_PARSER_HPP_
