// furnitureIO.h
#pragma once
#include <string>
#include "manufacturingsystem.h"

void saveToFile(const std::string& furnitureFile, 
    const std::string& orderFile, 
    const ManufacturingSystem& system);
void loadFromFile(const std::string& furnitureFile, 
    const std::string& orderFile, 
    ManufacturingSystem& system);