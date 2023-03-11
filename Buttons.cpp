#include "Buttons.h"

Buttons::Buttons()
{
}
Buttons::Buttons(int whichButton, sf::RenderWindow& window)
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

	if (!font.loadFromFile("czcionka.ttf"))
		throw std::invalid_argument("czcionka niezaladowana");

	switch (whichButton)
	{
		case 0: //Przycisk powrotu do gry
			stopTexture.loadFromFile("textures/buttons/stopbutton.png");
			button.setPosition(1660,0);
			button.setSize(sf::Vector2f(50, 50));
			button.setTexture(&stopTexture);
			break;

		case 1: //Przycisk odnowienia gry
			backtogameTexture.loadFromFile("textures/buttons/backtogameButton.png");
			set_text2("Wznow gre");

			set_button(sf::Color::Transparent, sf::Color::White, 2.f, sf::Vector2f(65 + tekst.getGlobalBounds().width , 50), sf::Vector2f((window.getSize().x / 2) - ((65+ tekstBounds.width) / 2), window.getSize().y / 5), sf::Vector2f(button.getPosition().x + 55, window.getSize().y / 5 + (button.getGlobalBounds().height - tekstBounds.height) / 4));

			buttonSprite.setTexture(backtogameTexture);
			buttonSprite.setPosition(button.getPosition());
			break;

		case 2: //Przycisk powrotu do menu gwnego
			renewTexture.loadFromFile("textures/buttons/renewButton.png");
			set_text2("Powtorz gre");

			set_button(sf::Color::Transparent, sf::Color::White, 2.f, sf::Vector2f(65 + tekst.getGlobalBounds().width, 50), sf::Vector2f((window.getSize().x / 2) - ((65 + tekstBounds.width) / 2), window.getSize().y / 2.5), sf::Vector2f(button.getPosition().x + 55, window.getSize().y / 2.5 + (button.getGlobalBounds().height - tekstBounds.height)/4));

			buttonSprite.setTexture(renewTexture);
			buttonSprite.setPosition(button.getPosition());
			break;

		case 3: //Przycisk powrotu do menu gwnego
			backtomenuTexture.loadFromFile("textures/buttons/backtomenuButton.png");
			set_text2("Wyjdz do menu glownego");

			set_button(sf::Color::Transparent, sf::Color::White, 2.f, sf::Vector2f(65 + tekstBounds.width, 50), sf::Vector2f(window.getSize().x / 2 - ((65 + tekstBounds.width) / 2), window.getSize().y / 1.66), sf::Vector2f(button.getPosition().x +55, window.getSize().y / 1.66 + (button.getGlobalBounds().height - tekstBounds.height) / 4));

			buttonSprite.setTexture(backtomenuTexture);
			buttonSprite.setPosition(button.getPosition());
			break;

		case 4:	//Przycisk powrotu do menu gwnego po mierci
			set_text2("Wyjdz do menu");
			set_button(sf::Color::Transparent, sf::Color::White, 2.f, sf::Vector2f(tekstBounds.width + 56, tekstBounds.height + 50), sf::Vector2f(window.getSize().x / 2 - ((button.getSize().x + tekstBounds.width) / 2), window.getSize().y * 0.50f), sf::Vector2f(button.getPosition().x + 55, button.getPosition().y + 25));
			break;

		case 5: //Przycisk wyboru wyczenia gry
			set_text2("Tak");

			set_button(sf::Color::Transparent, sf::Color::White, 2.f, sf::Vector2f(tekstBounds.width + 100, tekstBounds.height + 60), sf::Vector2f(window.getSize().x / 2 - button.getGlobalBounds().width * 1.5, window.getSize().y * 0.50f), sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - tekst.getGlobalBounds().width / 2, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - tekst.getGlobalBounds().height / 2 - 10));
			break;

		case 6: //Przycisk powrotu do gry w menu wyboru zakoczenia gry
			set_text2("Nie");

			set_button(sf::Color::Transparent, sf::Color::White, 2.f, sf::Vector2f(tekstBounds.width + 100, tekstBounds.height + 60), sf::Vector2f(window.getSize().x / 2 + button.getGlobalBounds().width / 2, window.getSize().y * 0.50f), sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - tekst.getGlobalBounds().width / 2, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - tekst.getGlobalBounds().height / 2 - 10));
			break;

		case 7:
			pickaxeT.loadFromFile("textures/pickaxes.png");
			set_text2("Latwy");

			button.setTexture(&pickaxeT);
			set_button(sf::Color::Transparent, sf::Color::White, 2.f, sf::Vector2f(window.getSize().x / 5, window.getSize().y / 2), sf::Vector2f(window.getSize().x / 10, window.getSize().y / 4), sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width/2 - tekst.getGlobalBounds().width/2, button.getGlobalBounds().top + button.getGlobalBounds().height + 10));
			
			set_pickaxe(sf::IntRect(0, 0, 14, 14), sf::Vector2f(window.getSize().x / 5 / 20, window.getSize().y / 2 / 20), sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - pickaxe.getLocalBounds().width / 2 * pickaxe.getScale().x, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - pickaxe.getLocalBounds().height / 2 * pickaxe.getScale().y))
			break;

		case 8: //Przycisk redniego poziomu trudnoci
			pickaxeT.loadFromFile("textures/pickaxes.png");
			set_text2("Sredni");

			button.setTexture(&pickaxeT);
			set_button(sf::Color::Transparent, sf::Color::White, 2.f, sf::Vector2f(window.getSize().x / 5, window.getSize().y / 2), sf::Vector2f(window.getSize().x / 10 * 4, window.getSize().y / 4), sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - tekst.getGlobalBounds().width / 2, button.getGlobalBounds().top + button.getGlobalBounds().height + 10));

			set_pickaxe(sf::IntRect(14, 0, 14, 14), sf::Vector2f(window.getSize().x / 5 / 20, window.getSize().y / 2 / 20), sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - pickaxe.getLocalBounds().width / 2 * pickaxe.getScale().x, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - pickaxe.getLocalBounds().height / 2 * pickaxe.getScale().y))
			break;

		case 9: //Przycisk trudnego poziomu trudnoci
			pickaxeT.loadFromFile("textures/pickaxes.png");
			set_text2("Trudny");

			set_button(sf::Color::Transparent, sf::Color::White, 2.f, sf::Vector2f(window.getSize().x / 5, window.getSize().y / 2), sf::Vector2f(window.getSize().x / 10 * 7, window.getSize().y / 4), sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - tekst.getGlobalBounds().width / 2, button.getGlobalBounds().top + button.getGlobalBounds().height + 10));

			set_pickaxe(sf::IntRect(28, 0, 14, 14), sf::Vector2f(window.getSize().x / 5 / 20, window.getSize().y / 2 / 20), sf::Vector2f(button.getGlobalBounds().left + button.getGlobalBounds().width / 2 - pickaxe.getLocalBounds().width / 2 * pickaxe.getScale().x, button.getGlobalBounds().top + button.getGlobalBounds().height / 2 - pickaxe.getLocalBounds().height / 2 * pickaxe.getScale().y))
			break;

	}
}

