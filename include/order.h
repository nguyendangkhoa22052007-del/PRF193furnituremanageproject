#pragma once
#include <string>
#include <memory>   //std::shared_ptr
#include "furniture.h"

class Order {
private:
    std::string orderID;
    std::string carpenterName;
    std::shared_ptr<Furniture> furnitureItem; //smart pointer 
    std::string startDate;
    int estimatedTime;

public:
    //(CONSTRUCTOR & DESTRUCTOR)
    //smart pointer
    Order(std::string id, std::string name, std::shared_ptr<Furniture> item, std::string date, int time);
    
    virtual ~Order() = default;
    //GETTER FUNCTIONS
    std::string getOrderID() const;
    std::string getCarpenterName() const;
    std::shared_ptr<Furniture> getFurnitureItem() const;
    std::string getStartDate() const;
    int getEstimatedTime() const;
    //SETTER FUNCTIONS
    void setCarpenterName(std::string name);
    void setEstimatedTime(int time);
    double calculatePricing() const; 
};