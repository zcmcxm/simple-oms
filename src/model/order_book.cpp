#include <iostream>
#include "order_book.h"
#include "order.h"

std::vector<Order> OrderBook::getOrders() const
{
    return orders;
}

std::optional<Order> OrderBook::getOrderById(int id) const
{
    for (const auto &order : orders)
    {
        if (order.getId() == id)
        {
            return order;
        }
    }
    std::cout << "Order not found" << std::endl;
    return std::nullopt;
}

void OrderBook::addOrder(const Order &order)
{
    orders.push_back(order);
}