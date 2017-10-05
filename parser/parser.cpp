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
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "parser.hpp"
#include "../stdlib/stdlib.hpp"

/*
  * Tokenize and parse string

  * If Opening Paren:
    * Create a new expression. 
    * Increment the stack
    * Keep parsing the rest till the stack is empty
    * Add each new item to the "things" in the expression

  * If Closing Paren:
    * Decrement the stack

  * Otherwise Read as a token:
    * Tokens are seperated by whitespace
    * If, however, there's a " mark, we ignore spaces and read till we match the "

  * ARGS:
    * std::string s            --> String to parse
    * int &i                   --> Integer keeping track of the position we're at in the string
    * std::vector<char> &stack --> Reference to a vector representing the stack tracking the Parens

  * RETURNS:
    * parser::thing *          --> Pointer to a "thing" (token or expression) which is the root node in the tree
*/

parser::thing* parse_(std::string s, int &i, std::vector<char> &stack) {
 
  while (std::isspace(s[i]) && i < s.length()) i++;

  if (s[i] == '(') {

    parser::expression* e = new parser::expression;

    stack.push_back('(');
    i++;

    while (!stack.empty()) {
      if(!(e->insert_thing(parse_(s, i, stack))))
        break;
    }  // stack empty checking WHILE ENDs

    return e;
 
  }

  else if (s[i] == ')') {
   
    if (stack.empty())
      stdlib::exit("UNMATCHED BRACES");
  
    stack.pop_back();
    i++;
  
  }

  else {
   
    std::string buff;
    bool ignore_space = false, started_string = false;

    while ((ignore_space || !isspace(s[i])) && s[i] != ')') {
      
      buff.push_back(s[i]);
      i++;

      if (s[i-1] == '"') {
        
        if (!started_string) {
          started_string = true;
          ignore_space = true;
        }

        else
          break;

      }
    
    }

    parser::token *t = new parser::token(buff);
    return t;

  }

  return NULL;

}

/*
  * Tokenize and parse string into a tree.
  * ARGS:
    * std::string s --> String to parse
  * RETURNS:
    * parser::thing *  --> Pointer to a "thing" (token or expression) which is the root of the parse tree 
*/
parser::thing* parser::parse(std::string s) {

  int i = 0;
  std::vector<char> stack;
  return parse_(s, i, stack);

}
