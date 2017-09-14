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
} // namespace parser

enum class parser::type { TOKEN, EXPRESSION };

class parser::thing {
public:
  type t;
};

class parser::token : public parser::thing {
  std::string content;

public:
  explicit token(std::string s) {
    content = s;
    t = parser::type::TOKEN;
  }

  std::string get_content() { return content; }
};

class parser::expression : public parser::thing {

public:
  std::vector<parser::thing> things;
  expression() { t = parser::type::EXPRESSION; }

  void insert_thing(thing t) { things.push_back(t); }
};

#endif // _USERS_MARUTHGOYAL_SP_PARSER_PARSER_HPP_
