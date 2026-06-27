#pragma once

#include <string>

class PortfolioService {
    private:
        std::shared_ptr<OrderRepository> orderRepository;
    public:
        PortfolioService(std::shared_ptr<OrderRepository> repository);
        std::string getSummary() const;
};