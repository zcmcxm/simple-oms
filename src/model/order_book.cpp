#include <iostream>
#include "order_book.h"
#include "order.h"

std::vector<Order> OrderBook::getOrders() const
{
    return orders;
}

Order* OrderBook::getOrderById(int id)
{
    for (auto &order : orders)
    {
        if (order.getId() == id)
        {
            return &order;
        }
    }
    return nullptr;
}

const Order* OrderBook::getOrderById(int id) const
{
    for (const auto &order : orders)
    {
        if (order.getId() == id)
        {
            return &order;
        }
    }
    return nullptr;
}

void OrderBook::addOrder(const Order &order)
{
    orders.push_back(order);
}