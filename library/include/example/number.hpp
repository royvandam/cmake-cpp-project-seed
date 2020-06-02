#pragma once

namespace Example {

class Number
{
public:
    Number(int n = 0);

    int Factorial();
    int Fibonacci();

    void operator=(int n);
    operator int();

protected:
    int _n;
};

}  // namespace Example