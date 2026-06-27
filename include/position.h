#include <string>

class Position {
    private:
        std::string symbol;
        int quantity;
        double averagePrice;
    public:
        Position() : symbol(""), quantity(0), averagePrice(0.0) {};
        Position(std::string sym, int q, double p) : symbol(sym), quantity(q), averagePrice(p) {};
};