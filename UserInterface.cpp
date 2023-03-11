#include "UserInterface.h"

UserInterface::UserInterface(sf::RenderWindow& window) :
	Pause(false),
	renew(false),
	helpMenuBool(false),
	isSaved(false),
	isLoaded(false),
	escape(false),
	diamonds(),
	iron(),
	difficultyText(),
	playerNumber(),
	naglowek(),
	kategorie(),
	helpText(),
	difficulty(0), //Inicjalizacja poziomu trudnoci
	escBack(),
	leave(),
	gameOver()
{
	 menu = std::make_unique<Menu>(window.getSize().x, window.getSize().y); 

	 if (!font.loadFromFile("czcionka.ttf"))
		throw std::invalid_argument("czcionka niezaladowana");

	 //Inicjalizacja sprite'a licznika surowcow
	 if (!countUIT.loadFromFile("textures/UI.jpg"))
		throw std::invalid_argument("Nieznaleziono textures/UI.jpg");

	 countUI.setTexture(countUIT);
	 countUI.setPosition(FULL_HD_WIDTH - 390, 85);

	przyciskStop = std::make_unique<Buttons>(0, window);
	przyciskBackToGame = std::make_unique<Buttons>(1, window);
	przyciskRenew = std::make_unique<Buttons>(2, window);
	przyciskBackToMenu = std::make_unique<Buttons>(3, window);
	endGameBackToMenu = std::make_unique<Buttons>(4, window);
	yesButton = std::make_unique<Buttons>(5, window);
	noButton = std::make_unique<Buttons>(6, window);
	easyButton = std::make_unique<Buttons>(7, window);
	mediumButton = std::make_unique<Buttons>(8, window);
	hardButton = std::make_unique<Buttons>(9, window);

	 //odczyt i zapis struktury graczy
	 this->loadPlayers();

	//Pomocnicza wiadomo o poruszaniu sie miedzy menu
	set_text(escBack, sf::Color::White, "Kliknij Escape, aby cofnac!", 30, 50.f, 50.f);
	//tekst konca gry
	set_text(gameOver, sf::Color::Red, "Koniec Gry!", 70, window.getSize().x / 2 - gameOver.getGlobalBounds().width / 2, window.getSize().y / 3);
	//Elementy menu statystyk graczy
	set_text(naglowek, diamondColor, "Wyniki graczy", 40, window.getSize().x / 2 - naglowek.getGlobalBounds().width / 2, window.getSize().y / 6);
	set_text(kategorie, sf::Color::White, "Gracz                    Diamenty          Zelazo          Poziom trudnosci", 35, 100, window.getSize().y / 6 * 1.5);
	//Tekst w helpMenu
	set_text(helpText, sf::Color::White,
	"Celem gry jest uzbieranie jak najwiekszej ilosci diamentow oraz zelaza \n podczas kopania do gory w celu unikniecia smierci w kontakcie z wynurzajaca sie lawa. \n Nalezy zwracac uwage, aby droga ucieczki nie zostala zniszczona \n\n\n Sterowanie postacia: \n W oraz Spacja - Skok \n A lub D - odpowiednio ruch lewo badz w prawo \n F4 - zapisanie obecnego stanu gry \n \n Przytrzymujac LPM mozliwa jest destrukcja klockow. Czas zniszczenia klocka jest zalezny od jego typu. \n\n Aby wyjsc z Help Menu nalezy kliknac F2",
	20, window.getSize().x / 2 - helpText.getGlobalBounds().width / 2, window.getSize().y / 8);
	helpText.setPosition(window.getSize().x / 2 - helpText.getGlobalBounds().width / 2, window.getSize().y / 8);
	//Zapytanie wyjscia z gry
	set_text(leave, sf::Color::White, "Czy chcesz wyjsc z gry?", 40, window.getSize().x / 2 - leave.getGlobalBounds().width / 2, window.getSize().y / 3);
	
	//Tekst diamentow oraz zelaza wywietlanych w trakcie gry
	set_number(playerNumber, sf::Color::White, 30);
	set_number(diamonds, sf::Color(77, 230, 225), 30);
	set_number(iron, sf::Color(178, 183, 185), 30);
	set_number(difficultyText, sf::Color::White, 30);	
}

