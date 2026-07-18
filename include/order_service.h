#pragma once

#include "order_repository.h"
#include "order.h"
#include "order_book.h"

class OrderService {
    private:
        std::shared_ptr<OrderBook> orderBook;
        std::shared_ptr<OrderRepository> orderRepository;
    public:
        OrderService(std::shared_ptr<OrderBook> book, std::shared_ptr<OrderRepository> repository);
        void submitOrder(const Order& order);
        int createLimitOrder(Side side, std::string symbol, int quantity, double limitPrice);
        int createMarketOrder(Side side, std::string symbol, int quantity);
        bool cancelOrder(int orderId, std::string& error);
        bool fillOrder(int orderId, int quantity, std::string& error);
        std::vector<Order> getAllOrders() const;
};