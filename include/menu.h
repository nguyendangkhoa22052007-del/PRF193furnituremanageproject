#ifndef MENU_H
#define MENU_H

#include "../include/manufacturingsystem.h"

class Menu {
private:
    ManufacturingSystem system;

public:
    void run();

    void addFurnitureMenu();
    void searchByIDMenu();
    void searchByMaterialMenu();
    void updateFurnitureMenu();
    void displayFurnitureMenu();
};

#endif