#include "TileMap.h"


TileMap::TileMap()
{
	this->initVariable();  //inicjalizowanie zmiennych
	this->generateTiles(); //generowanie typow kafli
	this->map();           //mapowanie typow kafli

}

TileMap::~TileMap()
{
	delete myszka;
}

void TileMap::initVariable()
{
	typ_kafli = std::vector<std::vector<int>>(mapSizeY, std::vector<int>(mapSizeX));
	tileMap = std::vector<std::vector<sf::RectangleShape>>(mapSizeY, std::vector<sf::RectangleShape>(mapSizeX));

	//Inicjalizacja podstawowych cech gry
	ironMiningTime = 2.f;
	diamondMiningTime = 2.5f;
	stoneMiningTime = 1.5f;
	difficultyMultiplier = 1.f;

	srand(time(NULL));
	elapsed = 0;
	miningTime = 0;
	gridSizeF = 60.f;
	gatheredDiamonds = 0;
	gatheredIron = 0;

	//Poczatkowa pozycja gracza
	pastPlayerGridPos = 12;
	
	//tekstury blokow
	diamond.loadFromFile("textures/diamond.jpg");
	stone.loadFromFile("textures/stone.jpg");
	iron.loadFromFile("textures/iron.jpg");
	destroying.loadFromFile("textures/destroyingTextures.png");


	//animacja niszczenia
	rectDestroying = sf::IntRect(0, 0, 32, 32);
	destroyingTiles.setTexture(destroying);
	destroyingTiles.setTextureRect(rectDestroying);
	destroyingTiles.setScale (sf::Vector2f(gridSizeF/32, gridSizeF/32));


	isTileDown = false;
}

void TileMap::generateTiles()
{
	//typ diamentu = 0
	//typ ¿elaza = 1
	//typ kamienia = 2 && 3 && 4 && 5
	//typ przestrzeni = 6

	for (auto& y : typ_kafli)
	{
		for (auto& x : y)
		{
			x = rand()%5;
		}
	}

	//pusta przestrzen poczatkowa
	for (int x = 0; x < mapSizeX; x++)
	{
		typ_kafli[11][x] = 6;
		typ_kafli[12][x] = 6;
	}

	//schody
	typ_kafli[11][10] = 2;
	typ_kafli[12][10] = 2;
	typ_kafli[12][9] = 2;
}

void TileMap::map()
{
	for (int y = 0; y < mapSizeY; y++)
	{
		for (int x = 0; x < mapSizeX; x++)
		{
			if (typ_kafli[y][x] == 0) //dane bloku diamentu
			{
				tileMap[y][x].setTexture(&diamond);
				tileMap[y][x].setSize(sf::Vector2f(gridSizeF, gridSizeF));
				tileMap[y][x].setOutlineThickness(1.f);
				tileMap[y][x].setOutlineColor(sf::Color::Black);
				tileMap[y][x].setPosition(6 * gridSizeF + gridSizeF * x, gridSizeF * y);
			}
			else if (typ_kafli[y][x] == 1) //dane bloku zelaza
			{
				tileMap[y][x].setTexture(&iron);
				tileMap[y][x].setSize(sf::Vector2f(gridSizeF, gridSizeF));
				tileMap[y][x].setOutlineThickness(1.f);
				tileMap[y][x].setOutlineColor(sf::Color::Black);
				tileMap[y][x].setPosition(6 * gridSizeF + gridSizeF * x, gridSizeF * y);

			}
			else if (typ_kafli[y][x] == 2 || typ_kafli[y][x] == 3 || typ_kafli[y][x] == 4 || typ_kafli[y][x] == 5) //dane bloku kamienia
			{
				tileMap[y][x].setTexture(&stone);
				tileMap[y][x].setSize(sf::Vector2f(gridSizeF, gridSizeF));
				tileMap[y][x].setOutlineThickness(1.f);
				tileMap[y][x].setOutlineColor(sf::Color::Black);
				tileMap[y][x].setPosition(6 * gridSizeF + gridSizeF * x, gridSizeF * y);
			}
			else if (typ_kafli[y][x] == 6) //dane pustych przestrzenii
			{
				tileMap[y][x].setSize(sf::Vector2f(0,0));
				tileMap[y][x].setOutlineThickness(1.f);
				tileMap[y][x].setOutlineColor(sf::Color::Black);
				tileMap[y][x].setPosition(6 * gridSizeF + gridSizeF * x, gridSizeF * y);
			}
		}
	}
}

