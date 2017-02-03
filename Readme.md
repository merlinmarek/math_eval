Simple evaluation of mathematical expressions in infix notation using the shunting-yard algorithm.

build with:
```
mkdir build
cd build
cmake ..
make
make install
```

After that you can include math_eval.h and link with -lmath_eval.

Example

```
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
```

Be sure to compile with c++11 support like

```
g++ -std=c++11 demo.cc -lmath_eval
```

If you are using cmake to build your project you can use

```
find_package(MathEval)

.
.
.

target_link_libraries(YourProject math_eval)
```
