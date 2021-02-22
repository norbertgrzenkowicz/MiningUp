
#include "Myszka.h"

Myszka::Myszka()
{
	font.loadFromFile("czcionka.ttf");

	testBox = new sf::RectangleShape;
	testBoxHalfed = new sf::RectangleShape;
	tileSelector = new sf::RectangleShape;

	//zasieg postaci
	destroyRange = 120;

	//Rozmiar siatki
	gridSizef = 60.f;
	gridSizeU = static_cast<int>(gridSizef);
	
	//tekst wyswietlanych koordynatow
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);
	text.setFont(font);
	text.setPosition(20.f, 20.f);
	//TileSelector
	tileSelector->setSize(sf::Vector2f(gridSizef, gridSizef));
	tileSelector->setFillColor(sf::Color::Transparent);
	tileSelector->setOutlineThickness(1.f);
	tileSelector->setOutlineColor(sf::Color::Green);

	//Pomocnicze wyznaczania kafli
	testBox->setSize(sf::Vector2f(10, 10));
	testBox->setFillColor(sf::Color::Green);
	testBoxHalfed->setSize(sf::Vector2f(10, 10));
	testBoxHalfed->setFillColor(sf::Color::Yellow);
}

Myszka::~Myszka()
{
	delete testBox, testBoxHalfed, tileSelector;
}

