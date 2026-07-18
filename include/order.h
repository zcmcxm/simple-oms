#pragma once

#include <string>

enum class OrderType { MARKET, LIMIT };
enum class Side { BUY, SELL };
enum class OrderStatus { ACTIVE, CANCELED };

class Order {
public:
    static Order createMarketOrder(Side side, const std::string& symbol, int quantity) {
        return Order(OrderType::MARKET, side, symbol, quantity, 0.0);
    }

    static Order createLimitOrder(Side side, const std::string& symbol, int quantity, double limitPrice) {
        return Order(OrderType::LIMIT, side, symbol, quantity, limitPrice);
    }

    int getId() const noexcept { return id_; }
    OrderType getType() const noexcept { return type_; }
    Side getSide() const noexcept { return side_; }
    const std::string& getSymbol() const noexcept { return symbol_; }
    int getOriginalQuantity() const noexcept { return originalQuantity_; }
    int getFilledQuantity() const noexcept { return filledQuantity_; }
    OrderStatus getStatus() const noexcept { return status_; }
    std::optional<double> getLimitPrice() const noexcept { return limitPrice_; }
    static const std::string_view getCsvHeader() { return csvHeader_; }

private:
    Order(OrderType type, Side side, std::string symbol, int originalQuantity, std::optional<double> limitPrice = std::nullopt)
        : id_(nextId_++),
        type_(type),
        side_(side),
        symbol_(std::move(symbol)),
        originalQuantity_(originalQuantity),
        filledQuantity_(0),
        status_(OrderStatus::ACTIVE),
        limitPrice_(limitPrice)
    {}
    inline static int nextId_ = 0;
    int id_;
    OrderType type_;
    Side side_;
    std::string symbol_;
    std::optional<double> limitPrice_;
    int originalQuantity_;
    int filledQuantity_;
    OrderStatus status_;
    static constexpr std::string_view csvHeader_ = "ID,Type,Side,Symbol,OriginalQuantity,FilledQuantity,Status";
};