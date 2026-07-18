#include "order.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "order_repository.h"

namespace {

std::string getProjectRoot() {
    return std::filesystem::current_path().parent_path().string();
}

} // namespace

std::string CsvOrderRepository::getStoragePath() const {
    return std::filesystem::path(getProjectRoot()) / CSV_FILE_PATH;
}

void CsvOrderRepository::addOrders(const std::vector<Order>& orders)
{
    const auto path = getStoragePath();
    std::ofstream file(path);

    if (file.is_open())
    {
        file << Order::getCsvHeader() << "\n";

        for (const auto& order : orders)
        {
            file << order.getId() << ","
                 << static_cast<int>(order.getType()) << ","
                 << static_cast<int>(order.getSide()) << ","
                 << order.getSymbol() << ","
                 << order.getOriginalQuantity() << ","
                 << order.getFilledQuantity() << ","
                 << static_cast<int>(order.getStatus()) << "\n";
        }
        file.close();
    }
}

std::vector<Order> CsvOrderRepository::getAllOrders() const
{
    std::vector<Order> orders;
    const auto path = getStoragePath();
    std::ifstream file(path);
    if (!file.is_open())
    {
        return orders;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        if (row.size() >= 7)
        {
            orders.emplace_back(
                static_cast<OrderType>(std::stoi(row[1])),
                static_cast<Side>(std::stoi(row[2])),
                row[3],
                std::stoi(row[4]),
                std::stoi(row[5]),
                static_cast<OrderStatus>(std::stoi(row[6]))
            );
        }
    }

    file.close();
    return orders;
}

std::shared_ptr<OrderBook> CsvOrderRepository::loadOrders() const
{
    auto orders = getAllOrders();
    return std::make_shared<OrderBook>(orders);
}