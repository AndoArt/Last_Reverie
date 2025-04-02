#include <iostream>
#include <fstream>
using namespace std;
#include"/usr/local/cs/cs251/react.h"
#include "Item.h"
#include "Character.h"
#include "Mob.h"

class State {
    private:
        Player player;
        int page;
        Item **inventory;
        string name;
        string type;
        string effect;
        int effect_value;
        int stat_spend;
        int selected_item;
        Mob* monsters;

    public:
        State(istream &is) { read_from(is); }
        void read_from(istream &is) {
            string tmp;
            getline(is,tmp);
            is >> page;
            getline(is,tmp);
            is >> stat_spend;
            getline(is,tmp);
            is >> selected_item;
            
            getline(is,tmp);
            getline(is,tmp);

            //Player
            string Cname;
            int lvl, hp, maxhp , str, def, exp, Rexp, stpt;
            Gear _ar, _wp;
            getline(is, tmp, ' ');
            getline(is, Cname);
            getline(is, tmp, ' ');
            is >> lvl;
            getline(is, tmp, ' ');
            is >> hp;
            getline(is, tmp, ' ');
            getline(is, tmp, ' ');
            is >> maxhp;
            getline(is, tmp, ' ');
            is >> str;
            getline(is, tmp, ' ');
            is >> def;
            getline(is, tmp, ' ');
            is >> exp;
            getline(is, tmp, ' ');
            getline(is, tmp, ' ');
            is >> Rexp;
            getline(is, tmp, ' ');
            is >>stpt;

            getline(is, tmp);

            Player temp(Cname, lvl, hp, maxhp, str, def ,exp, Rexp, stpt, _ar, _wp);
            player = temp;

            getline(is, tmp);

            //inventory
            inventory = new Item*[5];

            for (int i = 0 ; i < 5 ; i++) {
                inventory[i] = new Item;
            }

            for (int i = 0 ; i < 5 ; i++) {

                getline(is, name);
                getline(is, type);
                getline(is, effect);
                is >> effect_value;

                getline(is, tmp);

                Item *f;

                if (type == "Gear") {
                    f = new Gear(name, effect, effect_value);
                    (*f).add(inventory);
                }
                if (type == "Consumable") {
                    f = new Consumable(name, effect, effect_value);
                    (*f).add(inventory);
                }
                if (type == "KeyItem") {
                    f = new KeyItems(name);
                    (*f).add(inventory);
                }
                getline(is,tmp);            
            }

            getline(is,tmp);

            //monsters
            string nameM;
            int hpM, lvlM, dmgM;
            bool dM;


            monsters = new Mob[4];

            for (int i = 0 ; i < 4 ; i++) {

                getline(is, tmp ,' ');
                getline(is, nameM);
                getline(is, tmp ,' ');
                is >> hpM;
                getline(is, tmp ,' ');
                is >> lvlM;
                getline(is,tmp);
                is >> dmgM;
                getline(is,tmp);
                is >> dM;

                getline(is, tmp);

                if(!dM) monsters[i] = Mob(nameM, hpM, dmgM, lvlM, dM);
            }
        }
    ~State() {
        delete [] inventory;
        delete [] monsters;}

    void write_to(ostream &os) const {
        os << "#" << endl;
        os << page << endl;
        os << stat_spend << endl;
        os << selected_item << endl;
        os << "#" << endl;
        os << "Name: " << player.getName() << endl;
        os << "Level: " << player.getLvl() << endl;
        os << "HP: " << player.getHP() << " / " << player.getMaxHP() << endl;
        os << "STR: " << player.getSTR() << endl;
        os << "DEF: " << player.getDEF() << endl;
        os << "EXP: " << player.getEXP() << " / " << player.getRExp() << endl;
        os << "Pts: " << player.getStPts() << endl;
        
        os << "#" << endl;

        for (int i = 0 ; i < 5 ; i++) {
            os << inventory[i] -> getName() << endl;
            os << inventory[i] -> getType() << endl;
            os << inventory[i] -> getEffect() << endl;
            os << inventory[i] -> getEffect_val() << endl;

            os << endl;
        }

        os << "#" << endl;

        for (int i = 0 ; i < 4 ; i++) {
            os << "Name: " <<monsters[i].getName() << endl;
            os << "HP: " << monsters[i].getHP() << endl;
            os << "Lvl: " << monsters[i].getlvl() << endl;
            os << monsters[i].getDmg() << endl;
            os << monsters[i].getdead() << endl;
        }
    }

