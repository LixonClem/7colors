#Déclaration du projet

project(7colors)


#WWWWWWWWWWWWWWWWWWWaaaaaaaaaaalllllllllllllllllllllllllllllllllll
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -ggdb")


#Déclaration de l'exécutable

add_executable(

        main

        src/ia.h
        src/ia.c

        src/parameters.h

        src/board.h
        src/board.c

        src/player.h

        src/parameters.h

        src/main.c

)