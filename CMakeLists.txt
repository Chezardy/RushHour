cmake_minimum_required(VERSION 2.8)

project(RUSH_HOUR)

ADD_DEFINITIONS(-std=c99 -g -Wall -Werror)

include_directories(${RUSH_HOUR_SOURCE_DIR}/src/libgame
					${RUSH_HOUR_SOURCE_DIR}/src/games)

#Le répertoire contenant les codes source
add_subdirectory(src)

enable_testing()

add_test(piece1 ${RUSH_HOUR_BINARY_DIR}/src/libgame/tests/test_piece1)
add_test(play_move ${RUSH_HOUR_BINARY_DIR}/src/libgame/tests/test_play_move)


#Si le test dure trop longtemps, il est arrêté
set_tests_properties(play_move PROPERTIES TIMEOUT 2)
set_tests_properties(piece1 PROPERTIES TIMEOUT 2)
