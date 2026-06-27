#pragma once

#include <string>

enum class OrderType { MARKET, LIMIT };
enum class Side { BUY, SELL };

class Order {
public:
    Order(OrderType type, Side side, std::string symbol, int quantity)
        : id_(nextId_++),
          type_(type),
          side_(side),
          symbol_(std::move(symbol)),
          quantity_(quantity)
    {}

    virtual ~Order() = default;

    int getId() const noexcept { return id_; }
    OrderType getType() const noexcept { return type_; }
    Side getSide() const noexcept { return side_; }
    const std::string& getSymbol() const noexcept { return symbol_; }
    int getQuantity() const noexcept { return quantity_; }
    static const std::string_view getCsvHeader() { return csvHeader_; }

private:
    inline static int nextId_ = 0;
    int id_;
    OrderType type_;
    Side side_;
    std::string symbol_;
    int quantity_;
    static constexpr std::string_view csvHeader_ = "ID,Type,Side,Symbol,Quantity";
};