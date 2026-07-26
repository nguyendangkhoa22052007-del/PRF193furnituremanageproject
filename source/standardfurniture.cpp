#include "../include/standardfurniture.h"

using namespace std;

// =====================
// Constructor
// =====================
StandardFurniture::StandardFurniture(
    const string& id,
    MaterialType material,
    double length,
    double width,
    double height,
    const string& color
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
}

// =====================
// Pricing
// =====================
double StandardFurniture::calculatePricing() const
{
    // Standard furniture:
    // material cost + basic labor cost

    const double BASIC_LABOR_COST = 500.0;

    return calculateMaterialCost() + BASIC_LABOR_COST;
}