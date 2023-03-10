#include "Menu.h"



Menu::Menu() :
 loadGame(false),
	game_start(false),
	menu_start(true),
	set_newGame(false),
	choose_difficulty(false),
	playersChart(false),
	selectedMenuitem(0)
{
}

Menu::Menu(float width, float height)
{

	if (!font.loadFromFile("czcionka.ttf"))
	{
		std::cout<< "czcionka niezaladowana";
	}

	//Zawartosc elementow menu glownego
	std::vector<std::string> h =
	{
		"New game",
		"Load game",
		"Players",
		"Quit"
	};

	//Inicjalizacja pomocniczych stanow gry
	loadGame = false;
	game_start = false;
	menu_start = true;
	set_newGame = false;
	choose_difficulty = false;
	playersChart = false;
	selectedMenuitem = 0;

	//Inicjalizacja tytulu
	tytul = new sf::Text;

	tytul->setFont(font);
	tytul->setString("The Dungeon");
	tytul->setFillColor(sf::Color(77, 230, 225));
	tytul->setCharacterSize(60);
	tytul->setPosition(width / 2 - tytul->getGlobalBounds().width/2, 50);

	//Inicjalizacja polozenia elementow oraz ich wlasciwosci
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		menu[i].setFont(font);
		if (i == 0)
			menu[i].setFillColor(sf::Color(77, 230, 225));
		else
			menu[i].setFillColor(sf::Color::White);
		menu[i].setString(h[i]);
		menu[i].setPosition(sf::Vector2f(width / 2 - menu[i].getGlobalBounds().width/2, 100 + tytul->getGlobalBounds().height + height / (MAX_ITEMS + 2) * (i + 1)));
	}
}

Menu::~Menu()
{
	delete tytul;
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
	window.draw(*tytul);
}

void Menu::MoveUp()
{
	if (selectedMenuitem - 1 >= 0)
	{
		menu[selectedMenuitem].setFillColor(sf::Color::White);
		selectedMenuitem--;
		menu[selectedMenuitem].setFillColor(sf::Color(77, 230, 225));
	}
}

void Menu::MoveDown()
{
	if (selectedMenuitem + 1 < MAX_ITEMS)
	{
		menu[selectedMenuitem].setFillColor(sf::Color::White);
		selectedMenuitem++;
		menu[selectedMenuitem].setFillColor(sf::Color(77, 230, 225));
	}
}

void Menu::moving(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
			this->MoveUp();
		if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			this->MoveDown();

		if (event.key.code == sf::Keyboard::Return)
		{
			if (this->get_SelectedItem() == 0)		//Przejscie do wyboru poziomu trudnoci
			{
				choose_difficulty = true;
				menu_start = false;
			}
			else if (this->get_SelectedItem() == 1) //Przejscie do adowania zapisanej gry
			{
				loadGame = true;
				menu_start = false;
			}
			else if (this->get_SelectedItem() == 2)	//Przejscie do menu statystyk graczy
			{
				playersChart = true;
				menu_start = false;
			}
			else if (this->get_SelectedItem() == MAX_ITEMS - 1) //Wyjscie z gry
				window.close();
		}
	}
	if (event.type == sf::Event::Closed)

		window.close();
}