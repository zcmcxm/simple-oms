#pragma once

#include "order.h"
#include <string>

class MarketOrder : public Order {
    public:
        MarketOrder(Side side, const std::string& symbol, int quantity)
            : Order(OrderType::MARKET, side, symbol, quantity) {}
};