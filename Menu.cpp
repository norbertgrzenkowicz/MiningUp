#include "Menu.h"



Menu::Menu() :
 loadGame(false),
	game_start(false),
	menu_start(true),
	newGame(false),
	choose_difficulty(false),
	playersChart(false),
	selectedMenuitem(0)
{
}

Menu::Menu(float width, float height) :
	//Inicjalizacja pomocniczych stanow gry
	tytul(),
	loadGame(false),
	game_start(false),
	menu_start(true),
	newGame(false),
	choose_difficulty(false),
	playersChart(false),
	selectedMenuitem(0)
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

	set_text(tytul, sf::Color(77, 230, 225), "MiningUp!", 60, width / 2 - tytul.getGlobalBounds().width/2, 50);


	//Inicjalizacja polozenia elementow oraz ich wlasciwosci
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		menu[i].setFont(font);
		if (i == 0)
			menu[i].setFillColor(sf::Color(77, 230, 225));
		else
			menu[i].setFillColor(sf::Color::White);
		menu[i].setString(h[i]);
		menu[i].setPosition(sf::Vector2f(width / 2 - menu[i].getGlobalBounds().width/2, 100 + tytul.getGlobalBounds().height + height / (MAX_ITEMS + 2) * (i + 1)));
	}
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
	window.draw(tytul);
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

void Menu::set_menu_start(bool menu_start)
{
	this->menu_start = menu_start;
}

bool Menu::get_menu_start()
{
	return menu_start;
}

void Menu::set_newGame(bool newGame)
{
	this->newGame = newGame;
}

bool Menu::get_newGame()
{
	return newGame;
}

void Menu::set_game_start(bool game_start)
{
	this->game_start = game_start;
}

bool Menu::get_game_start()
{
	return game_start;
}


void Menu::set_loadGame(bool loadGame)
{
	this->loadGame = loadGame;
}

bool Menu::get_loadGame()
{
	return loadGame;
}

void Menu::set_choose_difficulty(bool choose_difficulty)
{
	this->choose_difficulty = choose_difficulty;
}

bool Menu::get_choose_difficulty()
{
	return choose_difficulty;
}

void Menu::set_playersChart(bool playersChart)
{
	this->playersChart = playersChart;
}

bool Menu::get_playersChart()
{
	return playersChart;
}
