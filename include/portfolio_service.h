#pragma once

#include <string>
#include "order_repository.h"

class PortfolioService {
    private:
        OrderBook& orderBook;
    public:
        PortfolioService(OrderBook& book);
        std::string getSummary() const;
};