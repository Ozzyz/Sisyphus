

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runSisyphusTests
        fentest.cpp
        boardtest.cpp
        board_attack_test.cpp)

target_link_libraries(runSisyphusTests gtest gtest_main)
target_link_libraries(runSisyphusTests Sisyphus)