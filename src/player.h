#include "TileMap.h"
#include "Walkable.h"
class player : public Walkable
{
  public:
    player();

    void move(const float& dt, sf::Event& event);   // Poruszanie si i skakanie

    void wallCollision() final;                            // Kollizja dla ekranu
    void objectCollision(sf::RectangleShape wall) final;   // Kolizja wobec jednego obiektu
    void objectCollisionToTileMap(TileMap* map);           // Kolizcja wobec caej TileMapy
    void physics() final;                                  // Grawitacja postaci

    void didLavaTouched(sf::Vector2f lavaPos);   // Czy gracz yje/dotkn lawy?
    bool getLavaTouched();                       // Zwraca informacje o mierci
    void undoDeath(bool death);

    void moveArm();                            // Ruch rki, kilofa wraz z postaci
    void walkingAnimation(const float& dt);    // Animacja poruszania si
    bool death(const float& dt, bool death);   // Animacja mierci

    void setPosition(sf::Vector2f entityPos) final;   // Ustawianie pozycji gracza
    void setPositionDefault() final;                  // Ustawianie startowej pozycjia gracza
    void setPickaxe(unsigned int difficulty);         // Ustawianie kilofa wraz z poziomem trudnoci

    sf::Vector2f getPosition();   // Uzyskanie pozycji postaci
    sf::FloatRect getBounds();    // Uzyskanie wymiarw postaci

    void draw(sf::RenderWindow& window) final;   // rysowanie gracza

  private:
    // Tekstury, Sprite oraz wymiary gracza, rki i kilofa
    std::unique_ptr<sf::Sprite> gracz;
    std::unique_ptr<sf::Sprite> pickaxeArm;
    std::unique_ptr<sf::Sprite> pickaxe;

    std::unique_ptr<sf::Texture> tekstura;
    std::unique_ptr<sf::Texture> pickaxeTexture;

    sf::RectangleShape hitbox;   // hitbox postaci

    sf::FloatRect nextPos;
    sf::IntRect rectGraczSprite;
    sf::IntRect rectArmSprite;
    sf::IntRect rectDiamondPickaxeSprite, rectIronPickaxeSprite, rectStonePickaxeSprite;

    // Zmienne poruszania si gracza
    static constexpr float gravity = 0.1f;
    static constexpr int movementspeed = 200;
    float elapsedJump;
    sf::Vector2f velocity;

    sf::Vector2i playerPos;                 // pozycja gracza
    static constexpr float gridsize = 60;   // wielko siatki
    float dtime;                            // delta time

    bool lavaTouched;   // Czy gracz zyje
    bool isJumping;     // Czy gracz skacze
};
