cmake_minimum_required(VERSION 3.20)
project("we_do_be_learning")

SET(SOURCE_FILES
    src/Background.h
    src/Background.cpp
    src/Buttons.h
    src/Buttons.cpp
    src/Camera.h
    src/Camera.cpp
    src/Game.h
    src/Game.cpp
    src/Lava.h
    src/Lava.cpp
    src/main.cpp
    src/Menu.cpp
    src/Menu.h
    src/Myszka.cpp
    src/Myszka.h
    src/player.cpp
    src/player.h
    src/TileMap.cpp
    src/TileMap.h
    src/UserInterface.cpp
    src/UserInterface.h
    src/Entity.h
    src/Positionable.h
    )

    find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
    
    add_executable(we_do_be_learning ${SOURCE_FILES})
    target_link_libraries(we_do_be_learning sfml-graphics sfml-audio)