cmake_minimum_required(VERSION 3.20)
project("we_do_be_learning")

SET(SOURCE_FILES
    Background.h
    Background.cpp
    Buttons.h
    Buttons.cpp
    Camera.h
    Camera.cpp
    Game.h
    Game.cpp
    Lava.h
    Lava.cpp
    main.cpp
    Menu.cpp
    Menu.h
    Myszka.cpp
    Myszka.h
    player.cpp
    player.h
    TileMap.cpp
    TileMap.h
    UserInterface.cpp
    UserInterface.h
    )

    find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
    
    add_executable(we_do_be_learning ${SOURCE_FILES})
    target_link_libraries(we_do_be_learning sfml-graphics sfml-audio)