#include <map>
#include <sstream>
#include <string>

#include "order.h"
#include "portfolio_service.h"

PortfolioService::PortfolioService(OrderBook& book): orderBook(book) {}

std::string PortfolioService::getSummary() const {
    std::map<std::string, int> netPositions;
    std::map<std::string, int> filledVolumes;
    std::map<std::string, int> openVolumes;

    for (const auto& order : orderBook.getOrders()) {
        if (order.getStatus() == OrderStatus::CANCELED) {
            continue;
        }

        const std::string& symbol = order.getSymbol();
        const int filled = order.getFilledQuantity();
        const int remaining = std::max(0, order.getOriginalQuantity() - filled);

        filledVolumes[symbol] += filled;
        if (order.getStatus() != OrderStatus::FILLED) {
            openVolumes[symbol] += remaining;
        }

        if (order.getSide() == Side::BUY) {
            netPositions[symbol] += filled;
        } else {
            netPositions[symbol] -= filled;
        }
    }

    std::ostringstream summary;
    summary << "Portfolio Summary:";

    if (netPositions.empty()) {
        summary << " No active positions.";
        return summary.str();
    }

    for (const auto& [symbol, net] : netPositions) {
        summary << " " << symbol << ": net=" << net
                << " (filled=" << filledVolumes[symbol]
                << ", open=" << openVolumes[symbol] << ")";
    }

    return summary.str();
}