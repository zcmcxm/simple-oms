#pragma once
#include "order.h"
#include <vector>
#include <optional>
#include <iostream>

class OrderBook
{
    std::vector<Order> orders;

public:
    OrderBook() : orders() {}
    OrderBook(std::vector<Order> orders) : orders(orders) {}
    std::vector<Order> getOrders() const;
    std::optional<Order> getOrderById(int id) const;
    void addOrder(const Order &order);
};