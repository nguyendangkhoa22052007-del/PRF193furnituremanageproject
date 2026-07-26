#pragma once

#include "../include/furniture.h"

class CustomFurniture : public Furniture
{
private:
    double customizationFee;

public:

    CustomFurniture(
        const std::string& id,
        MaterialType material,
        double length,
        double width,
        double height,
        const std::string& color,
        double customizationFee
    );

    double getCustomizationFee() const;

    void setCustomizationFee(double fee);

    double calculatePricing() const override;
};