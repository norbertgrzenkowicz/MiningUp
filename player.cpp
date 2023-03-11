#include "player.h"


float gravity = 0.1f;

player::player()
{
	this->initVariables();
	this->initTexture();
}

player::~player()
{
	delete gracz;
}

void player::initVariables()
{
	//Inicjalizacja cech ruchu
	gravity = 0.1f;
	movementspeed = 200.f;
	velocity.x = 0.f;
	velocity.y = 0.f;
	dtime = 0;
	elapsedJump = 0;
	//Zmienne stanu ycia oraz skakania
	lavaTouched = false;
	isJumping = false;
}

void player::initTexture()
{
	if (!tekstura.loadFromFile("textures/charactersprites.png"))
		std::cout<<"Nie zaladowano tekstury";

	if (!pickaxeTexture.loadFromFile("textures/pickaxes.png"))
		std::cout<<"Nie zaladowano tekstury";

	//Wymiary Sprite'ow
	rectGraczSprite = sf::IntRect(0, 0, 30, 40);
	rectArmSprite = sf::IntRect(20, 40, 15, 20);
	rectDiamondPickaxeSprite = sf::IntRect(0, 0, 14, 14);
	rectIronPickaxeSprite = sf::IntRect(14, 0, 14, 14);
	rectStonePickaxeSprite = sf::IntRect(28, 0, 14, 14);

	//Inicjalizacja tekstur
	gracz = new sf::Sprite;
	pickaxeArm = new sf::Sprite;
	pickaxe = new sf::Sprite;

	gracz->setTexture(tekstura);
	pickaxeArm->setTexture(tekstura);
	pickaxe->setTexture(pickaxeTexture);

	gracz->setTextureRect(rectGraczSprite);
	pickaxeArm->setTextureRect(rectArmSprite);


	//Rotacja rki i kilofa
	pickaxeArm->setRotation(-45.f);
	pickaxe->setRotation(45.f);

	pickaxeArm->rotate(0.f);
	pickaxe->rotate(0.f);

	//Wybranie rodka obrotu postaci
	gracz->setOrigin({ gracz->getLocalBounds().width / 2, 0 });
	pickaxeArm->setOrigin({-gracz->getLocalBounds().width / 2, 0 });
	pickaxe->setOrigin({ -gracz->getLocalBounds().width / 2, 0 });

	//Pozycjonowanie pocztkowe rki, kilofa oraz gracza
	pickaxeArm->setPosition(sf::Vector2f(gracz->getPosition().x - 5, gracz->getPosition().y + 4 + gracz->getGlobalBounds().height / 2));
	pickaxe->setPosition(sf::Vector2f(pickaxeArm->getPosition().x + 20, gracz->getPosition().y - 10));
	gracz->setPosition(9 * gridsize, 12 * gridsize);

	//Ustawienie wielkosci postaci oraz jej elementow
	gracz->setScale(1.5f, 1.5f);
	pickaxeArm->setScale(1.5f, 1.5f);
	pickaxe->setScale(1.5f, 1.5f);
	
	//Zmienna pomocnicza wskazujaca hitbox
	hitbox.setOutlineColor(sf::Color::Green);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(2.f);
	hitbox.setSize(sf::Vector2f(gracz->getGlobalBounds().width, gracz->getGlobalBounds().height));
}

void player::move(const float& dt, sf::Event& event)
{
	sf::Vector2f gamerPosition = gracz->getPosition();

	velocity.x = 0;

	//Prawy ruch
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += +movementspeed * dt;
	}
	//Lewy ruch
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x += -movementspeed * dt;
	}

	if (isJumping == false) //Skok
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			isJumping = true;
			velocity.y = -5;
		}
	}
	elapsedJump += dt;
	if (velocity.y == 0 && elapsedJump >0.5f)
	{
		isJumping = false;
		elapsedJump = 0.f;
	}

	//metody animacji, kolizji oraz podania rki za graczem
	this->moveArm();
	this->walkingAnimation(dt);
	this->physics();
	gracz->move(velocity);
	this->wallCollision();
}

