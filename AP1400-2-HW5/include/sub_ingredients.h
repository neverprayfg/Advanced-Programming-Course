#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#include "ingredient.h"
#define DEFCLASS(INGREDIENT, num)                       \
class INGREDIENT : public Ingredient{                   \
public:                                                 \
    INGREDIENT(size_t units) : Ingredient(num, units){  \       
        name = #INGREDIENT;                             \
    }                                                   \
    virtual std::string get_name() override{            \
        return name;                                    \
    }                                                   \
    virtual Ingredient* get_pointer() override{         \
        return new INGREDIENT(units);                   \
    }                                                   \
}
DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);
 
#endif // SUB_INGREDIENTS_H

