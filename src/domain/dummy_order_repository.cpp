#include "order.h"
#include <iostream>
#include "order_repository.h"

class DummyOrderRepository : public OrderRepository {
public:
    void addOrders(const std::vector<Order>& orders) override {
        for (const auto& order : orders) {
            std::cout << "Order added: " << order.getId() << std::endl;
        }
    }
    std::vector<Order> getAllOrders() const override {
        std::cout << "Get all orders" << std::endl;
        return {};
    }
};