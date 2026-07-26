#include "../include/order.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

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
      status(OrderStatus::Pending)
{
    if(id.empty())
        throw invalid_argument("Order ID cannot be empty.");

    if(!item)
        throw invalid_argument("Furniture item cannot be null.");

    setCarpenterName(name);
    setStartDate(date);
    setEstimatedTime(time);
}

//=========================
// Helper Functions
//=========================

string Order::statusToString(OrderStatus status)
{
    switch (status)
    {
    case OrderStatus::Pending:
        return "Pending";

    case OrderStatus::InProgress:
        return "InProgress";

    case OrderStatus::Completed:
        return "Completed";

    default:
        return "Pending";
    }
}

OrderStatus Order::stringToStatus(
    const string& statusString)
{
    string value = statusString;

    transform(value.begin(),
              value.end(),
              value.begin(),
              [](unsigned char c)
              {
                  return tolower(c);
              });

    if (value == "pending")
        return OrderStatus::Pending;

    if (value == "inprogress")
        return OrderStatus::InProgress;

    if (value == "completed")
        return OrderStatus::Completed;

    throw invalid_argument("Invalid order status.");
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

OrderStatus Order::getStatus() const
{
    return status;
}

//=========================
// Setter
//=========================

void Order::setCarpenterName(const string& name)
{
    if (name.empty())
        throw invalid_argument(
            "Carpenter name cannot be empty.");

    carpenterName = name;
}

void Order::setEstimatedTime(int time)
{
    if (time <= 0)
        throw invalid_argument(
            "Estimated time must be greater than 0.");

    estimatedTime = time;
}

void Order::setStartDate(const string& date)
{
    if (date.empty())
        throw invalid_argument(
            "Date cannot be empty.");

    startDate = date;
}

void Order::setFurnitureItem(shared_ptr<Furniture> item)
{
    if (!item)
        throw invalid_argument(
            "Furniture cannot be null.");

    furnitureItem = item;
}

void Order::setStatus(OrderStatus status)
{
    this->status = status;
}

//=========================
// Business Logic
//=========================

double Order::calculatePricing() const
{
    if (!furnitureItem)
        return 0.0;

    const double LABOR_RATE = 200.0;

    return furnitureItem->calculatePricing()
         + estimatedTime * LABOR_RATE;
}