#add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

#créé l'exécutable test_piece1
add_executable(test_piece1 test_piece1.c)
add_executable(test_play_move test_play_move.c)

#spécifie la librairie nécessaire pour l'exécutable en question
target_link_libraries(test_piece1 game)
target_link_libraries(test_play_move game)
