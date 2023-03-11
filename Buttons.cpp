#include "Buttons.h"

Buttons::Buttons()
{
}
Buttons::Buttons(int whichButton, sf::RenderWindow& window)
	:
	obramowanie()

{
	//whichButton - Wykorzystanie przycisku
	// 0 - Przycisk stop
	// 1 - Przycisk powrotu do gry
	// 2 - Przycisk odnowienia gry
	// 3 - Przycisk powrotu do menu gwnego
	// 4 - Przycisk powrotu do menu gwnego po mierci
	// 5 - Przycisk wyboru wyczenia gry
	// 6 - Przycisk powrotu do gry w menu wyboru zakoczenia gry
	// 7 - Przycisk atwego poziomu trudnoci
	// 8 - Przycisk redniego poziomu trudnoci
	// 9 - Przycisk trudnego poziomu trudnoci

	// button = new sf::RectangleShape;
	// obramowanie = new sf::RectangleShape;
	buttonBounds = new sf::FloatRect;
	buttonSprite = new sf::Sprite;
	tekst = new sf::Text;
	// tekstBounds = new sf::FloatRect;

	if (!font.loadFromFile("czcionka.ttf"))
	{
		std::cout << "czcionka niezaladowana";
	}

	if (whichButton == 0)	//Przycisk stop
	{
		stopTexture.loadFromFile("textures/buttons/stopbutton.png");
		button.setPosition(1660,0);
		button.setSize(sf::Vector2f(50, 50));
		button.setTexture(&stopTexture);
	}
	
	else if (whichButton == 1) //Przycisk powrotu do gry
	{
		backtogameTexture.loadFromFile("textures/buttons/backtogameButton.png");
		tresc = "Wznow gre";
		tekst->setFont(font);
		tekst->setFillColor(sf::Color::White);
		tekst->setString(tresc);
		tekstBounds = tekst->getGlobalBounds();

		button.setFillColor(sf::Color::Transparent);
		button.setOutlineColor(sf::Color::White);
		button.setOutlineThickness(2.f);
		button.setSize(sf::Vector2f(65 + tekst->getGlobalBounds().width , 50));
		button.setPosition(sf::Vector2f((window.getSize().x / 2) - ((65+ tekstBounds.width) / 2), window.getSize().y / 5));
		buttonSprite->setTexture(backtogameTexture);
		buttonSprite->setPosition(button.getPosition());
		
		tekst->setPosition(sf::Vector2f(button.getPosition().x + 55, window.getSize().y / 5 + (button.getGlobalBounds().height - tekstBounds.height) / 4));
	}

	else if (whichButton == 2) //Przycisk odnowienia gry
	{

		renewTexture.loadFromFile("textures/buttons/renewButton.png");
		tresc = "Powtorz gre";
		tekst->setFont(font);
		tekst->setFillColor(sf::Color::White);
		tekst->setString(tresc);
		tekstBounds = tekst->getGlobalBounds();

		button.setFillColor(sf::Color::Transparent);
		button.setOutlineColor(sf::Color::White);
		button.setOutlineThickness(2.f);
		button.setSize(sf::Vector2f(65 + tekst->getGlobalBounds().width, 50));
		button.setPosition(sf::Vector2f((window.getSize().x / 2) - ((65 + tekstBounds.width) / 2), window.getSize().y / 2.5));
		buttonSprite->setTexture(renewTexture);
		buttonSprite->setPosition(button.getPosition());
		
		tekst->setPosition(sf::Vector2f(button.getPosition().x + 55, window.getSize().y / 2.5 + (button.getGlobalBounds().height - tekstBounds.height)/4));
	}
	else if (whichButton == 3) //Przycisk powrotu do menu gwnego
	{

		backtomenuTexture.loadFromFile("textures/buttons/backtomenuButton.png");
		tresc = "Wyjdz do menu glownego";

		tekst->setFont(font);
		tekst->setFillColor(sf::Color::White);
		tekst->setString(tresc);
		tekstBounds = tekst->getGlobalBounds();

		button.setFillColor(sf::Color::Transparent);
		button.setOutlineColor(sf::Color::White);
		button.setOutlineThickness(2.f);
		button.setSize(sf::Vector2f(65 + tekstBounds.width, 50));
		button.setPosition(window.getSize().x / 2 - ((65 + tekstBounds.width) / 2), window.getSize().y / 1.66);
		buttonSprite->setTexture(backtomenuTexture);
		buttonSprite->setPosition(button.getPosition());

		tekst->setPosition(sf::Vector2f(button.getPosition().x +55, window.getSize().y / 1.66 + (button.getGlobalBounds().height - tekstBounds.height) / 4));
	}

	else if (whichButton == 4)	//Przycisk powrotu do menu gwnego po mierci
	{
		tresc = "Wyjdz do menu";

		tekst->setFont(font);
		tekst->setFillColor(sf::Color::White);
		tekst->setString(tresc);
		tekstBounds = tekst->getGlobalBounds();
		button.setFillColor(sf::Color::Transparent);
		button.setOutlineColor(sf::Color::White);
		button.setOutlineThickness(2.f);
		button.setSize(sf::Vector2f(tekstBounds.width + 56, tekstBounds.height + 50));
		button.setPosition(sf::Vector2f(window.getSize().x / 2 - ((button.getSize().x + tekstBounds.width) / 2), window.getSize().y * 0.50f));
		tekst->setPosition(sf::Vector2f(button.getPosition().x + 55, button.getPosition().y + 25));
	}
	else if (whichButton == 5)	//Przycisk wyboru wyczenia gry
	{
		tresc = "Tak";

		tekst->setFont(font);
		tekst->setFillColor(sf::Color::White);
		tekst->setCharacterSize(30.f);
		tekst->setString(tresc);
		tekstBounds = tekst->getGlobalBounds();

		button.setFillColor(sf::Color::Transparent);
		button.setOutlineColor(sf::Color::White);
		button.setOutlineThickness(2.f);
		button.setSize(sf::Vector2f(tekstBounds.width + 100, tekstBounds.height + 60));
		button.setPosition(sf::Vector2f(window.getSize().x / 2 - button.getGlobalBounds().width * 1.5, window.getSize().y * 0.50f));
		tekst->setPosition(sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - tekst->getGlobalBounds().width / 2, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - tekst->getGlobalBounds().height / 2 - 10));
	}
	else if (whichButton == 6)	//Przycisk powrotu do gry w menu wyboru zakoczenia gry
	{
		tresc = "Nie";

		tekst->setFont(font);
		tekst->setFillColor(sf::Color::White);
		tekst->setCharacterSize(30.f);
		tekst->setString(tresc);
		tekstBounds = tekst->getGlobalBounds();
		button.setFillColor(sf::Color::Transparent);
		button.setOutlineColor(sf::Color::White);
		button.setOutlineThickness(2.f);
		button.setSize(sf::Vector2f(tekstBounds.width + 100, tekstBounds.height + 60));
		button.setPosition(sf::Vector2f(window.getSize().x / 2 + button.getGlobalBounds().width / 2, window.getSize().y * 0.50f));
		tekst->setPosition(sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - tekst->getGlobalBounds().width / 2, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - tekst->getGlobalBounds().height / 2 - 10));
	}
	else if (whichButton == 7)	//Przycisk atwego poziomu trudnoci
	{
	tresc = "Latwy";

	pickaxeT.loadFromFile("textures/pickaxes.png");
	tekst->setFont(font);
	tekst->setCharacterSize(30);
	tekst->setFillColor(sf::Color::White);
	tekst->setString(tresc);

	button.setTexture(&pickaxeT);
	button.setFillColor(sf::Color::Transparent);
	button.setOutlineColor(sf::Color::White);
	button.setOutlineThickness(2.f);
	button.setSize(sf::Vector2f(window.getSize().x / 5, window.getSize().y / 2));
	button.setPosition(sf::Vector2f(window.getSize().x / 10, window.getSize().y / 4));
	tekst->setPosition(sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width/2 - tekst->getGlobalBounds().width/2, button.getGlobalBounds().top + button.getGlobalBounds().height + 10));
	
	pickaxe.setTexture(pickaxeT);
	pickaxe.setTextureRect(sf::IntRect(0, 0, 14, 14));
	pickaxe.setScale(window.getSize().x / 5 / 20, window.getSize().y / 2 / 20);
	pickaxe.setPosition(sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - pickaxe.getLocalBounds().width / 2 * pickaxe.getScale().x, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - pickaxe.getLocalBounds().height / 2 * pickaxe.getScale().y));
	}
	else if (whichButton == 8)	//Przycisk redniego poziomu trudnoci
	{
	tresc = "Sredni";

	pickaxeT.loadFromFile("textures/pickaxes.png");

	tekst->setFont(font);
	tekst->setFillColor(sf::Color::White);
	tekst->setString(tresc);

	button.setTexture(&pickaxeT);
	button.setFillColor(sf::Color::Transparent);
	button.setOutlineColor(sf::Color::White);
	button.setOutlineThickness(2.f);
	button.setSize(sf::Vector2f(window.getSize().x / 5, window.getSize().y / 2));
	button.setPosition(sf::Vector2f(window.getSize().x / 10 * 4, window.getSize().y / 4));
	tekst->setPosition(sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - tekst->getGlobalBounds().width / 2, button.getGlobalBounds().top + button.getGlobalBounds().height + 10));
	
	pickaxe.setTexture(pickaxeT);
	pickaxe.setTextureRect(sf::IntRect(14, 0, 14, 14));
	pickaxe.setScale(window.getSize().x / 5 / 20, window.getSize().y / 2 / 20);
	pickaxe.setPosition(sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - pickaxe.getLocalBounds().width / 2 * pickaxe.getScale().x, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - pickaxe.getLocalBounds().height / 2 * pickaxe.getScale().y));
}
	else if (whichButton == 9)	//Przycisk trudnego poziomu trudnoci
	{
	tresc = "Trudny";

	pickaxeT.loadFromFile("textures/pickaxes.png");

	tekst->setFont(font);
	tekst->setFillColor(sf::Color::White);
	tekst->setString(tresc);

	button.setFillColor(sf::Color::Transparent);
	button.setOutlineColor(sf::Color::White);
	button.setOutlineThickness(2.f);
	button.setSize(sf::Vector2f(window.getSize().x / 5, window.getSize().y / 2));
	button.setPosition(sf::Vector2f(window.getSize().x / 10 * 7, window.getSize().y / 4));
	tekst->setPosition(sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - tekst->getGlobalBounds().width / 2, button.getGlobalBounds().top + button.getGlobalBounds().height + 10));
	
	pickaxe.setTexture(pickaxeT);
	pickaxe.setTextureRect(sf::IntRect(28, 0, 14, 14));
	pickaxe.setScale(window.getSize().x / 5 / 20, window.getSize().y / 2 / 20);
	pickaxe.setPosition(sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - pickaxe.getLocalBounds().width / 2 * pickaxe.getScale().x, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - pickaxe.getLocalBounds().height / 2 * pickaxe.getScale().y));
}
}
Buttons::~Buttons()
{
	delete buttonBounds, tekst, tekstBounds, buttonSprite;
}

