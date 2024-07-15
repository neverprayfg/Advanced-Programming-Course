#include "../include/espresso_based.h"

EspressoBased::EspressoBased() = default;

EspressoBased::EspressoBased(const EspressoBased& esp){
    name = esp.name;
    for(const auto& i: esp.ingredients){
        ingredients.push_back(i->get_pointer());
    }
}

void EspressoBased::operator=(const EspressoBased& esp){
    if(&esp == this) return;
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
    name = esp.name;
    for(const auto& i: esp.ingredients){
        ingredients.push_back(i->get_pointer());
    }
}

EspressoBased::~EspressoBased()
{
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

void EspressoBased::brew(){
    return;
}

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return ingredients;
}