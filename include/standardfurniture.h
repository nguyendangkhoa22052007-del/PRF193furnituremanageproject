#pragma once

#include "../include/furniture.h"

class StandardFurniture : public Furniture
{
public:

    StandardFurniture(
        const std::string& id,
        MaterialType material,
        double length,
        double width,
        double height,
        const std::string& color
    );

    double calculatePricing() const override;
};