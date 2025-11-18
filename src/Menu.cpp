#include "Menu.h"
#include <iostream>



// ===============================================================================
// Objective  : Initialize menu elements such as title, button, fonts, and text.
// Input      : None (constructor).
// Output     : A fully prepared main menu interface.
// Return     : None.
// Side effect: If font fails to load, text will not render properly.
// ===============================================================================
Menu::Menu() {

    // Attempt to load the font required for menu text
    if (!font.loadFromFile("assets/font.ttf")) {
        std::cout << "Failed to load font\n"; // Alerts user if font is missing
    }

    // ------------------ TITLE TEXT SETUP ------------------

    titleText.setFont(font);                 // Apply loaded font to title
    titleText.setString("PONG");             // Displayed title text
    titleText.setCharacterSize(60);          // Large title font size
    titleText.setFillColor(sf::Color::White); // White color for visibility
    titleText.setPosition(240, 50);          // Position at top-center


    // ------------------ HIGH SCORE TEXT SETUP ------------------

    highScoreText.setFont(font);                 // Apply font
    highScoreText.setCharacterSize(30);          // Medium font size
    highScoreText.setFillColor(sf::Color::White); // White text
    highScoreText.setPosition(200, 150);         // Position under title


    // ------------------ NEW GAME BUTTON SETUP ------------------

    newGameButton.setSize(sf::Vector2f(200, 60));   // Button dimensions
    newGameButton.setFillColor(sf::Color(80, 80, 80)); // Grey button color
    newGameButton.setPosition(220, 250);            // Centered on screen


    // ------------------ NEW GAME TEXT SETUP ------------------

    newGameText.setFont(font);                   // Use menu font
    newGameText.setString("New Game");           // Button label
    newGameText.setCharacterSize(24);            // Readable size
    newGameText.setFillColor(sf::Color::White);  // White text

    // ----- Center the text inside the button -----

    // Get text boundaries to calculate its center
    sf::FloatRect textBounds = newGameText.getLocalBounds();

    // Adjust origin to center text around its midpoint
    newGameText.setOrigin(
        textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f
    );

    // Position text exactly at button center
    newGameText.setPosition(
        newGameButton.getPosition().x + newGameButton.getSize().x / 2.0f,
        newGameButton.getPosition().y + newGameButton.getSize().y / 2.0f
    );
}



// ===============================================================================
// Objective  : Update the high score text displayed on the menu.
// Input      : score (int) → latest high score.
// Output     : Displays updated high score on screen.
// Return     : None.
// Side effect: None.
// ===============================================================================
void Menu::setHighScore(int score) {

    // Update text to reflect new high score value
    highScoreText.setString("High Score: " + std::to_string(score));
}



// ===============================================================================
// Objective  : Check if user has clicked the "New Game" button.
// Input      : mousePos → mouse coordinates relative to window.
// Output     : True if clicked, False otherwise.
// Return     : Boolean (true/false).
// Side effect: None.
// ===============================================================================
bool Menu::isNewGameClicked(const sf::Vector2i& mousePos) {

    // Check if the mouse coordinates lie inside the button rectangle
    return newGameButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
}



// ===============================================================================
// Objective  : Draw all menu elements to the window.
// Input      : Render window reference.
// Output     : Menu displayed on screen.
// Return     : None.
// Side effect: None.
// ===============================================================================
void Menu::draw(sf::RenderWindow& window) {

    // Draw title, score display, and the new game button + its text
    window.draw(titleText);
    window.draw(highScoreText);
    window.draw(newGameButton);
    window.draw(newGameText);
}