bool Buttons::isClicked(sf::Event &event, sf::RenderWindow& window)
{
	//Dynamiczna inicjalizacja Pooenia przycisku oraz jego wymiarw
	tekstBounds = tekst.getGlobalBounds();
	buttonBounds = button.getGlobalBounds();
	buttonBounds.width += tekstBounds.width;
	buttonPos = button.getPosition();

	//Inicjalizacja pozycji myszki
	mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (mousePos.x >= buttonPos.x
	&& mousePos.x <= buttonPos.x + buttonBounds.width + tekstBounds.width
	&& mousePos.y >= buttonPos.y 
	&& mousePos.y <= buttonPos.y + buttonBounds.height)				//Myszka wwntrz przycisku
	{
		sf::Vector2f obramowaniePos = button.getPosition();
		obramowanie.setPosition(sf::Vector2f(obramowaniePos.x, obramowaniePos.y));
		obramowanie.setSize(sf::Vector2f(button.getSize().x, button.getSize().y));
		obramowanie.setFillColor(sf::Color(0, 0, 0, 128));

		tekst.setFillColor(sf::Color(77, 230, 225));
		window.draw(obramowanie);									//Rysowanie obramowania na najechanym przycisku
	}

	if (mousePos.x >= buttonPos.x &&
		mousePos.x <= buttonPos.x + buttonBounds.width
		&& mousePos.y >= buttonPos.y
		&& mousePos.y <= buttonPos.y + buttonBounds.height
		&& event.key.code == sf::Mouse::Left
		)
	{
		return true;												//Przy nacisnieciu LPM metoda zwrci warto true
	}
	tekst.setFillColor(sf::Color::White);

	return false;
}

void Buttons::draw(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(tekst);
	window.draw(buttonSprite);
}

void Buttons::drawSprites(sf::RenderWindow& window)
{
	window.draw(pickaxe);
}
