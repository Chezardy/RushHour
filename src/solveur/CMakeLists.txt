add_executable(solveur solveur.c ../games/anerouge.c ../games/rush-hour.c)

target_link_libraries(solveur game)

link_directories(${RUSH_HOUR_BINARY_DIR}/src/game)

install(FILES ${RUSH_HOUR_BINARY_DIR}/src/solveur/solveur
		DESTINATION ${RUSH_HOUR_BINARY_DIR}/bin
		PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)