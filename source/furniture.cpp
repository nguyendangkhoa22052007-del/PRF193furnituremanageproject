#include "furniture.h"
#include <stdexcept> //invalid_argument
using namespace std;
//CONSTRUCTOR
Furniture::Furniture(std::string id, std::string material, double size, std::string color) {
    //check if id is empty
    if (id.empty()) {
        throw invalid_argument("Ma ID noi that khong duoc de trong!");
    }
    ID = id;
    setMaterialType(material);
    setSize(size);
    if (color.empty()) {
        BaseColor = "Default Color";
    } else {
        BaseColor = color;
    }
}
//GETTER FUNCTIONS
string Furniture::getID() const {
    return ID;
}
string Furniture::getMaterialType() const {
    return MaterialType;
}
double Furniture::getDimension() const {
    return dimension;
}
string Furniture::getColor() const {
    return BaseColor;
}
//SETTER FUNCTIONS
string Furniture::setMaterialType(string material) {
    //check material
    if (material != "Wood" && material != "Metal" && material != "Plastic") {
        throw invalid_argument("Vat lieu khong hop le! Chi duoc chon Wood, Metal, hoac Plastic.");
    }
    MaterialType = material;
    return MaterialType;
}

double Furniture::setSize(double size) {
    //check if size is negative
    if (size <= 0) {
        throw invalid_argument("Kich thuoc noi that phai lon hon 0!");
    }
    dimension = size;
    return dimension;
}
string Furniture::setColor(string color) {
    //check if color is empty
    if (color.empty()) {
        throw invalid_argument("Mau sac khong duoc de trong!");
    }
    BaseColor = color;
    return BaseColor;
}