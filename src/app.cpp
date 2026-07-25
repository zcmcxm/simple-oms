#include <algorithm>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "order.h"
#include "order_service.h"
#include "order_repository.h"
#include "portfolio_service.h"

namespace {

std::vector<std::string> splitTokens(const std::string& line) {
    std::istringstream stream(line);
    std::vector<std::string> tokens;
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::optional<Side> parseSide(const std::string& text) {
    if (text == "BUY" || text == "buy") return Side::BUY;
    if (text == "SELL" || text == "sell") return Side::SELL;
    return std::nullopt;
}

std::string toString(OrderType type) {
    switch (type) {
        case OrderType::MARKET: return "MARKET";
        case OrderType::LIMIT: return "LIMIT";
    }
    return "UNKNOWN";
}

std::string toString(Side side) {
    return side == Side::BUY ? "BUY" : "SELL";
}

void printHelp() {
    std::cout << "Available commands:\n"
              << "  help              - show this menu\n"
              << "  market_order      - create a new market order\n"
              << "  limit_order       - create a new limit order\n"
              << "  cancel_order      - cancel an existing order\n"
              << "  fill_order        - fill quantity for an existing order\n"
              << "  view_orders       - list active orders\n"
              << "  view_portfolio    - show portfolio summary\n"
              << "  quit / exit       - exit the application\n";
}

bool promptInt(const std::string& label, int& value) {
    std::string line;
    std::cout << label;
    if (!std::getline(std::cin, line) || line.empty()) {
        return false;
    }
    try {
        value = std::stoi(line);
        return true;
    } catch (...) {
        std::cout << "Invalid number.\n";
        return false;
    }
}

bool promptDouble(const std::string& label, double& value) {
    std::string line;
    std::cout << label;
    if (!std::getline(std::cin, line) || line.empty()) {
        return false;
    }
    try {
        value = std::stod(line);
        return true;
    } catch (...) {
        std::cout << "Invalid decimal number.\n";
        return false;
    }
}

bool promptString(const std::string& label, std::string& value) {
    std::cout << label;
    if (!std::getline(std::cin, value) || value.empty()) {
        std::cout << "Input cannot be empty.\n";
        return false;
    }
    return true;
}

void printOrders(const std::vector<Order>& orders) {
    if (orders.empty()) {
        std::cout << "No orders available.\n";
        return;
    }

    std::cout << "ID | Type | Side | Symbol | Limit Price | Original Quantity | Filled Quantity | Status\n";
    std::cout << "------------------------------------------------------------------------\n";
    for (const auto& order : orders) {
        std::string status = "ACTIVE";
        if (order.getStatus() == OrderStatus::CANCELED) {
            status = "CANCELED";
        } else if (order.getStatus() == OrderStatus::FILLED) {
            status = "FILLED";
        }

        std::cout << order.getId() << " | "
                  << toString(order.getType()) << " | "
                  << toString(order.getSide()) << " | "
                  << order.getSymbol() << " | "
                  << order.getLimitPrice().value_or(0.0) << " | "
                  << order.getOriginalQuantity() << " | "
                  << order.getFilledQuantity() << " | "
                  << status
                  << "\n";
    }
}

void createMarketOrder(OrderService& orderService) {
    std::string sideText;
    if (!promptString("Side (BUY/SELL): ", sideText)) return;

    auto side = parseSide(sideText);
    if (!side) {
        std::cout << "Side must be BUY or SELL.\n";
        return;
    }

    std::string symbol;
    if (!promptString("Symbol: ", symbol)) return;

    int quantity;
    if (!promptInt("Quantity: ", quantity)) return;

    std::string error;
    auto result = orderService.createMarketOrder(*side, symbol, quantity);
    if (result < 0) {
        std::cout << "Failed to create market order: " << error << "\n";
        return;
    }

    std::cout << "Created market order with ID " << result << "\n";
}

void createLimitOrder(OrderService& orderService) {
    std::string sideText;
    if (!promptString("Side (BUY/SELL): ", sideText)) return;

    auto side = parseSide(sideText);
    if (!side) {
        std::cout << "Side must be BUY or SELL.\n";
        return;
    }

    std::string symbol;
    if (!promptString("Symbol: ", symbol)) return;

    int quantity;
    if (!promptInt("Quantity: ", quantity)) return;

    double limitPrice;
    if (!promptDouble("Limit price: ", limitPrice)) return;

    auto result = orderService.createLimitOrder(*side, symbol, quantity, limitPrice);

    std::cout << "Created limit order with ID " << result << "\n";
}

void cancelOrder(OrderService& orderService) {
    int orderId;
    if (!promptInt("Order ID: ", orderId)) return;

    std::string error;
    if (!orderService.cancelOrder(orderId, error)) {
        std::cout << "Cancel failed: " << error << "\n";
        return;
    }

    std::cout << "Order " << orderId << " cancelled.\n";
}

void fillOrder(OrderService& orderService) {
    int orderId;
    if (!promptInt("Order ID: ", orderId)) return;

    int quantity;
    if (!promptInt("Fill quantity: ", quantity)) return;

    std::string error;
    if (!orderService.fillOrder(orderId, quantity, error)) {
        std::cout << "Fill failed: " << error << "\n";
        return;
    }

    std::cout << "Order " << orderId << " filled for " << quantity << " units.\n";
}

// void viewPortfolio(PortfolioService& portfolioService) {
//     std::cout << portfolioService.getSummary() << "\n";
// }

void viewOrders(const OrderService& orderService) {
    auto orders = orderService.getAllOrders();
    printOrders(orders);
}

} // namespace

void runApp(OrderService& orderService, PortfolioService& portfolioService) {
    std::cout << "Order Management System\n";
    printHelp();

    std::string line;
    while (true) {
        std::cout << "\noms> ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        auto tokens = splitTokens(line);
        if (tokens.empty()) {
            continue;
        }

        const std::string& command = tokens[0];
        if (command == "help") {
            printHelp();
        } else if (command == "market_order") {
            createMarketOrder(orderService);
        } else if (command == "limit_order") {
            createLimitOrder(orderService);
        } else if (command == "cancel_order") {
            cancelOrder(orderService);
        } else if (command == "fill_order") {
            fillOrder(orderService);
        } else if (command == "view_portfolio") {
            std::cout << portfolioService.getSummary() << "\n";
        } else if (command == "view_orders") {
            viewOrders(orderService);
        } else if (command == "quit" || command == "exit") {
            break;
        } else {
            std::cout << "Unknown command: " << command << "\n";
        }
    }

    std::cout << "Goodbye.\n";
}
