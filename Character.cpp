#include <iostream>
#include <fstream>
using namespace std;
#include "Character.h"

Player::Player() : name("") , lvl(0) , HP(0) , STR(0) , DEF(0) , EXP(0) {}

Player::Player(string n) : name(n) , lvl(1) , HP(10) , maxHP(10), STR(10) , DEF(10) , EXP(0), reqExp(10), statPts(0) {}

Player::Player(string n, int l, int h, int mh, int s, int d, int e, int r, int st, Gear ar, Gear wp) : name(n) , lvl(l) , HP(h) , maxHP(mh), STR(s) , DEF(d) , EXP(e), reqExp(r), statPts(st), armor(ar), weapon(wp) {}

string Player::getName() const {return name;}

int Player::getLvl() const {return lvl;}

int Player::getHP() const {return HP;}

int Player::getSTR() const {return STR;}

int Player::getDEF() const {return DEF;}

int Player::getEXP() const {return EXP;}

int Player::getMaxHP() const {return maxHP;}

int Player::getRExp() const {return reqExp;}

int Player::getStPts() const {return statPts;}

Gear Player::getArmor() const {return armor;}

Gear Player::getWeapon() const {return weapon;}

bool Player::levelUp() {
    if (EXP >= reqExp) {
    ifstream lvl_info("level_info");
    string tmp;
    getline(lvl_info, tmp);
        while (EXP >= reqExp) {
            getline(lvl_info, tmp);
            lvl_info >> reqExp;
        }
        lvl_info >> lvl;
        statPts += 10;
        return 1;
    }
    return 0;
}
        
void Player::expGain(int e) {
    EXP += e;
}

void Player::addmaxHP(int i) {
    maxHP += i;
    statPts -= i;
    }

void Player::addSTR(int i) {
    STR += i;
    statPts -= i;}

void Player::addDEF(int i) {
    DEF += i;
    statPts -= i;}


void Player::replenishHP() {
    HP = maxHP;
}

void Player::takeDmg(int i) {
    int dmg_calc = i/DEF;
    HP -= dmg_calc;
}

void Player::equipWeapon(Gear it, Item** inv, int i) {
    it.remove(inv, i);
    weapon.add(inv);
    weapon = it;
}

void Player::equipArmor(Gear it, Item** inv, int i) {
    it.remove(inv, i);
    armor.add(inv);
    armor = it;
}

void Player::useItem(Item* it, Item** inv, int i) {
    string eff = it->getEffect();
    int effVal = it->getEffect_val();
    if (eff == "Heal") {
        HP += effVal;
        it -> remove(inv, i);}
    if (eff == "Strengthen") {
        STR += effVal;
        it -> remove(inv, i);}
    if (eff == "Defence") {
        DEF += effVal;
        it -> remove(inv, i);
    }
}


