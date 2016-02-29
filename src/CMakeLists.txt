#création de la librairie libgame.c
add_library(game game/game.c game/piece.c)

#Il faut préciser les sous-répertoires du répertoire courant
add_subdirectory(game)
add_subdirectory(rushHour)