void Myszka::positioning(sf::RenderWindow &window, sf::Vector2f gamerPos, sf::FloatRect gamerBounds) //Kompletna metoda pozycjonowania myszki oraz kafli wzgledem zasiegu postaci
{
	//Inicjalizacja pozycji postaci
	std::stringstream ss;
	//sf::Vector2f gamerPos = gamer->getPosition();
	//sf::FloatRect gamerBounds = gamer->getGlobalBounds();
	gamerPosMid = sf::Vector2f(gamerPos.x, gamerPos.y + gamerBounds.height / 2);


	//Pozycjonowanie myszki
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(mousePosWindow);


	//Koordynaty myszki
	mousePosGrid.x = mousePosView.x / gridSizeU;
	mousePosGrid.y = mousePosView.y / gridSizeU;

	ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
		<< "window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
		<< "View: " << mousePosView.x << " " << mousePosView.y << "\n"
		<< "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";
	text.setString(ss.str());


	//Koordynaty myszki poza zasiêgiem postaci
	
	//tangensy dla trojk¹ta tworzonego przez œrodek postaci pozycji myszki oraz przeciêcia prostych X oraz Y
	float anglesTangensX;
	float anglesTangensY;
	anglesTangensX = (abs(gamerPosMid.y - mousePosView.y)) /(abs(gamerPosMid.x - mousePosView.x));
	anglesTangensY = (gamerPosMid.y - mousePosView.y) / (abs(gamerPosMid.x - mousePosView.x));


	//Celem ponizszych instrukcji jest uzyskanie punktu maksymalnego zasiegu, znajdujacego sie pomiedzy myszka a srodkiem postaci


	//dolny zakres
	if (mousePosView.y > gamerPosMid.y + destroyRange)
	{
		if (mousePosView.x < gamerPosMid.x && mousePosView.x > gamerPosMid.x - destroyRange)
		{
			rangeLimit = sf::Vector2f(gamerPosMid.x - destroyRange / anglesTangensX, gamerPosMid.y + destroyRange);
			rangeLimitHalfed = sf::Vector2f(gamerPosMid.x - destroyRange / 2 / anglesTangensX, gamerPosMid.y + destroyRange / 2);
		}
	
		else if(mousePosView.x > gamerPosMid.x && mousePosView.x < gamerPosMid.x + destroyRange)
		{
			rangeLimit = sf::Vector2f(gamerPosMid.x + destroyRange / anglesTangensX, gamerPosMid.y + destroyRange);
			rangeLimitHalfed = sf::Vector2f(gamerPosMid.x + destroyRange / 2 / anglesTangensX, gamerPosMid.y + destroyRange / 2);
		}
	}

	//gorny zakres
	else if (mousePosView.y < gamerPosMid.y - destroyRange)
	{
		if (mousePosView.x < gamerPosMid.x && mousePosView.x > gamerPosMid.x - destroyRange)
		{
			rangeLimit = sf::Vector2f(gamerPosMid.x - destroyRange / anglesTangensX, gamerPosMid.y - destroyRange);
			rangeLimitHalfed = sf::Vector2f(gamerPosMid.x - destroyRange / 2 / anglesTangensX, gamerPosMid.y - destroyRange / 2);
		}

		else if (mousePosView.x > gamerPosMid.x && mousePosView.x <= gamerPosMid.x + destroyRange)
		{
			rangeLimit = sf::Vector2f(gamerPosMid.x + destroyRange / anglesTangensX, gamerPosMid.y - destroyRange);
			rangeLimitHalfed = sf::Vector2f(gamerPosMid.x + destroyRange / 2 / anglesTangensX, gamerPosMid.y - destroyRange / 2);
		}
	}

	//lewy zakres
	else if (mousePosView.x < gamerPosMid.x - destroyRange)
	{
		if (mousePosView.y > gamerPosMid.y - destroyRange && mousePosView.y < gamerPosMid.y + destroyRange)
		{
			rangeLimit = sf::Vector2f(gamerPosMid.x - destroyRange, gamerPosMid.y - destroyRange * anglesTangensY);
			rangeLimitHalfed = sf::Vector2f(gamerPosMid.x - destroyRange / 2, gamerPosMid.y - (destroyRange/2) * anglesTangensY);
		}
	}
	//prawy zakres
	else if (mousePosView.x > gamerPosMid.x + destroyRange)
	{
		if (mousePosView.y < gamerPosMid.y + destroyRange && mousePosView.y > gamerPosMid.y - destroyRange)
		{
			rangeLimit = sf::Vector2f(gamerPosMid.x + destroyRange, gamerPosMid.y - destroyRange * anglesTangensY);
			rangeLimitHalfed = sf::Vector2f(gamerPosMid.x + destroyRange / 2, gamerPosMid.y - (destroyRange / 2)* anglesTangensY);
		}
	}

	//rogi
	//prawy górny róg
	if (mousePosView.x > gamerPosMid.x + destroyRange && mousePosView.y < gamerPosMid.y - destroyRange)
	{
		rangeLimit = sf::Vector2f(gamerPosMid.x + destroyRange, gamerPosMid.y - destroyRange);
		rangeLimitHalfed = sf::Vector2f(gamerPosMid.x + destroyRange / 2, gamerPosMid.y - destroyRange / 2);
	}
	//lewy górny róg
	else if (mousePosView.x < gamerPosMid.x - destroyRange && mousePosView.y < gamerPosMid.y - destroyRange)
	{
		rangeLimit = sf::Vector2f(gamerPosMid.x - destroyRange, gamerPosMid.y - destroyRange);
		rangeLimitHalfed = sf::Vector2f(gamerPosMid.x - destroyRange / 2, gamerPosMid.y - destroyRange / 2);
	}
	//lewy dolny róg
	else if (mousePosView.x < gamerPosMid.x - destroyRange && mousePosView.y > gamerPosMid.y + destroyRange)
	{
		rangeLimit = sf::Vector2f(gamerPosMid.x - destroyRange, gamerPosMid.y + destroyRange);
		rangeLimitHalfed = sf::Vector2f(gamerPosMid.x - destroyRange / 2, gamerPosMid.y + destroyRange / 2);
	}
	//prawy dolny róg
	else if (mousePosView.x > gamerPosMid.x + destroyRange && mousePosView.y > gamerPosMid.y + destroyRange)
	{
		rangeLimit = sf::Vector2f(gamerPosMid.x + destroyRange, gamerPosMid.y + destroyRange);
		rangeLimitHalfed = sf::Vector2f(gamerPosMid.x + destroyRange / 2, gamerPosMid.y + destroyRange / 2);
	}

	//rangeLimitHalfed = sf::Vector2f(rangeLimit.x/2, rangeLimit.y/2);
	if (rangeLimit.x >= 0.f)
	{
		rangeLimitGridPos.x = rangeLimit.x / gridSizeU;
		BetweentileGridPos.x = rangeLimitHalfed.x / gridSizeU;
		rangeLimitGridPos.y = rangeLimit.y / gridSizeU;
		BetweentileGridPos.y = rangeLimitHalfed.y / gridSizeU;
	}		

	//Pozycjonowanie tileSelector wewnatrz zasiegu
	if (mousePosView.x >= gridSizef*6 && mousePosView.x <= gridSizef*24
		&& mousePosView.x <= gamerPosMid.x + destroyRange && mousePosView.y <= gamerPosMid.y + destroyRange
		&& mousePosView.x >= gamerPosMid.x - destroyRange && mousePosView.y >= gamerPosMid.y - destroyRange
		)
	{
		tileSelector->setPosition(mousePosGrid.x * gridSizef, mousePosGrid.y * gridSizef);
	}
	else if (mousePosView.x >= gridSizef * 6 && mousePosView.x <= gridSizef * 24 
		&& (mousePosView.x > gamerPosMid.x + destroyRange || mousePosView.x < gamerPosMid.x - destroyRange
		 || mousePosView.y > gamerPosMid.y + destroyRange || mousePosView.y < gamerPosMid.y - destroyRange)
		)
	{
		tileSelector->setPosition(rangeLimitGridPos.x * gridSizef, rangeLimitGridPos.y * gridSizef);
	}

	//Pozycjonowanie pomocniczych punktów okreslajacych zasieg oraz jego po³owê
	testBoxHalfed->setPosition(rangeLimitHalfed);
	testBox->setPosition(rangeLimit);
}

void Myszka::draw(sf::RenderWindow& window) //rysowanie wszystkich elementow
{
	window.draw(*tileSelector);
	//odkomentuj dla dodatkowego interfejsu wskazuj¹cego maksymalny dystans oraz jego po³owê
	//window.draw(testBox);
	//window.draw(testBoxHalfed);
}

void Myszka::isTileBetween() //pozycjonuje tileSelector do kalfa pomiedzy wskazanym kaflem 
{
	tileSelector->setPosition(BetweentileGridPos.x * gridSizef, BetweentileGridPos.y * gridSizef);
}


sf::Vector2u Myszka::gettileSelectorGridPos() //zwracanie pozycji tileSelectora
{
	return sf::Vector2u(tileSelector->getPosition().x / gridSizef, tileSelector->getPosition().y / gridSizef);
}


sf::Vector2u Myszka::getBetweentileGridPos() //zwracanie pozycji kafla pomiedzy wskazanym kaflem
{
	return BetweentileGridPos;
}

sf::Text Myszka::getText() //zwracanie tekstu koordynatow myszki
{
	return text;
}