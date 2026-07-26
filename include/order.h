#pragma once

#include <string>
#include <memory>
#include "../include/furniture.h"

enum class OrderStatus
{
    Pending,
    InProgress,
    Completed
};

class Order
{
private:
    std::string orderID;
    std::string carpenterName;
    std::shared_ptr<Furniture> furnitureItem;
    std::string startDate;
    int estimatedTime;

    // Order status
    OrderStatus status;

public:
    // Constructor
    Order(const std::string& id,
          const std::string& name,
          std::shared_ptr<Furniture> item,
          const std::string& date,
          int time);

    virtual ~Order() = default;

    //-------------------------
    // Helper Functions
    //-------------------------

    static std::string statusToString(OrderStatus status);

    static OrderStatus stringToStatus(
        const std::string& status);

    //-------------------------
    // Getter
    //-------------------------

    std::string getOrderID() const;

    std::string getCarpenterName() const;

    std::shared_ptr<Furniture> getFurnitureItem() const;

    std::string getStartDate() const;

    int getEstimatedTime() const;

    OrderStatus getStatus() const;

    //-------------------------
    // Setter
    //-------------------------

    void setCarpenterName(
        const std::string& name);

    void setEstimatedTime(int time);

    void setStartDate(
        const std::string& date);

    void setFurnitureItem(
        std::shared_ptr<Furniture> item);

    void setStatus(OrderStatus status);

    //-------------------------
    // Business Logic
    //-------------------------

    double calculatePricing() const;
};