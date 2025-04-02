#ifndef __Item_H__
#define __Item_H__

class Item {
    private:
        string name;
        string type;
        string effect;
        int effect_val;

    public:
        Item();
        Item(string n , string t);
        Item(string n, string t, string e, int ev);
        void add(Item** inv);
        void remove(Item** inv, int i);
        string getName();
        virtual void inspect();
        string getType();
        string getEffect();
        int getEffect_val();

        
};

class Gear : public Item {
    private:

    public:
        Gear();
        Gear(string n, string e, int ev);
};

class Consumable : public Item {
    private:

    public:
        Consumable(string n, string e, int ev);
};

class KeyItems : public Item {
    private:

    public:
        KeyItems(string n);
};

#endif
