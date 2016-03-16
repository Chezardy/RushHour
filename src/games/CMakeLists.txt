#créé l'exécutable rush-hour
add_executable(jeux rush-hour.c anerouge.c displayV1.c main.c utils.c strategies.c)

#spécifie la librairie nécessaire pour l'exécutable "rush-hour"
target_link_libraries(jeux game)

#spécifie l'emplacement de la librairie
link_directories(${RUSH_HOUR_BINARY_DIR}/src/game)

#lors de "make install" l'exécutable rush-hourV1 est copié dans le dossier bin
install(FILES ${RUSH_HOUR_BINARY_DIR}/src/rushHour/jeux DESTINATION ${RUSH_HOUR_BINARY_DIR}/bin
		PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)

