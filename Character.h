#ifndef __Character_H__
#define __Character_H__
#include "Item.h"
#include "Character.h"

class Player{
    private:
        string name;
        int lvl, HP, maxHP, STR, DEF, EXP, reqExp, statPts;
        Gear armor, weapon;

    public:
        Player();
        Player(string n);
        Player(string n, int l, int h, int mh, int s, int d, int e, int r, int st, Gear ar, Gear wp);
        string getName() const;
        int getLvl() const;
        int getHP() const;
        int getMaxHP() const;
        int getSTR() const;
        int getDEF() const;
        int getEXP() const;
        int getRExp() const;
        int getStPts() const;
        bool levelUp();  
        void expGain(int e);
        void addmaxHP(int i);
        void addSTR(int i);
        void addDEF(int i);

        Gear getArmor() const;
        Gear getWeapon() const;
        
        void replenishHP();
        void takeDmg(int i);

        void equipWeapon(Gear it, Item** inv, int i);
        void equipArmor(Gear it, Item** inv, int i);

        void useItem(Item* it, Item** inv, int i);
};


#endif