void UserInterface::inGameUI(sf::Event& event, sf::RenderWindow& window, unsigned int diamondsCounted, unsigned int ironCounted)
{
	//dynamiczny odczyt zebranych diamentw i elaza
	std::stringstream ssDiamonds;
	std::stringstream ssIron;

	ssDiamonds << diamondsCounted;
	ssIron << ironCounted;
	std::string diamondsString = ssDiamonds.str();
	std::string ironString = ssIron.str();

	diamonds.setString(diamondsString);
	iron.setString(ironString);

	diamonds.setPosition(FULL_HD_WIDTH - 260, 100);
	iron.setPosition(FULL_HD_WIDTH - 260, 200);

	window.draw(countUI);

	if (przyciskStop->isClicked(event, window))
		Pause = true;

	if (Pause && helpMenuBool == false && escape == false)
	{
		this->putShadow(window);

		przyciskBackToGame->draw(window);
		przyciskRenew->draw(window);
		przyciskBackToMenu->draw(window);

		if (przyciskBackToGame->isClicked(event, window))
			Pause = false;

		else if (przyciskRenew->isClicked(event, window))
			this->set_renew(true);

		else if (przyciskBackToMenu->isClicked(event, window))
		{
			menu->set_menu_start(true);
			menu->set_game_start(false);
			Pause = false;
		}
	}

	this->helpMenu(event, window);
	this->leaveQuestion(event, window);

	przyciskStop->draw(window);
	window.draw(diamonds);
	window.draw(iron);

	//Zapytanie o wyjcie z gry
	this->leaveQuestion(event, window);
}

void UserInterface::helpMenu(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
		helpMenuBool = true;

	if (helpMenuBool)
	{
		this->putShadow(window);
		Pause = true;

		window.draw(helpText);
		
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
		{
			helpMenuBool = false;
			Pause = false;
		}
	}
}

bool UserInterface::endGameMenu(const bool isDead,sf::Event& event, sf::RenderWindow &window)
{
	if (isDead)
	{
		this->putShadow(window);
		window.draw(gameOver);
		endGameBackToMenu->draw(window);
		if (endGameBackToMenu->isClicked(event, window))
		{
			std::cout << "isclicked";
			return true;
		}
	}
	return false;
}

void UserInterface::playersScore(sf::Event& event, sf::RenderWindow& window)
{
	set_number(playerNumber, sf::Color::White, 30);

	std::string number;
	std::string diamondsS;
	std::string ironS;

	for (unsigned int i = 0; i < gracze.size(); i++)
	{
		std::stringstream ssDiamonds;
		std::stringstream ssIron;
		std::stringstream ssNumber;
		ssNumber << i + 1;
		ssDiamonds << gracze[i].diamondsCounted;
		ssIron << gracze[i].ironCounted;

		number = ssNumber.str();
		diamondsS = ssDiamonds.str();
		ironS = ssIron.str();

		diamonds.setString(diamondsS);
		iron.setString(ironS);

		if (gracze[i].difficulty == 1)
			difficultyText.setString("Latwy");

		else if (gracze[i].difficulty == 2)
			difficultyText.setString("Sredni");

		else if (gracze[i].difficulty == 3)
			difficultyText.setString("Trudny");

		playerNumber.setString(number);

		playerNumber.setPosition(150.f, window.getSize().y / 6 * 2 + window.getSize().y / 12 * i);
		diamonds.setPosition(700.f, window.getSize().y / 6 * 2 + window.getSize().y / 12 * i);
		iron.setPosition(1050.f, window.getSize().y / 6 * 2 + window.getSize().y / 12 * i);
		difficultyText.setPosition(1450.f, window.getSize().y / 6 * 2 + window.getSize().y / 12 * i);

		window.draw(playerNumber);
		window.draw(diamonds);
		window.draw(iron);
		window.draw(difficultyText);
	}
	window.draw(escBack);
	window.draw(naglowek);
	window.draw(kategorie);
}

