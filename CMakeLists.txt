cmake_minimum_required(VERSION 2.8)

project(RUSH_HOUR)

ADD_DEFINITIONS(-std=c99 -g -Wall -Werror)

include_directories(${RUSH_HOUR_SOURCE_DIR}/src/game
					${RUSH_HOUR_SOURCE_DIR}/src/rushHour)

#Le répertoire contenant les codes source
add_subdirectory(src)