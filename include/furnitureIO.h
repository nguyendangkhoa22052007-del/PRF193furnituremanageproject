#pragma once

#include <string>

class ManufacturingSystem;

// Save all furniture and orders to files
void saveToFile(
    const std::string& furnitureFile,
    const std::string& orderFile,
    const ManufacturingSystem& system
);

// Load all furniture and orders from files
void loadFromFile(
    const std::string& furnitureFile,
    const std::string& orderFile,
    ManufacturingSystem& system
);