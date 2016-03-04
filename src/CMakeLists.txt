#création de la librairie libgame.c
add_library(game game/game.c game/piece.c)

#Il faut préciser les sous-répertoires du répertoire courant
add_subdirectory(game)
add_subdirectory(rushHour)

install(FILES ${RUSH_HOUR_BINARY_DIR}/src/libgame.a DESTINATION ${RUSH_HOUR_BINARY_DIR}/lib
		PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
install(FILES ${RUSH_HOUR_SOURCE_DIR}/src/game/game.h ${RUSH_HOUR_SOURCE_DIR}/src/game/piece.h DESTINATION ${RUSH_HOUR_BINARY_DIR}/include
		PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
