#include "order.h"
#include "order_repository.h"
#include "order_service.h"

OrderService::OrderService(std::shared_ptr<OrderBook> book, std::shared_ptr<OrderRepository> repository) : orderBook(book), orderRepository(repository) {}

void OrderService::submitOrder(const Order &order)
{
    this->orderBook->addOrder(order);
    this->orderRepository->addOrders(this->orderBook->getOrders());
}

int OrderService::createLimitOrder(Side side, std::string symbol, int quantity, double limitPrice)
{
    Order order = Order::createLimitOrder(side, symbol, quantity, limitPrice);
    this->orderBook->addOrder(order);
    this->orderRepository->addOrders(this->orderBook->getOrders());
    return order.getId();
}

int OrderService::createMarketOrder(Side side, std::string symbol, int quantity)
{
    Order order = Order::createMarketOrder(side, symbol, quantity);
    this->orderBook->addOrder(order);
    this->orderRepository->addOrders(this->orderBook->getOrders());
    return order.getId();
}

bool OrderService::cancelOrder(int orderId, std::string &error)
{
    Order* order = this->orderBook->getOrderById(orderId);
    if (!order)
    {
        error = "Order not found";
        return false;
    }

    if (order->getStatus() == OrderStatus::CANCELED)
    {
        error = "Order is already canceled";
        return false;
    }

    order->markAsCanceled();
    this->orderRepository->addOrders(this->orderBook->getOrders());
    return true;
}

bool OrderService::fillOrder(int orderId, int quantity, std::string &error)
{
    if (quantity <= 0)
    {
        error = "Fill quantity must be greater than zero";
        return false;
    }
    
    Order* order = this->orderBook->getOrderById(orderId);
    if (!order)
    {
        error = "Order not found";
        return false;
    }

    if (order->getStatus() == OrderStatus::CANCELED)
    {
        error = "Cannot fill a canceled order";
        return false;
    }

    if (order->getStatus() == OrderStatus::FILLED)
    {
        error = "Order is already filled";
        return false;
    }

    int remaining = order->getOriginalQuantity() - order->getFilledQuantity();
    if (quantity > remaining)
    {
        error = "Fill quantity exceeds remaining order quantity";
        return false;
    }

    order->fillQuantity(quantity);
    this->orderRepository->addOrders(this->orderBook->getOrders());
    return true;
}

std::vector<Order> OrderService::getAllOrders() const
{
    return this->orderBook->getOrders();
}