    int get_page() const {return page;}
    Item** getInv() const {return inventory;}

    void initialize_fight();
    void resume();
    void save_and_exit();
    void update(string input, istream &is);
};

//Global Variables
string text[30];
string info[10];
bool react = false;
const int input_index = 2, prompt_index = 25;


void read_text_data() {
    ifstream fs("screen.txt");
    string comment;
    for (int i = 0; i < 30; ++i) {
        getline(fs, text[i], '#');
        if (!text[i].empty()) text[i].pop_back();  // remove newline
    getline(fs, comment);
  }
}

void display(const State &state, ostream &os) {
    int n = state.get_page();
    
    if (react) {
        if (1 == n) {
            _add_yaml("startscreen.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
	        os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (2 == n) {
            _add_yaml("2screen.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
	        os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (3 == n) {
            _add_yaml("mainscreen.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
            os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (6 == n) {
            _add_yaml("rest.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
            os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (7 == n || 20 == n) {
            _add_yaml("inventoryscreen.yaml", {{"prompt_index", prompt_index},
            {"input_index", input_index}});
            os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (8 == n) {
            _add_yaml("usescreen2.yaml");
            os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (10 == n) {
            _add_yaml("profilescreen.yaml", {{"prompt_index", prompt_index},
            {"input_index", input_index}});
            os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (11 == n) {
            _add_yaml("spendscreen.yaml", {{"prompt_index", prompt_index},
            {"input_index", input_index}});
            os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (13 == n) {
            _add_yaml("distributescreen.yaml", {{"prompt_index", prompt_index},
            {"input_index", input_index}});
            os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (21 == n) {
            _add_yaml("usescreen1.yaml");
            os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (17== n) {
            _add_yaml("battlescreen.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
                
            _add_yaml("slimes.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
                
	        os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
        else if (18 == n) {
            _add_yaml("attackscreen.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
                
            _add_yaml("slimes.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
        }
        else {
            _add_yaml("story.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
	    os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
        }
	    
    } else os << "\033c";

    ofstream updt("curr_state");
    state.write_to(updt);

    ifstream fs("curr_state");
    string tmp;
    for (int i = 0; i < 10; ++i) {
        getline(fs, info[i], '#');
        if (!info[i].empty()) info[i].pop_back();  // remove newline
    getline(fs, tmp);
    }
    
    if (3 == n) {
        ifstream fs("curr_state");
        string tmp;
        getline(fs, tmp, '#');
        getline(fs, tmp, '#');
        getline(fs, tmp);
        
        for (int i = 0; i < 3 ; i++) {
            getline(fs, tmp);
            os << tmp << endl;}
            os << endl;
    }
    else if (7 == n) {
        ifstream fs("curr_state");
        string tmp;
        getline(fs, tmp, '#');
        getline(fs, tmp, '#');
        getline(fs, tmp);
        
        for (int i = 0; i < 3 ; i++) {
            getline(fs, tmp);
            os << tmp << endl;}
            os << endl
               << endl
               << endl
               << endl;
    os    << text[n]
            << info[3];
    }
    else if (10 == n) {
    os      << info[2] << endl;
    }
    else if (17 == n) {
        ifstream fs("curr_state");
        string tmp;
        getline(fs, tmp, '#');
        getline(fs, tmp, '#');
        getline(fs, tmp);

        for (int i = 0; i < 3 ; i++) {
            getline(fs, tmp);
            os << tmp << endl;}
            os << endl
               << endl
               << endl
            << info[4] << endl;
            //<< text[n] << endl;
    }
    else if (20 == n) {
        ifstream fs("curr_state");
        string tmp;
        getline(fs, tmp, '#');
        getline(fs, tmp, '#');
        getline(fs, tmp);
        
        for (int i = 0; i < 3 ; i++) {
            getline(fs, tmp);
            os << tmp << endl;}
            os << endl
               << endl
               << endl
               << endl;
    os    << text[n]
            << info[3];
    }
    else {
    os      << text[n];
    }
    

    if (react) os << '\0';
    
}

void State::initialize_fight() {
    for (int i = 0 ; i < 4 ; i++) {
        monsters[i] = Mob("Slime", player.getLvl());
    }
}

void State::resume() {
  ifstream fs("saved_state");
  read_from(fs);
}

void State::save_and_exit() {
  ofstream fs("saved_state");
  write_to(fs);
  exit(0);
}


void State::update(string input, istream &is){
    if (react && _received_event()) {
	// get input from the stream
	is.get(); is.get();  // skip first two characters
	if ('~' != is.peek()) getline(is, input, '\0');
    }


    if (0 == page) page = 1;
    else {
        if (1 == page) {
            if (_event_id_is("quit")) exit(0);
            if (_event_id_is("start")) page = 2;
            if (_event_id_is("resume")) {
                page = 3;
                resume();
            }
            else return;
        }
        else if (2 == page) {
            Player tmp(input);
            player = tmp;
            page = 3;
        }
        else if (3 == page){
            if (_event_id_is("quit")) {
                page = 1;
                save_and_exit();}
            if (_event_id_is("adventure")) page = 4;
            if (_event_id_is("rest")) page = 6;
            if (_event_id_is("inventory")) page = 7;
            if (_event_id_is("profile")) page = 10;
            else return;
        }
        else if (4 == page) {
            initialize_fight();
            if (_event_id_is("click")) page = 17;
        }
        else if (5 == page) {
            if (_event_id_is("click")) page = 3;
        }
        else if (6 == page) {
            player.replenishHP();
            if (_event_id_is("click")) page = 3;
        }
        else if (7 == page) {
            if (_event_id_is("back")) page = 3;
            if (_event_id_is("item1")) {
                selected_item = 0;
                page = 8;}
            if (_event_id_is("item2")) {
                selected_item = 1;
                page = 8;}
            if (_event_id_is("item3")) {
                selected_item = 2;
                page = 8;}
            if (_event_id_is("item4")) {
                selected_item = 3;
                page = 8;}
            if (_event_id_is("item5")) {
                selected_item = 4;
                page = 8;}
        }
        else if (8 == page) {
            if (_event_id_is("equip")) page = 16;
            if (_event_id_is("use")) {
                page = 14;
            }
            if (_event_id_is("discard")) {
                page = 9;
            }
            if (_event_id_is("back")) {
                page = 7;
            }
        }
        else if (9 == page) {
            inventory[selected_item]->remove(inventory, selected_item);
            if (_event_id_is("click")) page = 7;
        }
        else if (10 == page) {
            if (_event_id_is("distribute")) page = 11;
            if (_event_id_is("back")) page = 3;
        }
        else if (11 == page) {
            stat_spend = stoi(input);
            if (stat_spend > player.getStPts()) {
                page = 12;
            }
            else {page = 13;}
        }
        else if (12 == page) {
            if (_event_id_is("click")) page = 11;
        }
        else if (13 == page) {
            if (_event_id_is("back")) {page = 10;}
            if (_event_id_is("hp")) {
                player.addmaxHP(stat_spend);
                page = 3;
            }
            if (_event_id_is("str")) {
                player.addSTR(stat_spend);
                page = 3;
            }
            if (_event_id_is("def")) {
                player.addDEF(stat_spend);
                page = 3;
            }
        }
        else if (14 == page) {
            player.useItem(inventory[selected_item], inventory, selected_item);
            if (_event_id_is("click")) page = 7;
        }
        else if (15 == page) exit(0);
        else if (16 == page) {if (_event_id_is("click")) page =3;}
        else if (17 == page) {
            bool win = false;

            if (player.getHP() <= 0) {page = 15; return;}

            for (int i = 0 ; i < 4 ; i++) {
                monsters[i].checkDead();
            }

            if (monsters[1].getHP() < 1 && monsters[2].getHP() < 1 && monsters[3].getHP() < 1 && monsters[4].getHP() < 1) win = true;

            if (win) {
                ifstream fs("drops");
                string tmp;
                int j  = rand() % 5;
                for (int i = 0; i < j; ++i) {
                    getline(fs, tmp, '#');
                }
                getline(fs, tmp);

                getline(fs, name);
                getline(fs, type);
                getline(fs, effect);
                fs >> effect_value;

                Item *f;

                if (type == "Gear") {
                    f = new Gear(name, effect, effect_value);
                    (*f).add(inventory);
                }
                if (type == "Consumable") {
                    f = new Consumable(name, effect, effect_value);
                    (*f).add(inventory);
                }
                if (type == "KeyItem") {
                    f = new KeyItems(name);
                    (*f).add(inventory);
                }

                player.expGain(15);
                if (player.levelUp()) {page = 5; return;}
                else {page = 3; return;}
                }
                

            if (_event_id_is("attack")) page = 18;
            if (_event_id_is("inventory")) page = 20;
            if (_event_id_is("run")) page = 19;
            
        }
        else if (18 == page) {
            if (_event_id_is("slime1")) monsters[0].takeDmg(player.getSTR());
            if (_event_id_is("slime2")) monsters[1].takeDmg(player.getSTR());
            if (_event_id_is("slime3")) monsters[2].takeDmg(player.getSTR());
            if (_event_id_is("slime4")) monsters[3].takeDmg(player.getSTR());

            for (int i = 0 ; i < 4 ; i++) {
                if (!monsters[i].getdead()) {player.takeDmg(monsters[i].getDmg());}
            }

            if (_event_id_is("back")) page = 17;
            page = 17;
        }
        else if (19 == page) {if (_event_id_is("click")) page = 3;}
        else if (20 == page) {
            if (_event_id_is("back")) page = 17;
            if (_event_id_is("item1")) {
                selected_item = 0;
                page = 21;}
            if (_event_id_is("item2")) {
                selected_item = 1;
                page = 21;}
            if (_event_id_is("item3")) {
                selected_item = 2;
                page = 21;}
            if (_event_id_is("item4")) {
                selected_item = 3;
                page = 21;}
            if (_event_id_is("item5")) {
                selected_item = 4;
                page = 21;}
        }
        else if (21 == page) {
            if (_event_id_is("use")) {
                page = 22;
            }
            if (_event_id_is("back")) {
                page = 20;
            }
        }
        else if (22 == page) page = 17;
    }
}


// -------- do not modify the code below -------
// ------- (except briefly for debugging) ------

int main(int argc, char **argv) {
  react = (argc > 1);
  read_text_data();

  bool just_starting = react ? _read_event_info() : true;
  while(1) {
	ifstream fs1(just_starting ? "initial_state" : "curr_state");
	State state(fs1);
	fs1.close();

	string input;
	if (just_starting) just_starting = false;
	else if (!react) getline(cin, input);

	ifstream fs2("incoming_text");
	state.update(input, fs2);

	ofstream fs3("outgoing_text"), fs4(react ? "end_state" : "curr_state");
	display(state, react ? fs3 : cout);
	state.write_to(fs4);

	if (react) {
  	  _write_react_yaml();
  	  break;
	}
  }
}
