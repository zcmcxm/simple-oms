#pragma once

#include <string>

class Execution {
    private:
        std::string symbol;
        int quantity;
        double price;
    public:
        Execution(std::string sym, int q, double p) : symbol(sym), quantity(q), price(p) {};
};