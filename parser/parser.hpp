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
