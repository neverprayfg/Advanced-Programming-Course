#include "../include/cappuccino.h"
#include "../include/sub_ingredients.h"

Cappuccino::Cappuccino() : EspressoBased(){
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    name = "Cappuccino";
}

Cappuccino::Cappuccino(const Cappuccino& cap) : EspressoBased(cap){
    for(const auto& i: cap.side_items){
        side_items.push_back(i->get_pointer());
    }
}

Cappuccino::~Cappuccino()
{
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Cappuccino::operator=(const Cappuccino& cap){
    if(&cap == this) return;
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
    EspressoBased::operator=(cap);
    for(const auto& i: cap.side_items){
        side_items.push_back(i->get_pointer());
    }
}

std::string Cappuccino::get_name(){
    return name;
}

double Cappuccino::price(){
    double sum = 0;
    for(const auto& i: ingredients){
        sum += i->price();
    }
    for(const auto& i: side_items){
        sum += i->price();
    }
    return sum;
}

void Cappuccino::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items(){
    return side_items;
}
