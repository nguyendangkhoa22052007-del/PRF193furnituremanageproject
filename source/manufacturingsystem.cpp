#include "manufacturingsystem.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

//====================================================
// ADD FURNITURE
//====================================================

void ManufacturingSystem::addFurniture(shared_ptr<Furniture> item)
{
    if (!item)
    {
        throw invalid_argument("Furniture cannot be null.");
    }

    if (searchFurnitureByID(item->getID()) != nullptr)
    {
        throw invalid_argument("Furniture ID already exists.");
    }

    furnitureList.push_back(item);

    // Đồng bộ lại STL Map
    classifyFurnitureByMaterial();
}

//====================================================
// ADD ORDER
//====================================================

void ManufacturingSystem::addOrder(unique_ptr<Order> order)
{
    if (!order)
    {
        throw invalid_argument("Order cannot be null.");
    }

    if (searchOrderByID(order->getOrderID()) != nullptr)
    {
        throw invalid_argument("Order ID already exists.");
    }

    orderList.push_back(move(order));
}

//====================================================
// DELETE FURNITURE
//====================================================

bool ManufacturingSystem::deleteFurniture(const string& id)
{
    for (const auto& order : orderList)
    {
        if (order->getFurnitureItem()->getID() == id)
        {
            return false;
        }
    }
    auto it = remove_if(
        furnitureList.begin(),
        furnitureList.end(),
        [&](const shared_ptr<Furniture>& item)
        {
            return item->getID() == id;
        });

    if (it == furnitureList.end())
    {
        return false;
    }

    furnitureList.erase(it, furnitureList.end());

    classifyFurnitureByMaterial();

    return true;
}

//====================================================
// DELETE ORDER
//====================================================

bool ManufacturingSystem::deleteOrder(const string& id)
{
    auto it = remove_if(
        orderList.begin(),
        orderList.end(),
        [&](const unique_ptr<Order>& order)
        {
            return order->getOrderID() == id;
        });

    if (it == orderList.end())
    {
        return false;
    }

    orderList.erase(it, orderList.end());

    return true;
}

//====================================================
// SEARCH FURNITURE BY ID
//====================================================

shared_ptr<Furniture>
ManufacturingSystem::searchFurnitureByID(const string& id) const
{
    for (const auto& item : furnitureList)
    {
        if (item->getID() == id)
        {
            return item;
        }
    }

    return nullptr;
}

//====================================================
// SEARCH ORDER BY ID
//====================================================

Order* ManufacturingSystem::searchOrderByID(
    const string& id) const
{
    for (const auto& order : orderList)
    {
        if (order->getOrderID() == id)
        {
            return order.get();
        }
    }

    return nullptr;
}

//====================================================
// SEARCH FURNITURE BY MATERIAL
//====================================================

vector<shared_ptr<Furniture>>
ManufacturingSystem::searchFurnitureByMaterial(
    MaterialType material) const
{
    auto it = furnitureByMaterial.find(material);

    if (it != furnitureByMaterial.end())
    {
        return it->second;
    }

    return {};
}
//====================================================
// UPDATE FURNITURE
//====================================================

bool ManufacturingSystem::updateFurnitureDetails(
    const string& id,
    MaterialType material,
    double length,
    double width,
    double height,
    const string& color)
{
    auto item = searchFurnitureByID(id);

    if (!item)
    {
        return false;
    }

    item->setMaterialType(material);
    item->setDimension(length, width, height);
    item->setColor(color);

    classifyFurnitureByMaterial();

    return true;
}

//====================================================
// DISPLAY FURNITURE
//====================================================

void ManufacturingSystem::displayFurniture() const
{
    if (furnitureList.empty())
    {
        cout << "No furniture found." << endl;
        return;
    }

    cout << "================ Furniture List ================" << endl;

    for (const auto& item : furnitureList)
    {
        cout << "ID: " << item->getID() << endl;

        cout << "Material: ";

        cout << Furniture::materialToString(item->getMaterialType()) << endl;

        cout << "Dimension: "
             << item->getLength()
             << " x "
             << item->getWidth()
             << " x "
             << item->getHeight()
             << endl;

        cout << "Color: "
             << item->getColor()
             << endl;

        cout << "Material Cost: "
             << item->calculateMaterialCost()
             << endl;

        cout << "----------------------------------------"
             << endl;
    }
}

//====================================================
// DISPLAY ORDERS
//====================================================

void ManufacturingSystem::displayOrders() const
{
    if (orderList.empty())
    {
        cout << "No orders found." << endl;
        return;
    }

    cout << "================ Order List ================" << endl;

    for (const auto& order : orderList)
    {
        cout << "Order ID: "
             << order->getOrderID()
             << endl;

        cout << "Carpenter: "
             << order->getCarpenterName()
             << endl;

        auto furniture = order->getFurnitureItem();

        cout << "Furniture ID: ";

        if (furniture)
        {
            cout << furniture->getID();
        }
        else
        {
            cout << "N/A";
        }

        cout << endl;

        cout << "Start Date: "
             << order->getStartDate()
             << endl;

        cout << "Estimated Time: "
             << order->getEstimatedTime()
             << " days"
             << endl;

        cout << "Total Price: "
             << order->calculatePricing()
             << endl;

        cout << "----------------------------------------"
             << endl;
    }
}
//====================================================
// CLASSIFY FURNITURE BY MATERIAL
//====================================================

void ManufacturingSystem::classifyFurnitureByMaterial()
{
    furnitureByMaterial.clear();

    for (const auto& item : furnitureList)
    {
        furnitureByMaterial[item->getMaterialType()].push_back(item);
    }
}

//====================================================
// GET FURNITURE MAP
//====================================================

const map<
    MaterialType,
    vector<shared_ptr<Furniture>>
>& ManufacturingSystem::getFurnitureMap() const
{
    return furnitureByMaterial;
}

//====================================================
// GET FURNITURE LIST
//====================================================

const vector<shared_ptr<Furniture>>&
ManufacturingSystem::getFurnitureList() const
{
    return furnitureList;
}

//====================================================
// GET ORDER LIST
//====================================================

const vector<unique_ptr<Order>>&
ManufacturingSystem::getOrderList() const
{
    return orderList;
}