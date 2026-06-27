cmake_minimum_required(VERSION 3.16)
project(OrderManagementSystem VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Enable building tests" ON)

# Include headers from the top-level include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES
    src/main.cpp
    src/app.cpp
    src/domain/order_service.cpp
    src/domain/portfolio_service.cpp
    src/domain/csv_order_repository.cpp
    src/model/order_book.cpp
)

add_executable(oms ${SOURCE_FILES})

target_include_directories(oms PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_compile_options(oms PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
)

if (BUILD_TESTING)
    enable_testing()
endif()
