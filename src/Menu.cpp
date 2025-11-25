#include "Menu.h"
#include <iostream>

/*
    Constructor: Menu::Menu()

    Objective:
        Initialize the entire game menu including:
        - Title text
        - High score text
        - AI mode button
        - PvP mode button
        - Loading fonts and setting up visuals

    Input Parameters:
        - None

    Return Value:
        - None (constructor)

    Side Effects:
        - Loads font from file (could fail and print to console)
        - Initializes SFML shapes and text elements

    Approach:
        - Load font from assets
        - Set up title and high score display
        - Configure two buttons: AI and PvP
        - Center text within buttons using bounding boxes
*/
Menu::Menu()
{
    if (!font.loadFromFile("assets/font.ttf"))
    {
        std::cout << "Failed to load font\n";
    }

    // --- Title ---
    titleText.setFont(font);
    titleText.setString("PONG");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(240, 50);

    // --- High Score Display ---
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(30);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(200, 150);

    // --- AI Button ---
    aiButton.setSize({200, 60});
    aiButton.setFillColor(sf::Color(80, 80, 80));
    aiButton.setPosition(220, 250);

    aiButtonText.setFont(font);
    aiButtonText.setString("Play vs AI");
    aiButtonText.setFillColor(sf::Color::White);
    aiButtonText.setCharacterSize(24);

    // Center text inside AI button
    auto b1 = aiButtonText.getLocalBounds();
    aiButtonText.setOrigin(b1.left + b1.width / 2, b1.top + b1.height / 2);
    aiButtonText.setPosition(aiButton.getPosition().x + 100,
                             aiButton.getPosition().y + 30);

    // --- PvP Button ---
    pvpButton.setSize({200, 60});
    pvpButton.setFillColor(sf::Color(80, 80, 80));
    pvpButton.setPosition(220, 350);

    pvpButtonText.setFont(font);
    pvpButtonText.setString("Two Players");
    pvpButtonText.setFillColor(sf::Color::White);
    pvpButtonText.setCharacterSize(24);

    // Center PvP text
    auto b2 = pvpButtonText.getLocalBounds();
    pvpButtonText.setOrigin(b2.left + b2.width / 2, b2.top + b2.height / 2);
    pvpButtonText.setPosition(pvpButton.getPosition().x + 100,
                              pvpButton.getPosition().y + 30);
}


/*
    Function: void Menu::setHighScore(int score)

    Objective:
        Update the displayed high score in the menu.

    Input Parameters:
        - int score: The high score to display.

    Return Value:
        - void

    Side Effects:
        - Modifies the text shown on the menu.

    Approach:
        - Convert score to string and set it on highScoreText.
*/
void Menu::setHighScore(int score)
{
    highScoreText.setString("High Score: " + std::to_string(score));
}


/*
    Function: bool Menu::isAISelected(const sf::Vector2i& mousePos) const

    Objective:
        Check if the player clicked on the "Play vs AI" button.

    Input Parameters:
        - const sf::Vector2i& mousePos: Mouse position relative to the window.

    Return Value:
        - bool: true if mouse is inside the AI button, false otherwise.

    Side Effects:
        - None.

    Approach:
        - Use SFML's contains() to check if the mouse coordinates fall within the button bounds.
*/
bool Menu::isAISelected(const sf::Vector2i &mousePos) const
{
    return aiButton.getGlobalBounds().contains(
        static_cast<float>(mousePos.x),
        static_cast<float>(mousePos.y));
}


/*
    Function: bool Menu::isPVPSelected(const sf::Vector2i& mousePos) const

    Objective:
        Check if the player clicked the "Two Players" PvP button.

    Input Parameters:
        - const sf::Vector2i& mousePos: Mouse position relative to the window.

    Return Value:
        - bool: true if player clicked PvP button, false otherwise.

    Side Effects:
        - None.

    Approach:
        - Use bounding-box collision detection via SFML's contains().
*/
bool Menu::isPVPSelected(const sf::Vector2i &mousePos) const
{
    return pvpButton.getGlobalBounds().contains(
        static_cast<float>(mousePos.x),
        static_cast<float>(mousePos.y));
}


/*
    Function: void Menu::draw(sf::RenderWindow &window)

    Objective:
        Render the entire menu onto the game window.

    Input Parameters:
        - sf::RenderWindow& window: The window to draw UI on.

    Return Value:
        - void

    Side Effects:
        - Renders UI elements to the window (visible output).

    Approach:
        - Draw title, high score, AI button, PvP button.
*/
void Menu::draw(sf::RenderWindow &window)
{
    window.draw(titleText);
    window.draw(highScoreText);
    window.draw(aiButton);
    window.draw(aiButtonText);
    window.draw(pvpButton);
    window.draw(pvpButtonText);
}
