#include <iostream>
using namespace std;
#include "Mob.h"

Mob::Mob() : name(""), HP(0) , Dmg(0) , lvl(0) , dead(true) {}
Mob::Mob(string n, int l) : name(n) , lvl(l) {
    HP = 10 * lvl;
    Dmg = 5 * lvl;
    dead = false;
}
Mob::Mob(string n, int h, int d, int l, int b) : name(n) , HP(h), Dmg(d), lvl(l), dead(b) {}

void Mob::takeDmg(int i) {
    HP -= i;
    
}

void Mob::checkDead() {
    if (HP <= 0) dead = true;
}

string Mob::getName() {return name;}
int Mob::getHP() {return HP;}
int Mob::getDmg() {return Dmg;}
int Mob::getlvl() {return lvl;}
bool Mob::getdead() {return dead;}