#include "order_service.h"
#include "portfolio_service.h"
#include "order_repository.h"
#include "order_book.h"

void runApp(OrderService& orderService, PortfolioService& portfolioService);

int main() {
    auto repository = std::make_shared<CsvOrderRepository>();
    auto orderBook = repository->loadOrders();
    PortfolioService portfolioService(repository);
    OrderService orderService(orderBook, repository);

    runApp(orderService, portfolioService);
    return 0;
}
