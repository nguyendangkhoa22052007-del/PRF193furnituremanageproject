#include "../include/customfurniture.h"

#include <stdexcept>

using namespace std;

// =====================
// Constructor
// =====================
CustomFurniture::CustomFurniture(
    const string& id,
    MaterialType material,
    double length,
    double width,
    double height,
    const string& color,
    double customizationFee
)
    : Furniture(
        id,
        material,
        length,
        width,
        height,
        color
    )
{
    setCustomizationFee(customizationFee);
}

// =====================
// Getter
// =====================
double CustomFurniture::getCustomizationFee() const
{
    return customizationFee;
}

// =====================
// Setter
// =====================
void CustomFurniture::setCustomizationFee(double fee)
{
    if (fee < 0)
    {
        throw invalid_argument(
            "Customization fee cannot be negative."
        );
    }

    customizationFee = fee;
}

// =====================
// Pricing
// =====================
double CustomFurniture::calculatePricing() const
{
    const double BASIC_LABOR_COST = 500.0;

    return calculateMaterialCost()
         + BASIC_LABOR_COST
         + customizationFee;
}