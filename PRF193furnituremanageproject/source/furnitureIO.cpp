<<<<<<< HEAD:PRF193furnituremanageproject/source/furnitureIO.cpp
#include "furnitureIO.h"
=======
#include "../include/furnitureIO.h"
>>>>>>> 565b61cde44112e68632224c427b12330bbc9786:source/furnitureIO.cpp
#include <fstream>
#include <iostream>

using namespace std;

// ====================================================
// HÀM LƯU FILE 
// ====================================================
void saveToFile(const string& furnitureFile, const string& orderFile, const ManufacturingSystem& system) {
    ofstream fOut(furnitureFile);
    if (!fOut.is_open()) {
<<<<<<< HEAD:PRF193furnituremanageproject/source/furnitureIO.cpp
        cout << "Loi: Khong the mo file de ghi Furniture!" << endl;
=======
        cout << "Error: Could not open file to write Furniture!" << endl;
>>>>>>> 565b61cde44112e68632224c427b12330bbc9786:source/furnitureIO.cpp
        return;
    }

    for (int i = 0; i < system.getFurnitureList().size(); i++) {
        const auto& item = system.getFurnitureList()[i];
        fOut << item->getID() << ","
             << Furniture::materialToString(item->getMaterialType()) << ","
             << item->getLength() << ","
             << item->getWidth() << ","
             << item->getHeight() << ","
             << item->getColor() << "\n";
    }
    fOut.close();

    ofstream oOut(orderFile);
    if (!oOut.is_open()) {
<<<<<<< HEAD:PRF193furnituremanageproject/source/furnitureIO.cpp
        cout << "Loi: Khong the mo file de ghi Order!" << endl;
=======
        cout << "Error: Could not open file to write Order!" << endl;
>>>>>>> 565b61cde44112e68632224c427b12330bbc9786:source/furnitureIO.cpp
        return;
    }

    for (int i = 0; i < system.getOrderList().size(); i++) {
        auto* order = system.getOrderList()[i].get();
        
        string fID = "N/A";
        if (order->getFurnitureItem() != nullptr) {
            fID = order->getFurnitureItem()->getID();
        }

        oOut << order->getOrderID() << ","
             << order->getCarpenterName() << ","
             << fID << ","
             << order->getStartDate() << ","
             << order->getEstimatedTime() << "\n";
    }
    oOut.close();

<<<<<<< HEAD:PRF193furnituremanageproject/source/furnitureIO.cpp
    cout << "Da luu toan bo du lieu he thong vao file thanh cong!" << endl;
=======
    cout << "System data saved successfully!" << endl;
>>>>>>> 565b61cde44112e68632224c427b12330bbc9786:source/furnitureIO.cpp
}

// ====================================================
// HÀM ĐỌC FILE 
// ====================================================

void loadFromFile(const string& furnitureFile, const string& orderFile, ManufacturingSystem& system) {
    ifstream fIn(furnitureFile);
    if (fIn.is_open()) {
        string line;
        string parts[6];
        while (getline(fIn, line)) {
            if (line.empty()) continue; 

            string temp = "";
            int count = 0;
            int len = line.length();

            for (int i = 0; i < len; i++) {
                if (line[i] == ',') {
                    parts[count++] = temp;
                    temp = "";
                } else {
                    temp += line[i];
                }
            }
            parts[count] = temp; 

            string id = parts[0];
            MaterialType mat = Furniture::stringToMaterial(parts[1]);
            double length = stod(parts[2]);
            double width = stod(parts[3]);
            double height = stod(parts[4]);
            string color = parts[5];

            auto item = make_shared<Furniture>(id, mat, length, width, height, color);
            system.addFurniture(item);
        }
        fIn.close();
    }

    ifstream oIn(orderFile);
    if (oIn.is_open()) {
        string line;
        string parts[5];
        
        while (getline(oIn, line)) {
            if (line.empty()) continue;

            string temp = "";
            int count = 0;
            int len = line.length();

            for (int i = 0; i < len; i++) {
                if (line[i] == ',') {
                    parts[count++] = temp;
                    temp = "";
                } else {
                    temp += line[i];
                }
            }
            parts[count] = temp;

            string oID = parts[0];
            string carpenter = parts[1];
            string fID = parts[2];
            string startDate = parts[3];
            int estTime = stoi(parts[4]);

            
            auto furnitureItem = system.searchFurnitureByID(fID);
            if (furnitureItem != nullptr) {
                
                auto order = make_unique<Order>(oID, carpenter, furnitureItem, startDate, estTime);
                system.addOrder(move(order));
            }
        }
        oIn.close();
    }

<<<<<<< HEAD:PRF193furnituremanageproject/source/furnitureIO.cpp
    cout << "Da tai du lieu tu file vao he thong thanh cong!" << endl;
=======
    cout << "Data loaded from files into the system successfully!" << endl;
>>>>>>> 565b61cde44112e68632224c427b12330bbc9786:source/furnitureIO.cpp
}