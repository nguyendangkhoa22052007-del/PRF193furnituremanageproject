#pragma once
#include <string>

enum class MaterialType
{
    Wood,
    Metal,
    Plastic
};

class Furniture
{
private:
    // Basic Information
    std::string ID;
    MaterialType material;

    // Dimensions
    double length;
    double width;
    double height;

    // Appearance
    std::string baseColor;

public:

    // Constructor
    Furniture(
        const std::string& id,
        MaterialType material,
        double length,
        double width,
        double height,
        const std::string& color
    );

    virtual ~Furniture() = default;

    //=========================
    // Static Helper Functions
    //=========================

    static std::string materialToString(MaterialType material);

    static MaterialType stringToMaterial(const std::string& material);

    //=========================
    // Getter
    //=========================

    std::string getID() const;

    MaterialType getMaterialType() const;

    double getLength() const;

    double getWidth() const;

    double getHeight() const;

    double getArea() const;

    double getVolume() const;

    std::string getColor() const;

    //=========================
    // Setter
    //=========================

    void setMaterialType(MaterialType material);

    void setDimension(
        double length,
        double width,
        double height
    );

    void setColor(const std::string& color);

    //=========================
    // Pricing
    //=========================

    virtual double calculateMaterialCost() const;

    // StandardFurniture và CustomFurniture sẽ override
    virtual double calculatePricing() const = 0;
};