void TileMap::destroyTile(const float& dt, sf::Event& event)
{
	this->ChangeTile(); //jesli jest kafel pomiedzy graczem a wybranym kaflem, zaznaczy kafel pomiedzy

	sf::Vector2u tileSelectorPos = myszka->gettileSelectorGridPos();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && tileSelectorPos.x >= 6 && tileSelectorPos.x < 36
		&& typ_kafli[tileSelectorPos.y][tileSelectorPos.x - 6] != 6
		)
	{
		if (isItSameBlock != typ_kafli[tileSelectorPos.y][tileSelectorPos.x - 6]) //Zerowanie czasu niszczenia przy zmianie bloku
		{
			miningTime = 0.f;
			this->map();
		}

		miningTime += dt;
		isItSameBlock = typ_kafli[tileSelectorPos.y][tileSelectorPos.x - 6];

		if (isItSameBlock == 0) //Diament
		{
			if (miningTime >= diamondMiningTime / difficultyMultiplier)
			{
				typ_kafli[tileSelectorPos.y][tileSelectorPos.x - 6] = 6;
				tileMap[tileSelectorPos.y][tileSelectorPos.x - 6].setSize(sf::Vector2f(0, 0));
				miningTime = 0;
				this->countDiamonds();
				this->map();
			}
		}
		else if (isItSameBlock == 1) //zelazo
		{
			if (miningTime >= ironMiningTime / difficultyMultiplier)
			{
				typ_kafli[tileSelectorPos.y][tileSelectorPos.x - 6] = 6;
				tileMap[tileSelectorPos.y][tileSelectorPos.x - 6].setSize(sf::Vector2f(0, 0));
				miningTime = 0;
				this->countIron();
				this->map();
			}
		}
		else if (isItSameBlock == 2 || isItSameBlock == 3 || isItSameBlock == 4 || isItSameBlock == 5) //kamien
		{
			if (miningTime >= stoneMiningTime / difficultyMultiplier)
			{
				typ_kafli[tileSelectorPos.y][tileSelectorPos.x - 6] = 6;
				tileMap[tileSelectorPos.y][tileSelectorPos.x - 6].setSize(sf::Vector2f(0, 0));
				miningTime = 0;
				this->map();
			}
		}

		this->animateDestroying(dt, tileSelectorPos.y, tileSelectorPos.x - 6); //Animacja niszczenia
	}
}

sf::Vector2f TileMap::tilesDown(sf::Vector2f playerPos) //Jesli obecna pozycja zostanie zmniejszona wzgledem osi X, dodatkowy rzad kaflow powstanie, a ostatni rzad zostanie usuniety
{
	int currentPlayerGridPos = static_cast<int>(playerPos.y) / gridSizeF;
	isTileDown = false;

	if (pastPlayerGridPos >= currentPlayerGridPos)
	{
		for (int y = mapSizeY - 2; y >= 0; y--)
		{
			int j = y + 1;
			typ_kafli[j] = typ_kafli[y];
		}
		for (int x = 0; x < mapSizeX; x++)
		{
			typ_kafli[0][x] = rand() % 5;
		}
		
		pastPlayerGridPos = currentPlayerGridPos;
		playerPos.y = playerPos.y + 60.f;

		isTileDown = true;

		this->map();
	}

	return playerPos;
}

void TileMap::ChangeTile()
{
	sf::Vector2u tileBetweenPos = myszka->getBetweentileGridPos();
	if (tileBetweenPos.x > 5 && tileBetweenPos.x < 24 && typ_kafli[tileBetweenPos.y][tileBetweenPos.x - 6] != 6)
	{
		myszka->isTileBetween();
	}
}

void TileMap::positioning(sf::RenderWindow& window, sf::Vector2f gamerPos, sf::FloatRect gamerBounds)
{
	myszka->positioning(window, gamerPos, gamerBounds); //Pozycjonowanie myszki
}

