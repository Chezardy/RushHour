#créé l'exécutable test_piece1
add_executable(test_piece1 test_piece1.c)

#spécifie la librairie nécessaire pour l'exécutable "test_piece1"
target_link_libraries(test_piece1 game)