#include "furniture.h"
#include <stdexcept>

using namespace std;

// =====================
// Constructor
// =====================
Furniture::Furniture(const string& id,
                     MaterialType material,
                     double length,
                     double width,
                     double height,
                     const string& color)
{
    if (id.empty())
        throw invalid_argument("Furniture ID cannot be empty.");

    ID = id;

    setMaterialType(material);
    setDimension(length, width, height);
    setColor(color);
}
string Furniture::materialToString(MaterialType material)
{
    switch (material)
    {
    case MaterialType::Wood:
        return "Wood";

    case MaterialType::Metal:
        return "Metal";

    case MaterialType::Plastic:
        return "Plastic";

    default:
        return "Unknown";
    }
}

MaterialType Furniture::stringToMaterial(
    const string& material)
{
    if (material == "Wood")
        return MaterialType::Wood;

    if (material == "Metal")
        return MaterialType::Metal;

    if (material == "Plastic")
        return MaterialType::Plastic;

    throw invalid_argument("Invalid material type.");
}
// =====================
// Getter
// =====================
string Furniture::getID() const
{
    return ID;
}

MaterialType Furniture::getMaterialType() const
{
    return material;
}

double Furniture::getLength() const
{
    return length;
}

double Furniture::getWidth() const
{
    return width;
}

double Furniture::getHeight() const
{
    return height;
}

double Furniture::getArea() const
{
    return length * width;
}

double Furniture::getVolume() const
{
    return length * width * height;
}

string Furniture::getColor() const
{
    return baseColor;
}

// =====================
// Setter
// =====================
void Furniture::setMaterialType(MaterialType material)
{
    this->material = material;
}

void Furniture::setDimension(double length,
                             double width,
                             double height)
{
    if (length <= 0)
        throw invalid_argument("Length must be greater than 0.");

    if (width <= 0)
        throw invalid_argument("Width must be greater than 0.");

    if (height <= 0)
        throw invalid_argument("Height must be greater than 0.");

    this->length = length;
    this->width = width;
    this->height = height;
}

void Furniture::setColor(const string& color)
{
    if (color.empty())
        throw invalid_argument("Color cannot be empty.");

    baseColor = color;
}
// =====================
// Calculate Material Cost
double Furniture::calculateMaterialCost() const
{
    double unitPrice = 0.0;

    switch(material)
    {
    case MaterialType::Wood:
        unitPrice = 500.0;
        break;

    case MaterialType::Metal:
        unitPrice = 300.0;
        break;

    case MaterialType::Plastic:
        unitPrice = 150.0;
        break;
    }

    return getArea() * unitPrice;
}