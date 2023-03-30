#pragma once
#include "Background.h"

class Game
{
  public:
    Game();

    void run();                  // Metoda zawiera gwn ptle gry wraz z jej wszystkimi elementami
    void checkGameState();       // Sprawdza oraz zmienia stany gry
    void loadSavedGame();        // aduje gr
    void loadMenuAfterDeath();   // aduje menu po przegraniu gry

  private:
    sf::RenderWindow window;
    sf::Clock dtClock;
    float dt;
    // typ wyliczeniowy potrzebny do zmieniania stanu gry midzy menu, wybieraniem trudnosi, wynikw graczy oraz gry
    enum State
    {
        STATE_MENU,                 // menu
        STATE_CHOOSINGDIFFICULTY,   // wybieranie poziomu trudnoci gry
        STATE_PLAYERSCHART,         // Wyniki graczy
        STATE_GAME                  // gra
    };
    enum State state_;

    // Inicjalizacja klas
    std::unique_ptr<UserInterface> UI;    // Interfejs gracza
    std::unique_ptr<Camera> gameCamera;   // Kamera
    std::unique_ptr<player> gracz;        // Jednostka sterowalna
    std::unique_ptr<TileMap> mapa;        // Otoczenie gracza
    std::unique_ptr<Lava> lawa;
    std::unique_ptr<Background> tlo;   // Wczytywanie ta
};
