#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text highScoreText;

    sf::RectangleShape aiButton;
    sf::Text aiButtonText;

    sf::RectangleShape pvpButton;
    sf::Text pvpButtonText;


public:
    Menu();

    // update text that shows current high score (vs AI only)
    void setHighScore(int score);

    bool isAISelected(const sf::Vector2i& mousePos) const;
    bool isPVPSelected(const sf::Vector2i& mousePos) const;

    // draw entire menu
    void draw(sf::RenderWindow& window);

};

#endif