void player::wallCollision()
{
	//Lewa kolizja
	if (gracz->getPosition().x < 360.f)
	{
		gracz->setPosition(360.f, gracz->getPosition().y);
	}

	//Gorna kolizja
	if (gracz->getPosition().y < 0.f)
	{
		gracz->setPosition(gracz->getPosition().x, 0.f);
	}
	//Prawa kolizja
	if (gracz->getPosition().x + gracz->getGlobalBounds().width > 1440)
	{
		gracz->setPosition(1440 - gracz->getGlobalBounds().width, gracz->getPosition().y);
	}
	//Dolna kolizja
	if (gracz->getPosition().y + gracz->getGlobalBounds().height > 1080)
	{
		gracz->setPosition(gracz->getPosition().x, 1080 - gracz->getGlobalBounds().height);
	}
}

void player::objectCollision(sf::RectangleShape wall)
{
	//wymiary gracza
	sf::FloatRect playerBounds = gracz->getGlobalBounds();
	sf::FloatRect wallBounds = wall.getGlobalBounds();
	hitbox.setPosition(playerBounds.left, playerBounds.top);

	nextPos = playerBounds; //Nastpna pozycja gracza jako wskanik gdzie znajdzie si w nastpnej klatce posta bez kolizji
	nextPos.left += velocity.x;
	nextPos.top += velocity.y;

	if (wallBounds.intersects(nextPos))
	{
		//Kolizja dolna
		if (playerBounds.top < wallBounds.top
			&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
			&& playerBounds.left < wallBounds.left + wallBounds.width
			&& playerBounds.left + playerBounds.width > wallBounds.left
			)
		{
			velocity.y = 0.f;
			gracz->setPosition(gracz->getPosition().x, wallBounds.top - playerBounds.height);
		}

		//Grna kolizja
		else if (playerBounds.top > wallBounds.top
			&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
			&& playerBounds.left < wallBounds.left + wallBounds.width
			&& playerBounds.left + playerBounds.width > wallBounds.left
			)
		{
			velocity.y = 0.f;
			gracz->setPosition(gracz->getPosition().x, wallBounds.top + wallBounds.height);
		}


		//Prawa kolizja
		if (playerBounds.left < wallBounds.left
			&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
			&& playerBounds.left + playerBounds.width > wallBounds.left
			&& playerBounds.top + 10 < wallBounds.top + wallBounds.height
			&& playerBounds.top + playerBounds.height > wallBounds.top + 10
			)
		{
			velocity.x = 0.f;
			gracz->setPosition(wallBounds.left - playerBounds.width / 2, playerBounds.top);
		}
		//Lewa kolizja
		else if (playerBounds.left > wallBounds.left
			&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
			&& playerBounds.left < wallBounds.left + wallBounds.width
			&& playerBounds.top + 10 < wallBounds.top + wallBounds.height
			&& playerBounds.top + playerBounds.height > wallBounds.top + 10
			)
		{

			velocity.x = 0.f;
			gracz->setPosition(wallBounds.left + wallBounds.width + playerBounds.width / 2, playerBounds.top);
		}

	}
}

void player::objectCollisionToTileMap(TileMap* map)
{
	for (auto& tiles : map->gettileMap()) 
	{
		for (auto& tile : tiles)
			this->objectCollision(tile); //Kolizja dla kadego bloku na mapie
	}
}

void player::physics()
{
	if (this->gracz->getPosition().y < 1080)
	{
		velocity.y += gravity;
	}
	//Przypieszenie grawitacyjne postaci
	velocity.x += acceleration.x; 
	velocity.y += acceleration.y;

}

void player::didLavaTouched(sf::Vector2f lavaPos)
{
	if (lavaPos.y < gracz->getPosition().y + gracz->getGlobalBounds().height)
	{
		lavaTouched = true;
	}
}

bool player::getLavaTouched()
{
	return lavaTouched;
}

