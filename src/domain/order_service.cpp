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
    // For simplicity, just return true. In a real implementation, you'd check if the order exists and can be cancelled.
    return true;
}

std::vector<Order> OrderService::getAllOrders() const
{
    return this->orderBook->getOrders();
}
