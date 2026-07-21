#include "order.h"
#include <stdexcept>

using namespace std;

//=========================
// Constructor
//=========================
Order::Order(const string& id,
             const string& name,
             shared_ptr<Furniture> item,
             const string& date,
             int time)
    : orderID(id),
      furnitureItem(item),
      startDate(date)
{
    if (id.empty())
        throw invalid_argument("Order ID cannot be empty.");

    if (item == nullptr)
        throw invalid_argument("Furniture item cannot be null.");

    setCarpenterName(name);
    setEstimatedTime(time);
}

//=========================
// Getter
//=========================
string Order::getOrderID() const
{
    return orderID;
}

string Order::getCarpenterName() const
{
    return carpenterName;
}

shared_ptr<Furniture> Order::getFurnitureItem() const
{
    return furnitureItem;
}

string Order::getStartDate() const
{
    return startDate;
}

int Order::getEstimatedTime() const
{
    return estimatedTime;
}

//=========================
// Setter
//=========================
void Order::setCarpenterName(const string& name)
{
    if (name.empty())
        throw invalid_argument("Carpenter name cannot be empty.");

    carpenterName = name;
}

void Order::setEstimatedTime(int time)
{
    if (time <= 0)
        throw invalid_argument("Estimated time must be greater than 0.");

    estimatedTime = time;
}
void Order::setStartDate(
    const string& date)
{
    if (date.empty())
        throw invalid_argument(
            "Date cannot be empty.");

    startDate = date;
}
void Order::setFurnitureItem(
    shared_ptr<Furniture> item)
{
    if (!item)
        throw invalid_argument(
            "Furniture cannot be null.");

    furnitureItem = item;
}
//=========================
// Business Logic
//=========================
double Order::calculatePricing() const
{
    if (!furnitureItem)
        return 0.0;

    return furnitureItem->calculateMaterialCost()
           + estimatedTime * 200.0;
}