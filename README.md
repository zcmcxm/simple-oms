# Simple OMS

A lightweight **Order Management System** written in modern C++ (C++17). It runs as an interactive command-line app that lets you create, cancel and fill orders, and view a running portfolio summary. Orders are persisted to a CSV file, so your order book survives restarts.

## Features

- **Market & limit orders** — create BUY/SELL orders for any symbol
- **Order lifecycle** — `ACTIVE` → `FILLED` (full or partial fills) or `CANCELED`, with validation (no overfills, no filling canceled orders, etc.)
- **Portfolio view** — net position per symbol, plus filled and open volume
- **CSV persistence** — every change is saved to `orders.csv` and reloaded on startup

## Build & Run

Requirements: CMake ≥ 3.16 and a C++17 compiler (Clang or GCC).

```bash
cmake -S . -B build
cmake --build build
cd build && ./oms
```

> Run the binary from inside `build/` — orders are stored in `orders.csv` in the project root (the parent of the working directory).

## Usage

```text
oms> limit_order
Side (BUY/SELL): BUY
Symbol: AAPL
Quantity: 100
Limit price: 189.5
Created limit order with ID 0

oms> fill_order
Order ID: 0
Fill quantity: 40
Order 0 filled for 40 units.

oms> view_orders
ID | Type | Side | Symbol | Limit Price | Original Quantity | Filled Quantity | Status
------------------------------------------------------------------------
0 | LIMIT | BUY | AAPL | 189.5 | 100 | 40 | ACTIVE

oms> view_portfolio
Portfolio Summary: AAPL: net=40 (filled=40, open=60)
```

| Command          | Description                          |
| ---------------- | ------------------------------------ |
| `market_order`   | Create a new market order            |
| `limit_order`    | Create a new limit order             |
| `cancel_order`   | Cancel an existing order             |
| `fill_order`     | Fill quantity on an existing order   |
| `view_orders`    | List all orders                      |
| `view_portfolio` | Show portfolio summary               |
| `help`           | Show the command menu                |
| `quit` / `exit`  | Exit the application                 |

## Project Structure

```text
include/                    Headers (Order, OrderBook, services, repository interface)
src/
├── main.cpp                Wires up the repository, order book and services
├── app.cpp                 Interactive CLI loop and input handling
├── domain/
│   ├── order_service.cpp       Order creation, cancel and fill logic
│   ├── portfolio_service.cpp   Position aggregation
│   └── csv_order_repository.cpp  CSV load/save
└── model/
    └── order_book.cpp      In-memory order storage
```

The design separates concerns into layers: the **CLI** (`app.cpp`) talks to **services** (`OrderService`, `PortfolioService`), which operate on a shared in-memory **`OrderBook`** and persist through an abstract **`OrderRepository`** interface — so the CSV backend can be swapped for another storage implementation.
