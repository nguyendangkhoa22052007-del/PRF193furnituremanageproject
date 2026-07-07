#pragma once
#include <string>
//building furniture class
class Furniture{
    private:
        std::string ID;
        std::string MaterialType;
        double dimension;
        std::string BaseColor;
    public:
        //constructor
        Furniture(std::string id, std::string material, double size, std::string color);
        //destructor
        virtual ~Furniture() = default;
        //getter
        std::string getID() const;
        std::string getMaterialType() const;
        double getDimension() const;
        std::string getColor() const;
        //setter
        std::string setMaterialType(std::string material);
        double setSize(double size);
        std::string setColor(std::string color);
};