void UserInterface::chooseDifficulty(sf::Event& event, sf::RenderWindow& window)
{
	if (easyButton->isClicked(event, window))
	{
		difficulty = 1;
		menu->set_newGame(true);
		menu->set_game_start(true);
		menu->set_choose_difficulty(false);
	}
	else if (mediumButton->isClicked(event, window))
	{
		difficulty = 2;
		menu->set_newGame(true);
		menu->set_game_start(true);
		menu->set_choose_difficulty(false);
	}
	else if (hardButton->isClicked(event, window))
	{
		difficulty = 3;
		menu->set_newGame(true);
		menu->set_game_start(true);
		menu->set_choose_difficulty(false);
	}
	easyButton->draw(window);
	easyButton->drawSprites(window);
	mediumButton->draw(window);
	mediumButton->drawSprites(window);
	hardButton->draw(window);
	hardButton->drawSprites(window);
	window.draw(escBack);
}

void UserInterface::save(sf::Vector2f&& playerPos, std::vector<std::vector<int>>&& tilemap, sf::Vector2f&& lavaPos, unsigned int diamondsCount, unsigned int ironCount)
{
	std::ofstream savefile;
	savefile.open("saves/save1.txt");
	if (savefile.is_open())
	{
		savefile << playerPos.x << "\n";
		savefile << playerPos.y << "\n";

		for (auto& tilerow : tilemap)
		{
			for (auto& tiles : tilerow)
				savefile << tiles<<" ";

			savefile << "\n";
		}
		savefile << lavaPos.x << "\n";
		savefile << lavaPos.y << "\n";
		savefile << diamondsCount <<"\n";
		savefile << ironCount <<"\n";
		savefile << difficulty;

		savefile.close();
	}
	this->savePlayers(diamondsCount, ironCount, difficulty);
	std::cout << "zapis wykonany";
}

void UserInterface::savePlayers(unsigned int diamondsCount, unsigned int ironCount, unsigned int difficulty)
{
		std::ofstream savePlayersfile;
		std::string line;

		if (gracze.size() < MAX_SAVES)
		{
			savePlayersfile.open("saves/players.txt", std::fstream::app);
			gracze.push_back(danegracza());
			gracze[gracze.size() - 1].diamondsCounted = diamondsCount;
			gracze[gracze.size() - 1].ironCounted = ironCount;
			gracze[gracze.size() - 1].difficulty = difficulty;

			if (savePlayersfile.is_open())
			{
				savePlayersfile << diamondsCount << " ";
				savePlayersfile << ironCount << " ";
				savePlayersfile << difficulty << "\n";
				savePlayersfile.close();
			}
		}
		else if (gracze.size() >= MAX_SAVES)
		{
			savePlayersfile.open("saves/players.txt");

			for (int i = MAX_SAVES - 2; i >= 0; i--)
			{
				int j = i + 1;
				gracze[j] = gracze[i];
			}
			gracze[0].diamondsCounted = diamondsCount;
			gracze[0].ironCounted = ironCount;
			gracze[0].difficulty = difficulty;

			for (auto& gracz : gracze)
			{
				savePlayersfile << gracz.diamondsCounted << " ";
				savePlayersfile << gracz.ironCounted << " ";
				savePlayersfile << gracz.difficulty;
				savePlayersfile << "\n";
			}
		}
}

void UserInterface::saveDead(unsigned int diamondsCount, unsigned int ironCount, unsigned int difficulty)
{
	if (!isSaved)
	{
		this->savePlayers(diamondsCount, ironCount, difficulty);
		isSaved = true;
	}
}

