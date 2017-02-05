#include <iostream>
#include <stdexcept>
#include <stack>
#include <queue>
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

std::queue<Token> tokenize_string(std::string str);
std::queue<Token> infix_to_postfix(std::string infix_string);
float math_eval(std::queue<Token> postfix_tokens);
