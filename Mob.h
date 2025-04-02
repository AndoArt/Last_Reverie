#ifndef __Mob_H__
#define __Mob_H__
#include "Character.h"

class Mob{
    private:
        string name;
        int HP, Dmg, lvl;
        bool dead;
    
    public:
        Mob();
        Mob(string n, int l);
        Mob(string n, int h, int d, int l, int b);
        void takeDmg(int i);
        string getName();
        int getHP();
        int getDmg();
        int getlvl();
        bool getdead();
        void checkDead();
};

#endif