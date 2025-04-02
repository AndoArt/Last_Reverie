a.out:	main.o Item.o Character.o Mob.o
	g++ -g -Wall main.o Item.o Character.o Mob.o /usr/local/cs/cs251/react.o -lcurl

Item.o:	Item.cpp Item.h
	g++ -Wall -c Item.cpp

Character.o: Character.cpp Character.h Item.h
	g++ -Wall -c Character.cpp

Mob.o : Mob.cpp Mob.h
	g++ -Wall -c Mob.cpp

main.o:	main.cpp Item.h Character.h Mob.h
	g++ -Wall -c main.cpp