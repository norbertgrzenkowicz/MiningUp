#include "Background.h"

Background::Background(sf::Vector2u window, std::string&& backgroundTexturePath) :
	background(),
	gameOutline(),
	backgroundTexture()
{
	if (!backgroundTexture.loadFromFile("textures/textureBackground.jpg"))
		std::cout<< "Nie zaladowano tekstury po sciezce" << backgroundTexturePath << std::endl;
	
	gameBackground = std::make_unique<sf::Sprite>();

	//Inicjalizacja ta szarego
	sf::Color backgroundColor(50, 50, 50);
	background.setFillColor(backgroundColor);
	background.setSize(sf::Vector2f(window.x, window.y));
	background.setPosition(sf::Vector2f(0.f, 0.f));

	//Inicjalizacja elementow srodowiska gracza
	gameBackground->setTexture(backgroundTexture);
	gameBackground->setScale(4.f, 4.f);
	gameBackground->setPosition({GAME_WINDOW_START, 0.f});

	gameOutline.setFillColor(sf::Color::Transparent);
	gameOutline.setOutlineColor(sf::Color::Black);
	std::cout << window.x << " " << window.y << std::endl;
	gameOutline.setSize(sf::Vector2f(window.y, window.y));
	gameOutline.setOutlineThickness(2.f);
	gameOutline.setPosition(GAME_WINDOW_START, 0.f);
}

void Background::drawBackground(sf::RenderWindow& window)
{
	window.draw(background);
}

void Background::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(gameOutline);
	window.draw(*gameBackground);
}
