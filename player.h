#include "TileMap.h"
#include "Positionable.h"
class player : public Positionable
{
private:
	//Tekstury, Sprite oraz wymiary gracza, rki i kilofa
	sf::Sprite* gracz;
	sf::Sprite* pickaxeArm;
	sf::Sprite* pickaxe;

	sf::Texture tekstura;
	sf::Texture pickaxeTexture;
	
	sf::FloatRect nextPos;
	sf::IntRect rectGraczSprite;
	sf::IntRect rectArmSprite;
	sf::IntRect rectDiamondPickaxeSprite, rectIronPickaxeSprite, rectStonePickaxeSprite;

	//Zmienne poruszania si gracza
	float gravity;
	float movementspeed;
	float elapsedJump;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	sf::Vector2i playerPos; //pozycja gracza
	float gridsize = 60;	//wielko siatki
	float dtime;			//delta time
	
	bool lavaTouched;		//Czy gracz yje
	bool isJumping;			//Czy gracz skacze

	sf::RectangleShape hitbox;	//hitbox postaci
public:
	player();
	virtual ~player();

	void initVariables();													//Inicjalizacja postaci
	void initTexture();														//Inicjalizacja tekstur
	void move(const float& dt, sf::Event &event);							//Poruszanie si i skakanie
	void wallCollision();													//Kollizja dla ekranu
	void objectCollision(sf::RectangleShape wall);							//Kolizja wobec jednego obiektu
	void objectCollisionToTileMap(TileMap *map);							//Kolizcja wobec caej TileMapy
	void physics();															//Grawitacja postaci
	void didLavaTouched(sf::Vector2f lavaPos);								//Czy gracz yje/dotkn lawy?
	bool getLavaTouched();													//Zwraca informacje o mierci
	void moveArm();															//Ruch rki, kilofa wraz z postaci
	void walkingAnimation(const float& dt);									//Animacja poruszania si
	bool death(const float& dt, bool death);								//Animacja mierci
	void setPosition(sf::Vector2f entityPos);								//Ustawianie pozycji gracza
	void setPositionDefault() final;												//Ustawianie startowej pozycjia gracza
	void setPickaxe(unsigned int difficulty);								//Ustawianie kilofa wraz z poziomem trudnoci
	sf::Vector2f getPosition();												//Uzyskanie pozycji postaci
	sf::FloatRect getBounds();												//Uzyskanie wymiarw postaci
	int getGridPosY();														//Uzyskanie pozycji na osi Y dla siatki
	void draw(sf::RenderWindow& window);									//rysowanie gracza 
};
