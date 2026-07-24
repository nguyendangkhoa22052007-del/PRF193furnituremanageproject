#pragma once
#include <string>

enum class MaterialType {
    Wood,
    Metal,
    Plastic
};

class Furniture {
private:
    std::string ID;

    MaterialType material;

    double length;
    double width;
    double height;

    std::string baseColor;

public:
    Furniture(
        const std::string& id,
        MaterialType material,
        double length,
        double width,
        double height,
        const std::string& color
    );

    virtual ~Furniture() = default;
    static std::string materialToString(MaterialType material);

    static MaterialType stringToMaterial(std::string material);
    // Getter
    std::string getID() const;

    MaterialType getMaterialType() const;

    double getLength() const;
    double getWidth() const;
    double getHeight() const;

    double getArea() const;

    double getVolume() const;

    std::string getColor() const;

    // Setter
    void setMaterialType(MaterialType material);

    void setDimension(
        double length,
        double width,
        double height
    );

    void setColor(const std::string& color);

    virtual double calculateMaterialCost() const;
};