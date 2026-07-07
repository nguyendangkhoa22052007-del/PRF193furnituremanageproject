#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "furniture.h"
#include "order.h"
class ManufacturingSystem {
private:
    //List
    std::vector<std::shared_ptr<Furniture>> furnitureList;
    std::vector<std::unique_ptr<Order>> orderList;

    // Advanced Logic: Using STL MAP to sort by material
    std::map<std::string, std::vector<std::shared_ptr<Furniture>>> furnitureByMaterial;

public:
    ManufacturingSystem() = default;
    virtual ~ManufacturingSystem() = default;
    //ADDING
    void addFurniture(std::shared_ptr<Furniture> item);
    void addOrder(std::unique_ptr<Order> order);

    //SEARCHING & UPDATING
    std::shared_ptr<Furniture> searchFurnitureByID(const std::string& id) const;
    std::vector<std::shared_ptr<Furniture>> searchFurnitureByMaterial(const std::string& material) const;
    
    bool updateFurnitureDetails(const std::string& id, const std::string& newMaterial, double newSize, const std::string& newColor);
    //STL MAP
    void classifyFurnitureByMaterial();
    const std::map<std::string, std::vector<std::shared_ptr<Furniture>>>& getFurnitureMap() const;

    //GET LIST FUNCTION
    const std::vector<std::shared_ptr<Furniture>>& getFurnitureList() const;
    const std::vector<std::unique_ptr<Order>>& getOrderList() const;
    //Sorting
    template <typename Comparator>
    void sortOrders(Comparator comp) {
        size_t n = orderList.size();
        
        for (size_t i = 0; i < n - 1; ++i) {
            size_t targetIndex = i;
            for (size_t j = i + 1; j < n; ++j) {
                //Lambda function 'comp'
                if (comp(orderList[j], orderList[targetIndex])) {
                    targetIndex = j;
                }
            }

            if (targetIndex != i) {
                std::swap(orderList[i], orderList[targetIndex]);
            }
        }
    }
};