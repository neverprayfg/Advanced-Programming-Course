
#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <iostream>
#include <string>
class Ingredient{
public:
    virtual std::string get_name() = 0;
    virtual Ingredient* get_pointer() = 0;
    double get_price_unit(){
        return price_unit;
    }
    size_t get_units(){
        return units;
    }
    double price() {
        return price_unit * units;
    }
    
protected:
    Ingredient(double price_unit, size_t units): price_unit(price_unit), units(units){}
    double price_unit;
    size_t units;
    std::string name;
};
 
#endif //INGREDIENT_H