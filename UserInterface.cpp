#include "UserInterface.h"

UserInterface::UserInterface(sf::RenderWindow& window)
{
	//Inicjalizacja pomocniczych stanów gry
	renew = false;
	Pause = false;
	helpMenuBool = false;
	isSaved = false;
	isLoaded = false;
	escape = false;

	difficulty = 0;		//Inicjalizacja poziomu trudnoœci

	//Inicjalizacja menu g³ównego
	 menu = new Menu(window.getSize().x, window.getSize().y); 

	 if (!font.loadFromFile("czcionka.ttf"))
	 {
		 std::cout << "czcionka niezaladowana";
	 }

	 //Inicjalizacja sprite'a licznika surowców
	 if (!countUIT.loadFromFile("textures/UI.jpg"));
	 countUI.setTexture(countUIT);
	 countUI.setPosition(1530, 85);

	 //odczyt i zapis struktury graczy
	 this->loadPlayers();


	 //Inicjalizacja przycisków
	przyciskStop = new Buttons(0, window);
	przyciskBackToGame = new Buttons(1, window);
	przyciskRenew = new Buttons(2, window);
	przyciskBackToMenu = new Buttons(3, window);
	endGameBackToMenu = new Buttons(4, window);
	yesButton = new Buttons(5, window);
	noButton = new Buttons(6, window);
	easyButton = new Buttons(7, window);
	mediumButton = new Buttons(8, window);
	hardButton = new Buttons(9, window);

	 
	diamonds = new sf::Text;
	iron = new sf::Text;
	difficultyText = new sf::Text;
	naglowek = new sf::Text;
	kategorie = new sf::Text;
	playerNumber = new sf::Text;
	helpText = new sf::Text;
	escBack = new sf::Text;
	leave = new sf::Text;
	gameOver = new sf::Text;
			 
	ButtonsVector.push_back(przyciskBackToGame);
	ButtonsVector.push_back(przyciskRenew);
	ButtonsVector.push_back(przyciskBackToMenu);

	
	//Tekst diamentów oraz ¿elaza wyœwietlanych w trakcie gry
	sf::Color diamondColor(77, 230, 225);
	diamonds->setFont(font);
	diamonds->setCharacterSize(40);
	diamonds->setFillColor(diamondColor);

	sf::Color ironColor(178, 183, 185);
	iron->setFont(font);
	iron->setCharacterSize(40);
	iron->setFillColor(ironColor);

	//Pomocnicza wiadomoœæ o poruszaniu siê miêdzy menu
	escBack->setFont(font);
	escBack->setFillColor(sf::Color::White);
	escBack->setString("Kliknij Escape, aby cofnac!");
	escBack->setCharacterSize(30);
	escBack->setPosition(50.f, 50.f);


	//tekst koñca gry
	gameOver->setFont(font);
	gameOver->setFillColor(sf::Color::Red);
	gameOver->setString("Koniec Gry!");
	gameOver->setCharacterSize(70);
	gameOver->setPosition(window.getSize().x / 2 - gameOver->getGlobalBounds().width / 2, window.getSize().y / 3);

	//Elementy menu statystyk graczy
	naglowek->setFont(font);
	naglowek->setFillColor(diamondColor);
	naglowek->setString("Wyniki graczy");
	naglowek->setCharacterSize(40);
	naglowek->setPosition(window.getSize().x / 2 - naglowek->getGlobalBounds().width / 2, window.getSize().y / 6);

	kategorie->setFont(font);
	kategorie->setFillColor(sf::Color::White);
	kategorie->setString("Gracz                    Diamenty          Zelazo          Poziom trudnosci");
	kategorie->setCharacterSize(35);
	kategorie->setPosition(100, window.getSize().y / 6 * 1.5);
	
	playerNumber->setFont(font);
	playerNumber->setFillColor(sf::Color::White);
	playerNumber->setCharacterSize(30);

	diamonds->setFont(font);
	diamonds->setFillColor(diamondColor);
	diamonds->setCharacterSize(30);

	iron->setFont(font);
	iron->setFillColor(ironColor);
	iron->setCharacterSize(30);
	
	difficultyText->setFont(font);
	difficultyText->setFillColor(sf::Color::White);
	difficultyText->setCharacterSize(30);

	//Tekst w helpMenu
	helpText->setFont(font);
	helpText->setCharacterSize(20);
	helpText->setString("Celem gry jest uzbieranie jak najwiekszej ilosci diamentow oraz zelaza \n podczas kopania do gory w celu unikniecia smierci w kontakcie z wynurzajaca sie lawa. \n Nalezy zwracac uwage, aby droga ucieczki nie zostala zniszczona \n\n\n Sterowanie postacia: \n W oraz Spacja - Skok \n A lub D - odpowiednio ruch lewo badz w prawo \n F4 - zapisanie obecnego stanu gry \n \n Przytrzymujac LPM mozliwa jest destrukcja klockow. Czas zniszczenia klocka jest zalezny od jego typu. \n\n Aby wyjsc z Help Menu nalezy kliknac F2");
	helpText->setPosition(window.getSize().x / 2 - helpText->getGlobalBounds().width / 2, window.getSize().y / 8);

	//Zapytanie wyjscia z gry
	leave->setFont(font);
	leave->setFillColor(sf::Color::White);
	leave->setString("Czy chcesz wyjsc z gry?");
	leave->setCharacterSize(40);
	leave->setPosition(window.getSize().x / 2 - leave->getGlobalBounds().width / 2, window.getSize().y / 3);
}

