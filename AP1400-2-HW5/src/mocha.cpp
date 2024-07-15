#include "../include/mocha.h"
#include "../include/sub_ingredients.h"
Mocha::Mocha() : EspressoBased(){
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
    name = "Mocha";
}

Mocha::Mocha(const Mocha& cap) : EspressoBased(cap){
    for(const auto& i: cap.side_items){
        side_items.push_back(i->get_pointer());
    }
}

Mocha::~Mocha()
{
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Mocha::operator=(const Mocha& cap){
    if(&cap == this) return;
    for(const auto& i : side_items)
        delete i;
    side_items.clear();    
    EspressoBased::operator=(cap);
    for(const auto& i: cap.side_items){
        side_items.push_back(i->get_pointer());
    }
}

std::string Mocha::get_name(){
    return name;
}

double Mocha::price(){
    double sum = 0;
    for(const auto& i: ingredients){
        sum += i->price();
    }
    for(const auto& i: side_items){
        sum += i->price();
    }
    return sum;
}

void Mocha::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items(){
    return side_items;
}
