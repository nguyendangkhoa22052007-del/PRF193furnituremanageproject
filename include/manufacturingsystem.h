#pragma once

#include <vector>
#include <map>
#include <memory>
#include <string>
#include <algorithm>

#include "furniture.h"
#include "order.h"

class ManufacturingSystem
{
private:

    std::vector<std::shared_ptr<Furniture>> furnitureList;

    std::vector<std::unique_ptr<Order>> orderList;

    std::map<
        MaterialType,
        std::vector<std::shared_ptr<Furniture>>
    > furnitureByMaterial;

public:

    ManufacturingSystem() = default;

    ~ManufacturingSystem() = default;

    //-------------------------
    // Furniture
    //-------------------------

    void addFurniture(std::shared_ptr<Furniture> item);

    bool deleteFurniture(const std::string& id);

    std::shared_ptr<Furniture>
    searchFurnitureByID(const std::string& id) const;

    std::vector<std::shared_ptr<Furniture>>
    searchFurnitureByMaterial(MaterialType material) const;

    bool updateFurnitureDetails(
        const std::string& id,
        MaterialType material,
        double length,
        double width,
        double height,
        const std::string& color
    );

    void displayFurniture() const;

    //-------------------------
    // Order
    //-------------------------

    void addOrder(std::unique_ptr<Order> order);

    bool deleteOrder(const std::string& id);

    Order* searchOrderByID(
        const std::string& id
    ) const;

    void displayOrders() const;

    //-------------------------
    // Classification
    //-------------------------

    void classifyFurnitureByMaterial();

    const std::map<
        MaterialType,
        std::vector<std::shared_ptr<Furniture>>
    >& getFurnitureMap() const;

    //-------------------------
    // Getter
    //-------------------------

    const std::vector<std::shared_ptr<Furniture>>&
    getFurnitureList() const;

    const std::vector<std::unique_ptr<Order>>&
    getOrderList() const;

    //-------------------------
    // Sort
    //-------------------------

    template<typename Comparator>
    void sortOrders(Comparator comp)
    {
        std::sort(
            orderList.begin(),
            orderList.end(),
            comp
        );
    }
};