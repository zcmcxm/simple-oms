#pragma once

#include <string>
#include "order_repository.h"

class PortfolioService {
    private:
        std::shared_ptr<OrderRepository> orderRepository;
    public:
        PortfolioService(std::shared_ptr<OrderRepository> repository);
        std::string getSummary() const;
};