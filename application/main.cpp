#include <example/number.hpp>

#include <iostream>

int
main() {
    Example::Number n(42);
    std::cout << "The 42th number of the fibonacci sequence = " << n.Fibonacci() << std::endl;
    return 0;
}