UserInterface::~UserInterface()
{
	delete przyciskStop, przyciskBackToGame, przyciskRenew, przyciskBackToMenu, endGameBackToMenu;
	delete menu;
	delete diamonds, iron, difficultyText, naglowek, kategorie, playerNumber, helpText, escBack, leave, gameOver;
}

void UserInterface::inGameUI(sf::Event& event, sf::RenderWindow& window, unsigned int diamondsCounted, unsigned int ironCounted)
{

	//dynamiczny odczyt zebranych diamentów i ¿elaza
	std::stringstream ssDiamonds;
	std::stringstream ssIron;

	ssDiamonds << diamondsCounted;
	ssIron << ironCounted;
	std::string diamondsString = ssDiamonds.str();
	std::string ironString = ssIron.str();


	diamonds->setString(diamondsString);
	iron->setString(ironString);

	diamonds->setPosition(1660, 100);
	iron->setPosition(1660, 200);

	//Przycisk stop, pauzuje grê i uruchamia przyciski powrotu do gry, odnowienia gry, powrotu do menu g³ównego


	window.draw(countUI);

	if (przyciskStop->isClicked(event, window) == true)
	{
		Pause = true;
	}

	if (Pause == true && helpMenuBool == false && escape == false)
	{
		this->putShadow(window);

		for (auto& buttons : ButtonsVector)
		{
			buttons->draw(window);
		}
		if (przyciskBackToGame->isClicked(event, window) == true)
		{
			Pause = false;
		}

		else if (przyciskBackToMenu->isClicked(event, window) == true)
		{
			menu->menu_start = true;
			menu->game_start = false;
			Pause = false;
		}
		else if (przyciskRenew->isClicked(event, window) == true)
		{
			this->set_renew(true);
		}
	}

	this->helpMenu(event, window);
	this->leaveQuestion(event, window);


	przyciskStop->draw(window);
	window.draw(*diamonds);
	window.draw(*iron);

	//Zapytanie o wyjœcie z gry
	this->leaveQuestion(event, window);
}

void UserInterface::helpMenu(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
	{
		helpMenuBool = true;
	}	

	if (helpMenuBool == true)
	{
		this->putShadow(window);
		Pause = true;

		window.draw(*helpText);
		
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
		{
			helpMenuBool = false;
			Pause = false;
		}
	}
}

bool UserInterface::endGameMenu(bool isDead,sf::Event& event, sf::RenderWindow &window)
{
	if (isDead == true)
	{
		this->putShadow(window);
		window.draw(*gameOver);
		endGameBackToMenu->draw(window);
		if (endGameBackToMenu->isClicked(event, window) == true)
		{
			std::cout << "isclicked";
			return true;
		}
	}
	return false;
}

