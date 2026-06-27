#pragma once

#include <string>
#include "order.h"

class LimitOrder : public Order {
    private:
        double limitPrice_;
    public:
        LimitOrder(Side side, const std::string& symbol, int quantity, double limitPrice)
            : Order(OrderType::LIMIT, side, symbol, quantity), limitPrice_(limitPrice) {}
        
        double getLimitPrice() const noexcept { return limitPrice_; }
};