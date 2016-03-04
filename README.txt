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