void TileMap::animateDestroying(const float& dt, int y, int x)
{
	dtime += dt;
	destroyingTiles.setScale(sf::Vector2f(gridSizeF / 32, gridSizeF / 32));

	destroyingTiles.setPosition(sf::Vector2f((x+6) * gridSizeF, y * gridSizeF));

	if (isItSameBlock ==0) //diament
	{
		if (dtime > (diamondMiningTime / difficultyMultiplier) / 4)
		{
			if (rectDestroying.left == 128)
			{
				rectDestroying.left = 0;
				destroyingTiles.setScale(0.f, 0.f);
			}
			else
			{
				rectDestroying.left += 32;
			}
			destroyingTiles.setTextureRect(rectDestroying);
			dtime = 0;
		}
	}

	if (isItSameBlock == 1) //zelazo
	{
		if (dtime > (ironMiningTime / difficultyMultiplier) / 4)
		{
			if (rectDestroying.left == 128)
			{
				rectDestroying.left = 0;
				destroyingTiles.setScale(0.f, 0.f);
			}
			else
			{
				rectDestroying.left += 32;
			}
			destroyingTiles.setTextureRect(rectDestroying);
			dtime = 0;
		}
	}

	if ((isItSameBlock == 2 || isItSameBlock == 3 || isItSameBlock == 4 || isItSameBlock == 5)) //kamien
	{
		if (dtime > (stoneMiningTime / difficultyMultiplier) / 4)
		{
			if (rectDestroying.left == 128)
			{
				rectDestroying.left = 0;
				destroyingTiles.setScale(0.f, 0.f);
			}
			else
			{
				rectDestroying.left += 32;
			}
			destroyingTiles.setTextureRect(rectDestroying);
			dtime = 0;
		}
	}
	
	if (isItSameBlock != typ_kafli[y][x])
	{
		rectDestroying.left = 0;
		destroyingTiles.setTextureRect(rectDestroying);
	}
}

void TileMap::countDiamonds()
{
	gatheredDiamonds += 1;
}

std::vector<std::vector<int>> TileMap::get_typ_kafli()
{
	return typ_kafli;
}

unsigned int TileMap::getGatheredDiamonds()
{
	return gatheredDiamonds;
}

void TileMap::setDiamonds(unsigned int diamonds)
{
	gatheredDiamonds = diamonds;
}

void TileMap::setDiamondsDefault()
{
	gatheredDiamonds = 0;
}

void TileMap::countIron()
{
	gatheredIron += 1;
}

void TileMap::setIron(unsigned int iron)
{
	gatheredIron = iron;
}

void TileMap::setIronDefault()
{
	gatheredIron = 0;
}

void TileMap::setDifficultyMultiplier(unsigned int difficulty)
{
	if (difficulty == 1)
	{
		difficultyMultiplier = 1.5f;
	}
	if (difficulty == 2)
	{

		difficultyMultiplier = 1.f;
	}
	if (difficulty == 3)
	{

		difficultyMultiplier = 0.75;
	}
}

unsigned int TileMap::getGatheredIron()
{
	return gatheredIron;
}

void TileMap::set_typ_kafli(std::vector<std::vector<int>> loadedTypy_kafli)
{
	typ_kafli = loadedTypy_kafli;
}

std::vector<std::vector<sf::RectangleShape>> TileMap::gettileMap()
{
	return tileMap;
}

bool TileMap::get_isTileDown()
{
	return isTileDown;
}

sf::Text TileMap::getText()
{
	return myszka->getText();
}

void TileMap::drawDestroyAnimation(sf::RenderWindow& window)
{
	if (miningTime <= diamondMiningTime / difficultyMultiplier && isItSameBlock == 0) //diament
	{
		window.draw(destroyingTiles);
	}

	if (miningTime <= ironMiningTime / difficultyMultiplier && isItSameBlock == 1) //zelazo
	{
		window.draw(destroyingTiles);
	}

	if (miningTime <= stoneMiningTime / difficultyMultiplier && (isItSameBlock == 2 || isItSameBlock == 3 || isItSameBlock == 4 || isItSameBlock == 5)) //kamien
	{
		window.draw(destroyingTiles);
	}
}

void TileMap::draw(sf::RenderWindow& window)
{
	for (int y = 0; y < mapSizeY; y++)
	{
		for (int x = 0; x < mapSizeX; x++)
		{
			window.draw(tileMap[y][x]);
		}
	}
	myszka->draw(window);
}