void UserInterface::playersScore(sf::Event& event, sf::RenderWindow& window)
{
	int i = 0;
	int j;

	std::string number;
	std::string diamondsS;
	std::string ironS;

	for (auto& gracz : gracze)
	{
		std::stringstream ssDiamonds;
		std::stringstream ssIron;
		std::stringstream ssNumber;
		j = i + 1;
		ssNumber << j;
		ssDiamonds << gracz.diamondsCounted;
		ssIron << gracz.ironCounted;

		number = ssNumber.str();
		diamondsS = ssDiamonds.str();
		ironS = ssIron.str();

		diamonds->setString(diamondsS);
		iron->setString(ironS);

		if (gracz.difficulty == 1)
		{
			difficultyText->setString("Latwy");
		}
		else if (gracz.difficulty == 2)
		{
			difficultyText->setString("Sredni");
		}
		else if (gracz.difficulty == 3)
		{
			difficultyText->setString("Trudny");
		}

		playerNumber->setString(number);

		playerNumber->setPosition(150.f, window.getSize().y / 6 * 2 + window.getSize().y / 12 * i);
		diamonds->setPosition(700.f, window.getSize().y / 6 * 2 + window.getSize().y / 12 * i);
		iron->setPosition(1050.f, window.getSize().y / 6 * 2 + window.getSize().y / 12 * i);
		difficultyText->setPosition(1450.f, window.getSize().y / 6 * 2 + window.getSize().y / 12 * i);

		i++;
		window.draw(*playerNumber);
		window.draw(*diamonds);
		window.draw(*iron);
		window.draw(*difficultyText);
	}
	window.draw(*escBack);
	window.draw(*naglowek);
	window.draw(*kategorie);
}

void UserInterface::chooseDifficulty(sf::Event& event, sf::RenderWindow& window)
{
	if (easyButton->isClicked(event, window))
	{
		difficulty = 1;
		menu->set_newGame = true;
		menu->game_start = true;
		menu->choose_difficulty = false;
	}
	else if (mediumButton->isClicked(event, window))
	{
		difficulty = 2;
		menu->set_newGame = true;
		menu->game_start = true;
		menu->choose_difficulty = false;
	}
	else if (hardButton->isClicked(event, window))
	{
		difficulty = 3;
		menu->set_newGame = true;
		menu->game_start = true;
		menu->choose_difficulty = false;
	}
	easyButton->draw(window);
	easyButton->drawSprites(window);
	mediumButton->draw(window);
	mediumButton->drawSprites(window);
	hardButton->draw(window);
	hardButton->drawSprites(window);
	window.draw(*escBack);
}

void UserInterface::save(sf::Event event, sf::Vector2f playerPos, std::vector<std::vector<int>> tilemap, sf::Vector2f lavaPos, unsigned int diamondsCount, unsigned int ironCount)
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
			{
				savefile << tiles<<" ";
			}
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

		if (gracze.size() < 5)
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
		else if (gracze.size() >= 5)
		{
			savePlayersfile.open("saves/players.txt");

			for (int i = 3; i >= 0; i--)
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
	if (isSaved != true)
	{
		this->savePlayers(diamondsCount, ironCount, difficulty);
		isSaved = true;
	}
}

void UserInterface::loadGame()
{
	
		std::string lines[29];
		std::ifstream savefile("saves/save1.txt");
		std::string line;
		int typy;
		int i = 0;

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
			std::cout << "plik nie zostal otwarty";
		}

		loadedGamerPos.x = std::stof(lines[0]);
		loadedGamerPos.y = std::stof(lines[1]);

		for (int i = 2; i <= 23; i++)
		{
			std::vector<int> typy_kafli;
			std::stringstream kafleString(lines[i]);
			while (kafleString >> typy)
			{
				typy_kafli.push_back(typy);
			}
			loadedTypy_kafli.push_back(typy_kafli);
		}

		loadedLavaPos.x = std::stof(lines[24]);
		loadedLavaPos.y = std::stof(lines[25]);
		loadedDiamonds = std::stoi(lines[26]);
		loadedIron = std::stoi(lines[27]);
		loadedDifficulty = std::stoi(lines[28]);


		menu->game_start = true;
		menu->menu_start = false;

}

void UserInterface::loadPlayers()
{
		std::fstream savePlayersfileReadingC("saves/players.txt", std::ios_base::in);
		std::fstream savePlayersfileReading("saves/players.txt", std::ios_base::in);
		std::string line;
		int j = 0;
		int lines = 0;
		int output[15];

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
			for (int i = 0; i < lines; i++)
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
	sf::RectangleShape menuShadow;
	menuShadow.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	menuShadow.setFillColor(sf::Color(0, 0, 0, 128));
	window.draw(menuShadow);
}

void UserInterface::leaveQuestion(sf::Event& event, sf::RenderWindow& window)
{
	if (escape == true)
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

		window.draw(*leave);
		noButton->draw(window);
		yesButton->draw(window);
	}
}

void UserInterface::set_escape(bool esc)
{
	escape = esc;
}

void UserInterface::set_renew(bool renewG)
{
	renew = renewG;
}

bool UserInterface::get_renew()
{
	return renew;
}

void UserInterface::set_difficulty(unsigned int difficulty)
{
	this->difficulty = difficulty;
}

unsigned int UserInterface::get_difficulty()
{
	return difficulty;
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