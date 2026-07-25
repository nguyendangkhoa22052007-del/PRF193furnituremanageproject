#include <iostream>
#include <memory>
#include <string>
#include "../include/manufacturingsystem.h"
#include "../include/furniture.h"
#include "../include/order.h"
#include "../include/menu.h"
using namespace std;

void showMainMenu() {
    cout << "\n========== FURNITURE MANAGEMENT SYSTEM ==========\n";
    cout << "1. Furniture Management\n";
    cout << "2. Order Management\n";
    cout << "3. Search & Analysis\n";
    cout << "4. Save Data\n";
    cout << "5. Load Data\n";
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

    try
    {
        cout << "ID: ";
        cin >> id;

        cout << "Material (Wood/Metal/Plastic): ";
        cin >> materialString;

        MaterialType material =
            Furniture::stringToMaterial(materialString);

        cout << "Length: ";
        cin >> length;

        cout << "Width: ";
        cin >> width;

        cout << "Height: ";
        cin >> height;

        cout << "Color: ";
        getline(cin >> ws, color);

        auto item =
            make_shared<Furniture>(
                id,
                material,
                length,
                width,
                height,
                color
            );

        system.addFurniture(item);

        cout << "Added successfully!\n";
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
        cout << "Not found!\n";
        return;
    }

    cout << "\nFurniture Information\n";

    cout << "ID: "
         << item->getID()
         << endl;

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

            cout << "-------------------------"
                 << endl;
        }
    }
    catch(const exception& e)
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

        cout << "New Material (Wood/Metal/Plastic): ";
        cin >> materialString;

        MaterialType material =
            Furniture::stringToMaterial(materialString);

        cout << "New Length: ";
        cin >> length;

        cout << "New Width: ";
        cin >> width;

        cout << "New Height: ";
        cin >> height;

        cout << "New Color: ";
        getline(cin >> ws, color);

        if(system.updateFurnitureDetails(
                id,
                material,
                length,
                width,
                height,
                color))
        {
            cout << "Updated successfully!\n";
        }
        else
        {
            cout << "Furniture not found!\n";
        }
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

        cout << "--------------------------------"
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
    cout << "2. Display All Orders\n";
    cout << "3. Sort Orders By Time\n";
    cout << "4. Delete Order\n";
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
        cin >> estimatedTime;

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
        }
        else
        {
            cout << "N/A";
        }
        cout << "\nStart Date: "
             << order->getStartDate();

        cout << "\nEstimated Time: "
             << order->getEstimatedTime();

        cout << "\nPricing: "
             << order->calculatePricing();

        cout << "\n------------------\n";
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

int main() {
    ManufacturingSystem system;

    int choice;

    do {
        showMainMenu();
        cin >> choice;

        switch(choice) {
             case 1:
            {
                int subChoice;

                do {
                    furnitureMenu();
                    cin >> subChoice;

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
                    cin >> subChoice;

                    switch(subChoice)
                        {
                         case 1:
                            addOrderUI(system);
                            break;

                        case 2:
                            displayOrdersUI(system);
                            break;

                        case 3:
                            sortOrdersByTimeUI(system);
                            break;
                        case 4:
                            deleteOrderUI(system);
                            break;
                        }

                } while(subChoice != 0);

                break;
}

            case 3:
                cout << "Search & Analysis\n";
                break;

            case 4:
                cout << "Save Data\n";
                break;

            case 5:
                cout << "Load Data\n";
                break;

            case 0:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 0);

    return 0;
}