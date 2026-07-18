#pragma once

#include <string>

enum class OrderType { MARKET, LIMIT };
enum class Side { BUY, SELL };
enum class OrderStatus { ACTIVE, CANCELED, FILLED };

class Order {
public:
    static Order createMarketOrder(Side side, const std::string& symbol, int originalQuantity) {
        return Order(OrderType::MARKET, side, symbol, originalQuantity, 0, OrderStatus::ACTIVE, std::nullopt);
    }

    static Order createLimitOrder(Side side, const std::string& symbol, int originalQuantity, double limitPrice) {
        return Order(OrderType::LIMIT, side, symbol, originalQuantity, 0, OrderStatus::ACTIVE, limitPrice);
    }

    Order(OrderType type, Side side, std::string symbol, int originalQuantity, int filledQuantity, OrderStatus status, std::optional<double> limitPrice)
        : id_(nextId_++),
        type_(type),
        side_(side),
        symbol_(std::move(symbol)),
        originalQuantity_(originalQuantity),
        filledQuantity_(filledQuantity),
        status_(status),
        limitPrice_(limitPrice)
    {}

    int getId() const noexcept { return id_; }
    OrderType getType() const noexcept { return type_; }
    Side getSide() const noexcept { return side_; }
    const std::string& getSymbol() const noexcept { return symbol_; }
    int getOriginalQuantity() const noexcept { return originalQuantity_; }
    int getFilledQuantity() const noexcept { return filledQuantity_; }
    OrderStatus getStatus() const noexcept { return status_; }
    std::optional<double> getLimitPrice() const noexcept { return limitPrice_; }
    static const std::string_view getCsvHeader() { return csvHeader_; }
    void markAsCanceled() { status_ = OrderStatus::CANCELED; }
    void fillQuantity(int quantity) { 
        filledQuantity_ += quantity; 
        if (filledQuantity_ >= originalQuantity_) {
            status_ = OrderStatus::FILLED; // Assuming order is completed when filled quantity reaches original quantity
        }
    }

private:
    inline static int nextId_ = 0;
    int id_;
    OrderType type_;
    Side side_;
    std::string symbol_;
    std::optional<double> limitPrice_;
    int originalQuantity_;
    int filledQuantity_;
    OrderStatus status_;
    static constexpr std::string_view csvHeader_ = "ID,Type,Side,Symbol,LimitPrice,OriginalQuantity,FilledQuantity,Status";
};