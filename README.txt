Projet de Programmation de Rush Hour et de l'ane rouge(2016)

L'executable prend les arguments suivants :
#Choix du jeux :
	-rushhour pour lancer le rush-hour
	-anerouge pour lancer l'Ane Rouge
#Choix de l'affichage :
	-nocolor pour lancer l'affichage simplifié sans couleur
	-text pour afficher la grille uniquement par les coordonnées des pieces
#Solveur :
	-solveur pour utiliser le solveur


Compilation Cmake:
	Dans le dossier du projet faire :
		- $ mkdir build
		- $ cd build
		- $ cmake ..
		- $ make install (déplace : - l'exécutable jeux dans le dossier build/bin/,
									- la librairie libgame.a dans build/lib/ 
									- game.h et piece.h dans build/include/)
		- $ make test
		- $ make clean
		
/*
Le projet fonctionne également sous windows, bien que cmake ne génère pas de makefile compatible.
Vous pouvez le compiler avec MinGW par exemple avec la commande :
	gcc -std=c99 -Wall -I./src/game/ -I./src/rushHour/ ./src/game/game.c ./src/game/piece.c ./src/rushHour/rush-hour.c ./src/rushHour/displayV1.c -o rushHourV1
*/