#pragma once

#include <string>
#include <memory>
#include "furniture.h"

class Order
{
private:
    std::string orderID;
    std::string carpenterName;
    std::shared_ptr<Furniture> furnitureItem;
    std::string startDate;
    int estimatedTime;

public:
    // Constructor
    Order(const std::string& id,
          const std::string& name,
          std::shared_ptr<Furniture> item,
          const std::string& date,
          int time);

    virtual ~Order() = default;

    // Getter
    std::string getOrderID() const;
    std::string getCarpenterName() const;
    std::shared_ptr<Furniture> getFurnitureItem() const;
    std::string getStartDate() const;
    int getEstimatedTime() const;

    // Setter
    void setCarpenterName(const std::string& name);
    void setEstimatedTime(int time);
    void setStartDate(const std::string& date);

    void setFurnitureItem(
        std::shared_ptr<Furniture> item);
    // Business Logic
    double calculatePricing() const;
};