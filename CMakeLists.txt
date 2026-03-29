cmake_minimum_required(VERSION 3.10)
project(AventuriersRail)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(headers)

set(SOURCES
    cpp/Couleur.cpp
    cpp/Ville.cpp
    cpp/CarteTrain.cpp
    cpp/Route.cpp
    cpp/Ticket.cpp
    cpp/Joueur.cpp
    cpp/Plateau.cpp
    cpp/Jeu.cpp
    main.cpp
)

add_executable(aventuriers ${SOURCES})

configure_file(src/map.csv ${CMAKE_BINARY_DIR}/src/map.csv COPYONLY)
configure_file(src/ticket.csv ${CMAKE_BINARY_DIR}/src/ticket.csv COPYONLY)

# ─── Google Test ────────────────────────────────────────────────────────────

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES
    cpp/Couleur.cpp
    cpp/Ville.cpp
    cpp/CarteTrain.cpp
    cpp/Route.cpp
    cpp/Ticket.cpp
    cpp/Joueur.cpp
    cpp/Plateau.cpp
    cpp/Jeu.cpp
    tests/tests.cpp
)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)
