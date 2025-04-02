#include <iostream>
using namespace std;
#include "Item.h"

//===================Item======================

Item::Item() : name("") , type ("") , effect ("") , effect_val(0) {} // the "empty" item
Item::Item(string n , string t) : name(n) , type(t) {}
Item::Item(string n, string t, string e, int ev) : name(n) , type(t) , effect(e) , effect_val(ev) {}
        
//adds an item to a given inventory
void Item::add(Item** inv) {
    int i = 0;

    while (i < 5) {
        if (inv[i] -> getName() != "") {i++;}
        else {inv[i] = this; break;}
    }

}

void Item::remove(Item** inv, int i) {
        inv[i] = new Item;
}
        
string Item::getName() {return name;}

void Item::inspect() {
    cout << "Name: "<< name << endl;
}

string Item::getType() {return type;}

string Item::getEffect() {return effect;}
        
int Item::getEffect_val() {return effect_val;}

//==================Gear======================

Gear::Gear() : Item() {}

Gear::Gear(string n, string e, int ev) : Item(n , "Gear", e, ev) {}


//==================Consumable======================

Consumable::Consumable(string n, string e, int ev) : Item(n , "Consumable", e, ev){}

//==================KeyItems======================

KeyItems::KeyItems(string n) : Item(n, "keyItem") {}