#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include "../include/manufacturingsystem.h"
#include "../include/furniture.h"
#include "../include/order.h"
#include "../include/menu.h"
#include "../include/furnitureIO.h"
#include "../include/standardfurniture.h"
#include "../include/customfurniture.h"
using namespace std;

const string FURNITURE_FILE = "furniture.txt";
const string ORDER_FILE = "orders.txt";
int inputInt()
{
    int value;

    while (!(cin >> value))
    {
        cout << "Invalid input! Please enter a number: ";

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }

    return value;
}
double inputDouble()
{
    double value;

    while (!(cin >> value))
    {
        cout << "Invalid input! Please enter a number: ";

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }

    return value;
}
void showMainMenu() {
    cout << "\n========== FURNITURE MANAGEMENT SYSTEM ==========\n";
    cout << "1. Furniture Management\n";
    cout << "2. Order Management\n";
    cout << "3. Search & Analysis\n";
    cout << "0. Exit\n";
    cout << "Choose: ";
}

// FURNITURE MENU
void furnitureMenu() {
    cout << "\n----- Furniture Management -----\n";
    cout << "1. Add Furniture\n";
    cout << "2. Search Furniture by ID\n";
    cout << "3. Search Furniture by Material\n";
    cout << "4. Update Furniture\n";
    cout << "5. Display All Furniture\n";
    cout << "6. Delete Furniture\n";
    cout << "0. Back\n";
}

