Projet de Programmation de Rush Hour (2016)

Compilation Cmake:
	Dans le dossier du projet faire :
		- $ mkdir build
		- $ cd build
		- $ cmake ..
		- $ make
		- $ make install (déplace : - l'exécutable rush-hourV1 dans le dossier build/bin/,
									- la librairie libgame.a dans build/lib/ 
									- game.h et piece.h dans build/include/)
		- $ make test
		- $ make clean
		
Le projet fonctionne également sous windows, bien que cmake ne génère pas de makefile compatible.
Vous pouvez le compiler avec MinGW par exemple avec la commande :
	gcc -std=c99 -Wall -I./src/game/ -I./src/rushHour/ ./src/game/game.c ./src/game/piece.c ./src/rushHour/rush-hour.c ./src/rushHour/displayV1.c -o rushHourV1
