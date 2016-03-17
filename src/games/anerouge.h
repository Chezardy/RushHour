#ifndef _AR_
#define _AR_
/*
Creer un jeu de taille 5*5 et y place les pieces de l'ane rouge
(en utilisant les nouvelles fonctions implementés dans les v2 de game.c et piece.c)

Il faudra aussi modifier les fonction d'affichage pour que les bords au et bas des tableaux fassent la bonne taille
	et trouver une moyen de régler le problème de fin de partie entre les jeux.
	(+ placer la sortie a la bonne place dans gridDisplay et simpleDisplay, et eventuellement changer les couleurs dans gridDisplay)
*/
game AR_getGame();


bool game_over_ar(cgame g);

#endif
