#créé l'exécutable rush-hour
add_executable(rush-hour rush-hour.c)

#spécifie la librairie nécessaire pour l'exécutable "rush-hour"
target_link_libraries(rush-hour game)

#spécifie l'emplacement de la librairie
link_directories(${RUSH_HOUR_BINARY_DIR}/src/game)