void player::moveArm()
{
	if (velocity.x > 0) //Rka oraz kilof podczs ruchu w prawo
	{
		gracz->setScale(1.5f, 1.5f);
		pickaxeArm->setScale(1.5f, 1.5f);
		pickaxe->setScale(1.5f, 1.5f);

		pickaxeArm->setRotation(-45.f);
		pickaxe->setRotation(45.f);

		pickaxeArm->rotate(0.f);
		pickaxe->rotate(0.f);

		pickaxeArm->setPosition(sf::Vector2f(gracz->getPosition().x - 5, gracz->getPosition().y + 4 + gracz->getGlobalBounds().height / 2));
		pickaxe->setPosition(sf::Vector2f(pickaxeArm->getPosition().x + 20, gracz->getPosition().y - 10));
	}

	else if (velocity.x < 0) //Rka oraz kilof podczs ruchu w lewo
	{
		gracz->setScale(-1.5f, 1.5f);
		pickaxeArm->setScale(-1.5f, 1.5f);
		pickaxe->setScale(-1.5f, 1.5f);

		pickaxeArm->setRotation(45.f);
		pickaxeArm->rotate(0.f);

		pickaxe->setRotation(-45.f);
		pickaxe->rotate(0.f);

		pickaxeArm->setPosition(sf::Vector2f(gracz->getPosition().x + 5, gracz->getPosition().y + 4 + gracz->getGlobalBounds().height / 2));
		pickaxe->setPosition(sf::Vector2f(pickaxeArm->getPosition().x - 20, gracz->getPosition().y - 10));
	}

	if (velocity.x == 0 && gracz->getScale().x ==1.5f) //Rka oraz kilof podczas ruchu w d
	{
		pickaxeArm->setPosition(sf::Vector2f(gracz->getPosition().x - 5, gracz->getPosition().y + 4 + gracz->getGlobalBounds().height / 2));
		pickaxe->setPosition(sf::Vector2f(pickaxeArm->getPosition().x + 20, gracz->getPosition().y - 10));
	}
	else if (velocity.x == 0 && gracz->getScale().x == -1.5f) //Rka oraz kilof podczas ruchu w gr
	{
		pickaxeArm->setPosition(sf::Vector2f(gracz->getPosition().x + 5, gracz->getPosition().y + 4 + gracz->getGlobalBounds().height / 2));
		pickaxe->setPosition(sf::Vector2f(pickaxeArm->getPosition().x - 20, gracz->getPosition().y - 10));
	}
}

void player::walkingAnimation(const float &dt)
{
	dtime += dt;

	if (velocity.y == 0 && velocity.x > 0) //animacja w prawo
	{
		if (dtime > 0.1f)
		{
			if (rectGraczSprite.left == 60)
			{
				rectGraczSprite.left = 0;
			}
			else
			{
				rectGraczSprite.left += 30;
			}
			gracz->setTextureRect(rectGraczSprite);
			dtime = 0;
		}
	}

	else if (velocity.y == 0 && velocity.x < 0) //animacja w lewo
	{
		if (dtime > 0.1f)
		{
			if (rectGraczSprite.left == 60)
			{
				rectGraczSprite.left = 0;
			}
			else
			{
				rectGraczSprite.left += 30;
			}
			gracz->setTextureRect(rectGraczSprite);
			gracz->setScale(-1.5f, 1.5f);
			dtime = 0;
		}
	}
	else if (velocity.x == 0) //Pozycja bez ruchu
	{
		rectGraczSprite.left = 0;
		gracz->setTextureRect(rectGraczSprite);
	}
}

bool player::death(const float& dt, bool death)
{
	if (gracz->getGlobalBounds().top < 22 * gridsize)
	{
		gracz->setRotation(-90.f);
		gracz->move(0, 500 * dt); //Ruch poniej ekranu
		return true;
	}
	else if (gracz->getGlobalBounds().top >= 22 * gridsize)
	{
		return true;
	}
	else
		return false;
}

void player::setPosition(sf::Vector2f playerPos)
{
	gracz->setPosition(playerPos);
}

void player::setPositionDefault()
{
	this->gracz->setPosition(9 * gridsize, 12 * gridsize);
}

void player::setPickaxe(unsigned int difficulty)
{
	if (difficulty == 1)
	{
		pickaxe->setTextureRect(rectDiamondPickaxeSprite);	//atwy -> diamentowy kilof
	}
	else if (difficulty == 2)
	{
		pickaxe->setTextureRect(rectIronPickaxeSprite);		//redni -> elazny kilof
	}
	else if (difficulty == 3)
	{
		pickaxe->setTextureRect(rectStonePickaxeSprite);		//Trudny -> kamienny kilof
	}
}

sf::Vector2f player::getPosition()
{
	return gracz->getPosition();
}

sf::FloatRect player::getBounds()
{
	return gracz->getGlobalBounds();
}

int player::getGridPosY()
{
	return static_cast<int>(gracz->getPosition().y);
}

void player::draw(sf::RenderWindow& window)
{
	window.draw(*gracz);
	window.draw(*pickaxe);
	window.draw(*pickaxeArm);
	//window->draw(hitbox); //odkomentuj w celu rysowania hitboxa
}
