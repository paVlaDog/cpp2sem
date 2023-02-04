#include "expression.h"

#include <iostream>

int main()
{
    const Add sum = Add(Const(1), Variable("x"));
    for (int i = 0; i < 10; ++i) {
        std::cout << "1 + " << i << " = " << sum.eval({{"x", i}}) << std::endl;
    }
}
