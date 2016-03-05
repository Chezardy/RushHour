// Codes couleurs
#define USE_COLOR 1

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[41;30m"
#define KGRN  "\x1B[42;32m"
#define KWHT  "\x1B[47;37m"
#define KBLK  "\x1B[40;30m"

#define KYEL  "\x1B[43;30m"
#define KBLU  "\x1B[44;30m"
#define KMAG  "\x1B[45;30m"
#define KCYN  "\x1B[46;30m"
#define KRED2  "\x1B[101;30m"
#define KGRN2  "\x1B[102;30m"
#define KYEL2  "\x1B[103;30m"
#define KBLU2 "\x1B[104;30m"
#define KMAG2  "\x1B[105;30m"
#define KCYN2  "\x1B[106;30m"

/*
Fonction d'affichage en mode console, dessine une grille représentant le jeu en couleurs.
La grille affiché a une taille 2 fois supérieur à la grille de jeu.
*/
void GridDisplay(game g, int nb_pieces);

/*
Affichage simplifié, plus petit et sans couleur pour les terminaux ne supportant pas les escape code ANSI
Fonctionnement similaire a DiplayGrid
*/
void SimpleDisplay(game g, int nb_pieces);

/*
Fontion d'affichage tres simplifié, a priori uniquement utile pour le débuggage
Affiche les coordonnées et les infos de chaques pieces
*/
void TextDisplay(game currentGame, int nb_pieces);