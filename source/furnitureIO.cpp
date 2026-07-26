#include "../include/furnitureIO.h"
#include "../include/standardfurniture.h"
#include "../include/customfurniture.h"
#include "../include/order.h"
#include "../include/manufacturingsystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
using namespace std;

//====================================================
// SAVE DATA
//====================================================

void saveToFile(const string& furnitureFile,
                const string& orderFile,
                const ManufacturingSystem& system)
{
    ofstream fOut(furnitureFile);

    if (!fOut.is_open())
    {
        cout << "Cannot open furniture file.\n";
        return;
    }

    for (const auto& item : system.getFurnitureList())
    {
        if (auto custom =
            dynamic_pointer_cast<CustomFurniture>(item))
        {
            fOut
                << "Custom,"
                << custom->getID() << ","
                << Furniture::materialToString(
                       custom->getMaterialType())
                << ","
                << custom->getLength() << ","
                << custom->getWidth() << ","
                << custom->getHeight() << ","
                << custom->getColor() << ","
                << custom->getCustomizationFee()
                << "\n";
        }
        else
        {
            fOut
                << "Standard,"
                << item->getID() << ","
                << Furniture::materialToString(
                       item->getMaterialType())
                << ","
                << item->getLength() << ","
                << item->getWidth() << ","
                << item->getHeight() << ","
                << item->getColor()
                << "\n";
        }
    }

    fOut.close();

    ofstream oOut(orderFile);

    if (!oOut.is_open())
    {
        cout << "Cannot open order file.\n";
        return;
    }

    for (const auto& order : system.getOrderList())
    {
        string furnitureID = "";

        if (order->getFurnitureItem())
        {
            furnitureID =
                order->getFurnitureItem()->getID();
        }

        oOut
            << order->getOrderID() << ","
            << order->getCarpenterName() << ","
            << furnitureID << ","
            << order->getStartDate() << ","
            << order->getEstimatedTime()
            << "\n";
    }

    oOut.close();

    cout << "Save completed successfully.\n";
}
//====================================================
// LOAD DATA
//====================================================

void loadFromFile(const string& furnitureFile,
                  const string& orderFile,
                  ManufacturingSystem& system)
{
    ifstream fIn(furnitureFile);

    if (fIn.is_open())
    {
        string line;

        while (getline(fIn, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            vector<string> parts;
            string token;

            while (getline(ss, token, ','))
            {
                parts.push_back(token);
            }

            if (parts.size() < 7)
                continue;

            string type = parts[0];

            string id = parts[1];

            MaterialType material =
                Furniture::stringToMaterial(parts[2]);

            double length = stod(parts[3]);
            double width = stod(parts[4]);
            double height = stod(parts[5]);

            string color = parts[6];

            shared_ptr<Furniture> item;

            if (type == "Standard")
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
            else if (type == "Custom")
            {
                if (parts.size() < 8)
                    continue;

                double fee = stod(parts[7]);

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
                continue;
            }

            system.addFurniture(item);
        }

        fIn.close();
    }

    ifstream oIn(orderFile);

    if (oIn.is_open())
    {
        string line;

        while (getline(oIn, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            vector<string> parts;
            string token;

            while (getline(ss, token, ','))
            {
                parts.push_back(token);
            }

            if (parts.size() != 5)
                continue;

            string orderID = parts[0];
            string carpenter = parts[1];
            string furnitureID = parts[2];
            string startDate = parts[3];
            int estimatedTime = stoi(parts[4]);

            auto furniture =
                system.searchFurnitureByID(furnitureID);

            if (!furniture)
                continue;

            auto order =
                make_unique<Order>(
                    orderID,
                    carpenter,
                    furniture,
                    startDate,
                    estimatedTime
                );

            system.addOrder(move(order));
        }

        oIn.close();
    }

    cout << "Data loaded successfully.\n";
}