void addFurnitureUI(ManufacturingSystem& system)
{
    string id;
    string materialString;
    string color;

    double length;
    double width;
    double height;

    int type;

    try
    {
        cout << "Furniture Type\n";
        cout << "1. Standard Furniture\n";
        cout << "2. Custom Furniture\n";
        cout << "Choose: ";
        type = inputInt();

        cout << "ID: ";
        cin >> id;

        cout << "Material (Wood/Metal/Plastic): ";
        cin >> materialString;

        MaterialType material =
            Furniture::stringToMaterial(materialString);

        cout << "Length: ";
        length = inputDouble();

        cout << "Width: ";
        width = inputDouble();

        cout << "Height: ";
        height = inputDouble();

        cout << "Color: ";
        getline(cin >> ws, color);

        shared_ptr<Furniture> item;

        if(type == 1)
        {
            item =
                make_shared<StandardFurniture>(
                    id,
                    material,
                    length,
                    width,
                    height,
                    color
                );
        }
        else if(type == 2)
        {
            double fee;

            cout << "Customization Fee: ";
            fee = inputDouble();

            item =
                make_shared<CustomFurniture>(
                    id,
                    material,
                    length,
                    width,
                    height,
                    color,
                    fee
                );
        }
        else
        {
            cout << "Invalid furniture type!\n";
            return;
        }

        system.addFurniture(item);

        cout << "Furniture added successfully!\n";
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }
}
void searchFurnitureByIDUI(
    ManufacturingSystem& system)
{
    string id;

    cout << "Enter ID: ";
    cin >> id;

    auto item =
        system.searchFurnitureByID(id);

    if (!item)
    {
        cout << "Furniture not found!\n";
        return;
    }

    cout << "\n========== FURNITURE ==========\n";

    cout << "ID: "
         << item->getID()
         << endl;

    cout << "Type: ";

    if(dynamic_pointer_cast<CustomFurniture>(item))
    {
        cout << "Custom Furniture";
    }
    else
    {
        cout << "Standard Furniture";
    }

    cout << endl;

    cout << "Material: "
         << Furniture::materialToString(
                item->getMaterialType())
         << endl;

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

    cout << "Total Pricing: "
         << item->calculatePricing()
         << endl;

    if(auto custom =
        dynamic_pointer_cast<CustomFurniture>(item))
    {
        cout << "Customization Fee: "
             << custom->getCustomizationFee()
             << endl;
    }

    cout << "===============================\n";
}   
void searchFurnitureByMaterialUI(
    ManufacturingSystem& system)
{
    string materialString;

    cout << "Material (Wood/Metal/Plastic): ";
    cin >> materialString;

    try
    {
        MaterialType material =
            Furniture::stringToMaterial(materialString);

        auto result =
            system.searchFurnitureByMaterial(material);

        if (result.empty())
        {
            cout << "No furniture found!\n";
            return;
        }

        cout << "\n========== RESULT ==========\n";

        for (const auto& item : result)
        {
            cout << "ID: "
                 << item->getID()
                 << endl;

            cout << "Type: ";

            if (dynamic_pointer_cast<CustomFurniture>(item))
            {
                cout << "Custom Furniture";
            }
            else
            {
                cout << "Standard Furniture";
            }

            cout << endl;

            cout << "Material: "
                 << Furniture::materialToString(
                        item->getMaterialType())
                 << endl;

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

            cout << "Total Pricing: "
                 << item->calculatePricing()
                 << endl;

            if (auto custom =
                dynamic_pointer_cast<CustomFurniture>(item))
            {
                cout << "Customization Fee: "
                     << custom->getCustomizationFee()
                     << endl;
            }

            cout << "----------------------------------"
                 << endl;
        }
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
}

void updateFurnitureUI(
    ManufacturingSystem& system)
{
    string id;
    string materialString;
    string color;

    double length;
    double width;
    double height;

    try
    {
        cout << "Furniture ID: ";
        cin >> id;

        auto item =
            system.searchFurnitureByID(id);

        if (!item)
        {
            cout << "Furniture not found!\n";
            return;
        }

        cout << "New Material (Wood/Metal/Plastic): ";
        cin >> materialString;

        MaterialType material =
            Furniture::stringToMaterial(materialString);

        cout << "New Length: ";
        length = inputDouble();

        cout << "New Width: ";
        width = inputDouble();

        cout << "New Height: ";
        height = inputDouble();

        cout << "New Color: ";
        getline(cin >> ws, color);

        item->setMaterialType(material);
        item->setDimension(
            length,
            width,
            height);

        item->setColor(color);
        system.classifyFurnitureByMaterial();
        if(auto custom =
            dynamic_pointer_cast<CustomFurniture>(item))
        {
            double fee;

            cout << "New Customization Fee: ";
            fee = inputDouble();

            custom->setCustomizationFee(fee);
        }

        cout << "Furniture updated successfully!\n";
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }
}

void displayAllFurniture(
    ManufacturingSystem& system)
{
    const auto& list =
        system.getFurnitureList();

    if (list.empty())
    {
        cout << "No furniture available!\n";
        return;
    }

    cout << "\n========== FURNITURE LIST ==========\n";

    for (const auto& item : list)
    {
        cout << "ID: "
             << item->getID()
             << endl;

        cout << "Type: ";

        if (dynamic_pointer_cast<CustomFurniture>(item))
        {
            cout << "Custom Furniture";
        }
        else
        {
            cout << "Standard Furniture";
        }

        cout << endl;

        cout << "Material: "
             << Furniture::materialToString(
                    item->getMaterialType())
             << endl;

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

        cout << "Total Pricing: "
             << item->calculatePricing()
             << endl;

        if (auto custom =
            dynamic_pointer_cast<CustomFurniture>(item))
        {
            cout << "Customization Fee: "
                 << custom->getCustomizationFee()
                 << endl;
        }

        cout << "----------------------------------------"
             << endl;
    }
}
void deleteFurnitureUI(
    ManufacturingSystem& system)
{
    string id;

    cout << "Furniture ID: ";
    cin >> id;

    if(system.deleteFurniture(id))
    {
        cout << "Deleted successfully!\n";
    }
    else
    {
        cout << "Furniture not found or is being used by an order!\n";
    }
}

// ORDER MANAGEMENT
void orderMenu()
{
    cout << "\n----- Order Management -----\n";
    cout << "1. Add Order\n";
    cout << "2. Search Order by ID\n";
    cout << "3. Search Order by Carpenter\n";
    cout << "4. Search Order by Status\n";
    cout << "5. Update Order Status\n";
    cout << "6. Display All Orders\n";
    cout << "7. Sort Orders By Time\n";
    cout << "8. Delete Order\n";
    cout << "0. Back\n";
    cout << "Choose: ";
}
void addOrderUI(ManufacturingSystem& system)
{
    string orderID;
    string carpenter;
    string furnitureID;
    string startDate;
    int estimatedTime;

    try
    {
        cout << "Order ID: ";
        cin >> orderID;

        cout << "Furniture ID: ";
        cin >> furnitureID;

        auto furniture =
            system.searchFurnitureByID(furnitureID);

        if (!furniture)
        {
            cout << "Furniture not found!\n";
            return;
        }

        cout << "Carpenter Name: ";
        getline(cin >> ws, carpenter);

        cout << "Start Date: ";
        cin >> startDate;

        cout << "Estimated Time: ";
        estimatedTime = inputInt();

        auto order =
            make_unique<Order>(
                orderID,
                carpenter,
                furniture,
                startDate,
                estimatedTime
            );

        system.addOrder(move(order));

        cout << "Order added successfully!\n";
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }
}

void displayOrdersUI(ManufacturingSystem& system)
{
    const auto& orders =
        system.getOrderList();

    if (orders.empty())
    {
        cout << "No orders available!\n";
        return;
    }

    for (const auto& order : orders)
    {
        cout << "\nOrder ID: "
             << order->getOrderID();

        cout << "\nCarpenter: "
             << order->getCarpenterName();

        auto furniture = order->getFurnitureItem();

        cout << "\nFurniture ID: ";

        if (furniture)
        {
            cout << furniture->getID();

            if(dynamic_pointer_cast<CustomFurniture>(furniture))
            {
                cout << "\nFurniture Type: Custom";
            }
            else
            {
                cout << "\nFurniture Type: Standard";
            }
        }
        else
        {
            cout << "N/A";
        }
        cout << "\nStart Date: "
             << order->getStartDate();

        cout << "\nEstimated Time: "
             << order->getEstimatedTime();
        cout << "\nStatus: "
             << Order::statusToString(
                    order->getStatus());
        cout << "\nPricing: "
             << order->calculatePricing();
        
        cout << "\n------------------\n";
    }
}
void searchOrderByIDUI(
    ManufacturingSystem& system)
{
    string id;

    cout << "Order ID: ";
    cin >> id;

    Order* order =
        system.searchOrderByID(id);

    if (!order)
    {
        cout << "Order not found!\n";
        return;
    }

    cout << "\n========== ORDER ==========\n";

    cout << "Order ID: "
         << order->getOrderID()
         << endl;

    cout << "Carpenter: "
         << order->getCarpenterName()
         << endl;

    auto furniture =
        order->getFurnitureItem();

    cout << "Furniture ID: ";

    if(furniture)
    {
        cout << furniture->getID();

        if(dynamic_pointer_cast<CustomFurniture>(furniture))
        {
            cout << "\nFurniture Type: Custom";
        }
        else
        {
            cout << "\nFurniture Type: Standard";
        }
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
         << endl;

    cout << "Status: "
         << Order::statusToString(
                order->getStatus())
         << endl;

    cout << "Pricing: "
         << order->calculatePricing()
         << endl;
}
void searchOrderByCarpenterUI(
    ManufacturingSystem& system)
{
    string carpenter;

    cout << "Carpenter name: ";
    getline(cin >> ws, carpenter);

    auto result =
        system.searchOrderByCarpenter(carpenter);

    if(result.empty())
    {
        cout << "No orders found!\n";
        return;
    }

    cout << "\n========== RESULT ==========\n";

    for(Order* order : result)
    {
        cout << "Order ID: "
             << order->getOrderID()
             << endl;

        cout << "Furniture ID: ";

        if(order->getFurnitureItem())
            cout << order->getFurnitureItem()->getID();
        else
            cout << "N/A";

        cout << endl;

        cout << "Status: "
             << Order::statusToString(
                    order->getStatus())
             << endl;

        cout << "Estimated Time: "
             << order->getEstimatedTime()
             << endl;

        cout << "Pricing: "
             << order->calculatePricing()
             << endl;

        cout << "----------------------\n";
    }
}
void searchOrderByStatusUI(
    ManufacturingSystem& system)
{
    int choice;

    cout << "Status\n";
    cout << "1. Pending\n";
    cout << "2. In Progress\n";
    cout << "3. Completed\n";
    cout << "Choose: ";

    choice = inputInt();

    OrderStatus status;

    switch(choice)
    {
        case 1:
            status = OrderStatus::Pending;
            break;

        case 2:
            status = OrderStatus::InProgress;
            break;

        case 3:
            status = OrderStatus::Completed;
            break;

        default:
            cout << "Invalid choice!\n";
            return;
    }

    auto result =
        system.searchOrderByStatus(status);

    if(result.empty())
    {
        cout << "No orders found!\n";
        return;
    }

    cout << "\n========== RESULT ==========\n";

    for(Order* order : result)
    {
        cout << "Order ID: "
             << order->getOrderID()
             << endl;

        cout << "Carpenter: "
             << order->getCarpenterName()
             << endl;

        cout << "Pricing: "
             << order->calculatePricing()
             << endl;

        cout << "----------------------\n";
    }
}
void updateOrderStatusUI(
    ManufacturingSystem& system)
{
    string id;

    int choice;

    cout << "Order ID: ";
    cin >> id;

    cout << "New Status\n";
    cout << "1. Pending\n";
    cout << "2. In Progress\n";
    cout << "3. Completed\n";
    cout << "Choose: ";

    choice = inputInt();

    OrderStatus status;

    switch(choice)
    {
        case 1:
            status = OrderStatus::Pending;
            break;

        case 2:
            status = OrderStatus::InProgress;
            break;

        case 3:
            status = OrderStatus::Completed;
            break;

        default:
            cout << "Invalid choice!\n";
            return;
    }

    if(system.updateOrderStatus(id, status))
    {
        cout << "Order status updated successfully!\n";
    }
    else
    {
        cout << "Order not found!\n";
    }
}
void deleteOrderUI(
    ManufacturingSystem& system)
{
    string id;

    cout << "Order ID: ";
    cin >> id;

    if(system.deleteOrder(id))
    {
        cout << "Deleted successfully!\n";
    }
    else
    {
        cout << "Order not found!\n";
    }
}

void sortOrdersByTimeUI(
    ManufacturingSystem& system)
{
    system.sortOrders(
        [](const unique_ptr<Order>& a,
           const unique_ptr<Order>& b)
        {
            return a->getEstimatedTime()
                 < b->getEstimatedTime();
        });

    cout << "Orders sorted by estimated time!\n";
}

void searchAnalysisMenu() {
    cout << "\n----- Search & Analysis -----\n";
    cout << "1. Search Furniture by ID\n";
    cout << "2. Search Furniture by Material\n";
    cout << "3. Classify & Display Furniture Map (by Material)\n";
    cout << "4. Display Total Revenue\n";
    cout << "0. Back\n";
    cout << "Choose: ";
}

void searchAndAnalysisUI(ManufacturingSystem& system) {
    int choice;
    do {
        searchAnalysisMenu();
        choice = inputInt();
        switch (choice) {
            case 1:
                searchFurnitureByIDUI(system);
                break;
            case 2:
                searchFurnitureByMaterialUI(system);
                break;
            case 3: {
                system.classifyFurnitureByMaterial();
                const auto& mapRef = system.getFurnitureMap();
                if (mapRef.empty()) {
                    cout << "No furniture data to analyze!\n";
                    break;
                }
                cout << "\n========== ANALYSIS BY MATERIAL ==========\n";
                for (const auto& pair : mapRef) {
                    cout << "Material: " << Furniture::materialToString(pair.first) 
                         << " (Total items: " << pair.second.size() << ")\n";
                    for (const auto& item : pair.second) {
                        cout << "  - ID: " << item->getID()
                            << " | Color: " << item->getColor()
                            << " | Price: "
                            << item->calculatePricing()
                            << "\n";
                    }
                }
                break;
            }
            case 4:
            {
                cout << "\n========== TOTAL REVENUE ==========\n";

                cout << "Total Revenue: "
                    << system.calculateRevenue()
                    << endl;

                break;
            }
            case 0:
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

int main() {
    ManufacturingSystem system;
    // Automatically load data
    loadFromFile(
        FURNITURE_FILE,
        ORDER_FILE,
        system
    );
    int choice;

    do {
        showMainMenu();
        choice = inputInt();

        switch(choice) {
             case 1:
            {
                int subChoice;

                do {
                    furnitureMenu();
                    subChoice = inputInt();

                    switch(subChoice) {

                    case 1:
                        addFurnitureUI(system);
                        break;

                    case 2:
                        searchFurnitureByIDUI(system);
                        break;

                    case 3:
                        searchFurnitureByMaterialUI(system);
                        break;

                    case 4:
                        updateFurnitureUI(system);
                        break;

                    case 5:
                        displayAllFurniture(system);
                        break;

                    case 6:
                        deleteFurnitureUI(system);
                        break;
                    }
                } while(subChoice != 0);

                break;
            }

            case 2:
            {
                int subChoice;

                do
                {
                    orderMenu();
                    subChoice = inputInt();

                    switch(subChoice)
                    {
                    case 1:
                        addOrderUI(system);
                        break;

                    case 2:
                        searchOrderByIDUI(system);
                        break;

                    case 3:
                        searchOrderByCarpenterUI(system);
                        break;

                    case 4:
                        searchOrderByStatusUI(system);
                        break;

                    case 5:
                        updateOrderStatusUI(system);
                        break;

                    case 6:
                        displayOrdersUI(system);
                        break;

                    case 7:
                        sortOrdersByTimeUI(system);
                        break;

                    case 8:
                        deleteOrderUI(system);
                        break;
                    }

                } while(subChoice != 0);

                break;
            }

            case 3:
                searchAndAnalysisUI(system);
                break;

            case 0:

            saveToFile(
                FURNITURE_FILE,
                ORDER_FILE,
                system
            );

            cout << "Data saved successfully.\n";
            cout << "Exiting program. Goodbye!\n";
            break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while(choice != 0);

    return 0;
}