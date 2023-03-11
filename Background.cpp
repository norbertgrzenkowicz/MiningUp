#include "Background.h"

Background::Background(sf::Vector2u window)
{
	if (!backgroundTexture.loadFromFile("textures/textureBackground.jpg"))
		std::cout<<"Nie zaladowano tekstury";
	
	background = new sf::RectangleShape;
	gameBackground = new sf::Sprite;
	gameOutline = new sf::RectangleShape;

	//Inicjalizacja ta szarego
	sf::Color backgroundColor(50, 50, 50);
	background->setFillColor(backgroundColor);
	background->setSize(sf::Vector2f(window.x, window.y));
	background->setPosition(sf::Vector2f(0.f, 0.f));


	//Inicjalizacja elementw rodowiska gracza
	gameBackground->setTexture(backgroundTexture);
	gameBackground->setPosition(sf::Vector2f(360.f, 0.f));
	gameBackground->setScale(4.f, 4.f);

	gameOutline->setFillColor(sf::Color::Transparent);
	gameOutline->setOutlineColor(sf::Color::Black);
	gameOutline->setSize(sf::Vector2f(1080.f, 1080.f));
	gameOutline->setOutlineThickness(2.f);
	gameOutline->setPosition(360.f, 0.f);
}

Background::~Background()
{
	delete gameOutline, gameBackground, background;
}

void Background::drawBackground(sf::RenderWindow& window)
{
	window.draw(*background);
}

void Background::draw(sf::RenderWindow& window)
{
	window.draw(*background);
	window.draw(*gameOutline);
	window.draw(*gameBackground);
}
