#include <math_eval.h>

enum class Association {LEFT, RIGHT};

std::map<std::string, std::tuple<int, Association>> operator_config = {
    {"+", std::tuple<int, Association>{2, Association::LEFT}},
    {"-", std::tuple<int, Association>{2, Association::LEFT}},
    {"*", std::tuple<int, Association>{3, Association::LEFT}},
    {"/", std::tuple<int, Association>{3, Association::LEFT}},
    {"^", std::tuple<int, Association>{4, Association::RIGHT}}
};

std::map<std::string, std::function<float(float)>> functions = {
    {"sin", (float(*)(float))std::sin},
    {"cos", (float(*)(float))std::cos},
    {"tan", (float(*)(float))std::tan},
    {"asin", (float(*)(float))std::asin},
    {"acos", (float(*)(float))std::acos},
    {"atan", (float(*)(float))std::atan},
    {"sinh", (float(*)(float))std::sinh},
    {"cosh", (float(*)(float))std::cosh},
    {"tanh", (float(*)(float))std::tanh},
    {"asinh", (float(*)(float))std::asinh},
    {"acosh", (float(*)(float))std::acosh},
    {"atanh", (float(*)(float))std::atanh},
    {"log", (float(*)(float))std::log},
    {"log10", (float(*)(float))std::log10},
    {"exp", (float(*)(float))std::exp},
    {"sqrt", (float(*)(float))std::sqrt},
    {"cbrt", (float(*)(float))std::cbrt},
    {"fabs", (float(*)(float))std::fabs},
}; 

std::queue<Token> tokenize_string(std::string str)
{
    std::queue<Token> tokens;
    Token token;
    for(char c : str)
    {
        TokenType type; 
        switch(c)
        {
            case '(':
            case ')':
                type = TokenType::BRACE;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                type = TokenType::NUMBER;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                type = TokenType::OPERATOR;
                break;
            default:
                type = TokenType::FUNCTION;

        }
        if(!token.value.empty())
        {
            if(token.type == type)
            {
                token.value.push_back(c);
            }
            else
            {
               tokens.emplace(token); 
               token.value = "";
            }
        }
        if(token.value.empty())
        {
            token.value = std::string(1, c);
            token.type = type;
            if(type == TokenType::BRACE)
            {
                tokens.emplace(token);
                token.value = "";
            }
        }
    }
    if(token.value != "")
        tokens.emplace(token);
    return tokens;
}

std::queue<Token> infix_to_postfix(std::string infix_string)
{
    auto end_pos = std::remove(infix_string.begin(), infix_string.end(), ' ');
    infix_string.erase(end_pos, infix_string.end());

    std::queue<Token> tokens = tokenize_string(infix_string);

    std::stack<Token> stack;
    std::queue<Token> queue;

    while(tokens.size())
    {
        auto token = tokens.front();
        tokens.pop();
        switch(token.type)
        {
            case TokenType::NUMBER:
                queue.push(token);
                break;
            case TokenType::FUNCTION:
                stack.push(token);
                break;
            case TokenType::OPERATOR:
                while(stack.size() && stack.top().type == TokenType::OPERATOR)
                {
                    auto config_1 = operator_config[token.value];
                    auto a_1 = std::get<1>(config_1);
                    auto p_1 = std::get<0>(config_1);
                    auto config_2 = operator_config[stack.top().value];
                    auto p_2 = std::get<0>(config_2);
                    if((a_1 == Association::LEFT && p_1 <= p_2) ||
                        (a_1 == Association::RIGHT && p_1 < p_2))
                    {
                        queue.push(stack.top());
                        stack.pop();
                    }
                    else
                    {
                        break;
                    }
                }
                stack.push(token);
                break;
            case TokenType::BRACE:
                if(token.value == "(")
                {
                    stack.push(token);
                }
                else
                {
                    while(stack.size() && stack.top().value != "(")
                    {
                        queue.push(stack.top());
                        stack.pop();
                    }
                    if(stack.top().value != "(")
                    {
                        //BAD INPUT -> NO MATCHING PARENTHESIS
                    }
                    else
                    {
                        stack.pop();
                        if(stack.size() && stack.top().type == TokenType::FUNCTION)
                        {
                            queue.push(stack.top());
                            stack.pop();
                        }
                    }
                }
                break;
        }
    }
    // no more tokens to read
    while(stack.size())
    {
        if(stack.top().type == TokenType::OPERATOR)
        {
            queue.push(stack.top());
            stack.pop();
        }
        else
        {
            //BAD INPUT
            break;
        }
    }
    return queue;
}

float math_eval(std::queue<Token> postfix_tokens)
{
    std::stack<float> operands;
    while(postfix_tokens.size())
    {
        auto token = postfix_tokens.front();
        postfix_tokens.pop();
        if(token.type == TokenType::NUMBER)
        {
            operands.push(std::stof(token.value));
        }
        else if(token.type == TokenType::OPERATOR)
        {
            auto op2 = operands.top();
            operands.pop();
            auto op1 = operands.top();
            operands.pop();

            if(token.value == "+")
                operands.push(op1 + op2);
            else if(token.value == "-")
                operands.push(op1 - op2);
            else if(token.value == "*")
                operands.push(op1 * op2);
            else if(token.value == "/")
                operands.push(op1 / op2);
            else if(token.value == "^")
                operands.push(std::pow(op1, op2));
        }
        else if(token.type == TokenType::FUNCTION)
        {
            auto op = operands.top();
            operands.pop();
            auto func = functions.find(token.value);
            if(func != functions.end())
            {
                operands.push(func->second(op));
            }
        }
        else //ERROR
        {

        }
    }
    return operands.size() ? operands.top() : 0.0f;
}
//int main(int argc, char** argv)
//{
//    std::string infix_string(argv[1]);
//    std::cout << "infix string\t" << infix_string << std::endl;
//    //std::string postfix_string = infix_to_postfix(infix_string);
//    auto postfix_tokens = infix_to_postfix(infix_string);
//    //std::string postfix_string = "";
//    //while(postfix_tokens.size())
//    //{
//    //    postfix_string += postfix_tokens.front().value;
//    //    postfix_tokens.pop();
//    //}
//    //std::cout << "postfix string\t" <<  postfix_string << std::endl;
//    std::cout << "math_eval\t" << math_eval(postfix_tokens) << std::endl;
//    return 0;
//}
