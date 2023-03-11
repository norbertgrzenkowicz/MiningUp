Game MiningUp!

A 2D game created in C++/SFML environment recently code got updated.
Game was supposed to be learning canvas for OOP and it did its purpose :)

It implements menu, game saving, movement, animations, object collision, randomly generated tiles of diamonds/iron/stone, moving object. 

Thats the view!

<img width="618" alt="image" src="https://user-images.githubusercontent.com/79313551/224508536-d5794670-4a95-438f-95cc-8feb3d6f5a3f.png">

POLISH FROM NOW ON

ABY WŁĄCZYĆ GRĘ, potrzebne są pliki .dll biblioteki SFML w folderze z kodem i zainstalowanie SFML do IDE.

Prosta gra powstała na potrzeby zdania przedmiotu na studia. Została napisana w całości w c++ w MS Visual Studio wykorzystując bibliotekę SFML.
Gra polega na zebraniu jak największej ilości surowców podczas ciągłego podnoszenia się poziomu lawy, której kontakt wraz z graczem kończy grę.
Następnie wyniki są zapisane i wyświetlane w menu gry.

Najważniejszymi elementami rozgrywki jest kolizja obiektów wraz z graczem, niszczenie kafli oraz skromna fizyka.
Cel gry oraz keybindy są dostępne pod klawiszem F1 podczas rozgrywki.
Do elementów User Interface należą menu główne/wyników/pauzy gry/końca gry/helpmenu oraz możliwość zapisania i wczytania gry(gra wykonuje autosave przy wyłączeniu gry).

Elementy graficzne były wykonywane na pixilart.com przy kooperacji z Photoshopem. 
Niestety brak zdolności artystycznych i czasu przeszkodził w budowie imersyjnego klimatu gry.

--------Opis klas--------

Game
  Główna pętla gry, konstruktory klas oraz wszystkie funkcje takie jak UI, zapisywanie podejść odbywają się w tej klasie. Konstruktor znajduje się w main.cpp, który uruchamia grę poprzez Game.run();

UserInterface
  Klasa zawiera konstruktory klasy Menu oraz Myszka. Klasa służy oczywiście jako interfejs użytkownika.

player
  Tworzenie oraz obsługa ruchu postaci grywalnej.
  Kolizja obiektów gracza wokól elementów(kafli) gry.
  
TileMap
  Tworzenie losowe wszystkich kafli na początku gry oraz tworzenie kafli wraz z biegiem gry i usuwaniem kolejnych.
  Klasa również współgra z inputem gracza do niszczenia kafli.
  
Myszka
  Pozycjonowanie myszki na ekranie wraz z Tile Selectorem będącym wkaźnikiem obecnie najechanego kafla.

Buttons
  Klasa zawiera konstruktory wszystkich przycisków w grzę. Zależnie od sytuacji konstruktor stworzy jednego, chcianego kafla
 
Background
  Tworzy tło za graczem, które utrzymuje się na ekranie wraz z progresem w grze.

Camera
  Tworzy widok gry skierowanej na graczu. Kamera podąża za graczem w osi Y.

Lava
  Klasa tworzy i lawę, jej poruszanie się ku górze oraz tworzy powiększający się kwadrat będący zasłoną png lawy.

Menu
  Główne menu gry odpowiednie za włączenie zasaveowanej/nowej gry oraz wybrania takich okien jak tabela graczy oraz wybór trudności.