bool Buttons::isClicked(sf::Event &event, sf::RenderWindow& window)
{
	//Dynamiczna inicjalizacja Pooenia przycisku oraz jego wymiarw
	tekstBounds = tekst->getGlobalBounds();
	*buttonBounds = button.getGlobalBounds();
	buttonBounds->width += tekstBounds.width;
	buttonPos = button.getPosition();

	//Inicjalizacja pozycji myszki
	mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (mousePos.x >= buttonPos.x
	&& mousePos.x <= buttonPos.x + buttonBounds->width + tekstBounds.width
	&& mousePos.y >= buttonPos.y 
	&& mousePos.y <= buttonPos.y + buttonBounds->height)				//Myszka wwntrz przycisku
	{
		sf::Vector2f obramowaniePos = button.getPosition();
		obramowanie.setPosition(sf::Vector2f(obramowaniePos.x, obramowaniePos.y));
		obramowanie.setSize(sf::Vector2f(button.getSize().x, button.getSize().y));
		obramowanie.setFillColor(sf::Color(0, 0, 0, 128));

		tekst->setFillColor(sf::Color(77, 230, 225));
		window.draw(obramowanie);									//Rysowanie obramowania na najechanym przycisku
	}

	if (mousePos.x >= buttonPos.x &&
		mousePos.x <= buttonPos.x + buttonBounds->width
		&& mousePos.y >= buttonPos.y
		&& mousePos.y <= buttonPos.y + buttonBounds->height
		&& event.key.code == sf::Mouse::Left
		)
	{
		return true;												//Przy nacisnieciu LPM metoda zwrci warto true
	}

	tekst->setFillColor(sf::Color::White);

	return false;
}

void Buttons::draw(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(*tekst);
	window.draw(*buttonSprite);
}

void Buttons::drawSprites(sf::RenderWindow& window)
{
	window.draw(pickaxe);
}
