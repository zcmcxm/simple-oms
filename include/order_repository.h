#pragma once

#include "order.h"
#include "order_book.h"
#include <memory>
#include <vector>

class OrderRepository
{
public:
    virtual ~OrderRepository() = default;
    virtual void addOrders(const std::vector<Order> &orders) = 0;
    virtual std::shared_ptr<OrderBook> loadOrders() const = 0;
    virtual std::vector<Order> getAllOrders() const = 0;
};

class CsvOrderRepository : public OrderRepository
{
    static constexpr const char *CSV_FILE_PATH = "orders.csv";

public:
    CsvOrderRepository() = default;
    void addOrders(const std::vector<Order> &orders) override;
    std::shared_ptr<OrderBook> loadOrders() const override;

private:
    std::vector<Order> getAllOrders() const override;
    std::string getStoragePath() const;
};