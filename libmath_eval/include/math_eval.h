#include <iostream>
#include <stdexcept>
#include <stack>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>
#include <cmath>

enum class TokenType {NUMBER, OPERATOR, FUNCTION, BRACE};

class Token
{
public: 
    std::string value;
    TokenType type;
};

std::deque<Token> tokenize_string(std::string str);
std::deque<Token> infix_to_postfix(std::string infix_string);
float math_eval(std::deque<Token> postfix_tokens);
