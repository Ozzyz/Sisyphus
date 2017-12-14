project(Sisyphus)

add_library(Sisyphus
        board.cpp
        evaluation.cpp
        fen.cpp
        main.cpp
        move.cpp
        utils.cpp
        search.cpp search.h evaluation.h)