void UserInterface::loadGame()
{
		std::string lines[SAVE_FILE_LENGTH];
		std::ifstream savefile("saves/save1.txt");
		std::string line;
		int typy;
		unsigned int i = 0;

		if (savefile.is_open())
		{
			while (std::getline(savefile, line))
			{
				if (line.size() > 0)
					lines[i] = line;
				i++;
			}
			savefile.close();
		}
		else
		{
			std::cout << "plik zapisu nie zostal otwarty";
		}

		loadedGamerPos.x = std::stof(lines[0]);
		loadedGamerPos.y = std::stof(lines[1]);

		for (uint8_t i = 2; i <= SAVE_FILE_LENGTH - 6; i++)
		{
			std::vector<int> typy_kafli;
			std::stringstream kafleString(lines[i]);
			while (kafleString >> typy)
			{
				typy_kafli.push_back(typy);
			}
			loadedTypy_kafli.push_back(typy_kafli);
		}

		loadedLavaPos.x = std::stof(lines[SAVE_FILE_LENGTH -5]);
		loadedLavaPos.y = std::stof(lines[SAVE_FILE_LENGTH - 4]);
		loadedDiamonds = std::stoi(lines[SAVE_FILE_LENGTH - 3]);
		loadedIron = std::stoi(lines[SAVE_FILE_LENGTH - 2]);
		loadedDifficulty = std::stoi(lines[SAVE_FILE_LENGTH - 1]);


		menu->set_game_start(true);
		menu->set_menu_start(false);

}

void UserInterface::loadPlayers()
{
		std::fstream savePlayersfileReadingC("saves/players.txt", std::ios_base::in);
		std::fstream savePlayersfileReading("saves/players.txt", std::ios_base::in);
		std::string line;
		unsigned int j = 0;
		unsigned int lines = 0;
		unsigned int output[15];

		if (savePlayersfileReading.is_open())
		{
			while (std::getline(savePlayersfileReadingC, line))
			{
				lines++;
			}
			savePlayersfileReadingC.close();
		}

		if (savePlayersfileReading.is_open() && lines != 0)
		{
			for (unsigned int i = 0; i < lines; i++)
			{
				savePlayersfileReading >> output[j];
				savePlayersfileReading >> output[j + 1];
				savePlayersfileReading >> output[j + 2];


				gracze.push_back(danegracza());
				gracze[i].diamondsCounted = output[j];
				gracze[i].ironCounted = output[j + 1];
				gracze[i].difficulty = output[j + 2];

				j += 3;
			}
			savePlayersfileReading.close();
		}
}

void UserInterface::putShadow(sf::RenderWindow& window)
{
	static sf::RectangleShape menuShadow;
	menuShadow.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	menuShadow.setFillColor(sf::Color(0, 0, 0, 128));
	window.draw(menuShadow);
}

void UserInterface::leaveQuestion(sf::Event& event, sf::RenderWindow& window)
{
	if (escape)
	{
		this->putShadow(window);
		escape = true;
		Pause = true;
		if (yesButton->isClicked(event, window))
		{
			window.close();
		}
		else if (noButton->isClicked(event, window))
		{
			escape = false;
			Pause = false;
		}

		window.draw(leave);
		noButton->draw(window);
		yesButton->draw(window);
	}
}

void UserInterface::set_escape(const bool esc)
{
	escape = esc;
}

void UserInterface::set_renew(const bool renewG)
{
	renew = renewG;
}

bool UserInterface::get_renew()
{
	return renew;
}

void UserInterface::set_difficulty(const unsigned int difficulty)
{
	this->difficulty = difficulty;
}

unsigned int UserInterface::get_difficulty()
{
	return difficulty;
}

void UserInterface::set_Pause(const bool Pause)
{
	this->Pause = Pause;
}


std::vector<std::vector<int>> UserInterface::get_loadedTypy_kafli()
{
	return loadedTypy_kafli;
}

sf::Vector2f UserInterface::get_loadedGamerPos()
{
	return loadedGamerPos;
}

sf::Vector2f UserInterface::get_loadedLavaPos()
{
	return sf::Vector2f(loadedLavaPos.x, loadedLavaPos.y);
}

unsigned int UserInterface::get_loadeddiamonds()
{
	return loadedDiamonds;
}

unsigned int UserInterface::get_loadediron()
{
	return loadedIron;
}

unsigned int UserInterface::get_loadedDifficulty()
{
	return loadedDifficulty;
}

bool UserInterface::get_Pause()
{
	return Pause;
}