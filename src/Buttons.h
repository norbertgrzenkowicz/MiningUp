#include "Entity.h"
#include "Myszka.h"

#define set_button(fillColor, outlineColor, outlineThickness, size, buttPos, textPos) \
    button.setFillColor(fillColor);                                                   \
    button.setOutlineColor(outlineColor);                                             \
    button.setOutlineThickness(outlineThickness);                                     \
    button.setSize(size);                                                             \
    button.setPosition(buttPos);                                                      \
    tekst.setPosition(textPos)

#define set_text2(tresc)                  \
    tekst.setFont(font);                  \
    tekst.setFillColor(sf::Color::White); \
    tekst.setString(tresc);               \
    tekstBounds = tekst.getGlobalBounds();

#define set_pickaxe(rect, scale, position) \
    pickaxe.setTexture(pickaxeT);          \
    pickaxe.setTextureRect(rect);          \
    pickaxe.setScale(scale);               \
    pickaxe.setPosition(position);

class Buttons : public Entity_iface
{
  public:
    Buttons();
    Buttons(unsigned int whichButton, sf::RenderWindow& window);   // Konstruktor wszystkich przyciskow, whichButton wskazuje jaki przycisk ma zostal przywolany

    bool isClicked(sf::Event& event,
                   sf::RenderWindow& window);     // Metoda sprawdzajaca czy przycisk zostal klikniety, rysuje szary element na przycisku jesli myszka jest wewnatrz przycisku
    void draw(sf::RenderWindow& window) final;    // rysowanie przyciskow i tekstu
    void drawSprites(sf::RenderWindow& window);   // rysowanie kilofow

  private:
    sf::Font font;   // czcionka

    // Elementy przycisku
    sf::RectangleShape button;
    sf::RectangleShape obramowanie;
    sf::FloatRect buttonBounds;
    sf::Sprite buttonSprite;

    // Elementy tekstu
    sf::Text tekst;
    sf::FloatRect tekstBounds;
    std::string tresc;

    // Pozycje
    sf::Vector2f mousePos;
    sf::Vector2f buttonPos;

    // tekstury
    sf::Texture stopTexture, backtogameTexture, renewTexture, backtomenuTexture, pickaxeT;

    // Sprite kilofu do menu wyboru poziomu trudnoci
    sf::Sprite pickaxe;
};
