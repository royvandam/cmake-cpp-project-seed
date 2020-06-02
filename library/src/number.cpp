#include <example/number.hpp>

namespace Example {

Number::Number(int n) : _n(n) {}

void
Number::operator=(int n) {
    _n = n;
}

Number::operator int() { return _n; }

int
Number::Factorial() {
    int factorial = 1;
    for (int i = 1; i <= _n; ++i) {
        factorial *= i;
    }
    return factorial;
}

int
Number::Fibonacci() {
    int a = 0, b = 1, c, i;

    if (_n == 0) {
        return 0;
    }

    for (i = 2; i <= _n; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}

}  // namespace Example