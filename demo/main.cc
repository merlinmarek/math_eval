#include <iostream>
#include <string>
#include <math_eval.h>

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "usage: ./demo <mathematical expression>" << std::endl;
        return -1;
    }
    std::string math_expr(argv[1]);
    std::cout << "evaluating " << math_expr << std::endl;
    std::cout << math_eval(infix_to_postfix(math_expr)) << std::endl;
    return 0;
}
