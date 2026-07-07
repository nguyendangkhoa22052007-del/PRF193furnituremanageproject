#include "manufacturingsystem.h"
#include <stdexcept>

using namespace std;

// 1. ADDING NEW FURNITURE FUNCTIONS
void ManufacturingSystem::addFurniture(shared_ptr<Furniture> item) {
    if (item == nullptr) return;

    if (searchFurnitureByID(item->getID()) != nullptr) {
        throw invalid_argument("Ma ID noi that nay da ton tai trong he thong!");
    }

    furnitureList.push_back(item);

    furnitureByMaterial[item->getMaterialType()].push_back(item);
}

void ManufacturingSystem::addOrder(unique_ptr<Order> order) {
    if (order == nullptr) return;

    for (const auto& o : orderList) {
        if (o->getOrderID() == order->getOrderID()) {
            throw invalid_argument("Ma ID don hang nay da ton tai trong he thong!");
        }
    }
    orderList.push_back(move(order));
}


// 2.SEARCHING FUNCTIONS
shared_ptr<Furniture> ManufacturingSystem::searchFurnitureByID(const string& id) const {
    for (const auto& item : furnitureList) {
        if (item->getID() == id) {
            return item;
        }
    }
    return nullptr;
}

vector<shared_ptr<Furniture>> ManufacturingSystem::searchFurnitureByMaterial(const string& material) const {
    auto it = furnitureByMaterial.find(material);
    if (it != furnitureByMaterial.end()) {
        return it->second;
    }
    return vector<shared_ptr<Furniture>>();
}


// 3. UPDATE INFORMATION

bool ManufacturingSystem::updateFurnitureDetails(const string& id, const string& newMaterial, double newSize, const string& newColor) {
    shared_ptr<Furniture> item = searchFurnitureByID(id);
    
    if (item == nullptr) {
        return false;
    }

    item->setMaterialType(newMaterial);
    item->setSize(newSize);
    item->setColor(newColor);

    classifyFurnitureByMaterial();
    
    return true;
}

// 4. ĐỒNG BỘ HÓA STL MAP PHÂN LOẠI
void ManufacturingSystem::classifyFurnitureByMaterial() {
    furnitureByMaterial.clear();
    for (const auto& item : furnitureList) {
        furnitureByMaterial[item->getMaterialType()].push_back(item);
    }
}

const map<string, vector<shared_ptr<Furniture>>>& ManufacturingSystem::getFurnitureMap() const {
    return furnitureByMaterial;
}

// 5. GETTING LIST FUNCTIONS
const vector<shared_ptr<Furniture>>& ManufacturingSystem::getFurnitureList() const {
    return furnitureList;
}

const vector<unique_ptr<Order>>& ManufacturingSystem::getOrderList() const {
    return orderList;
}