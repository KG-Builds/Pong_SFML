#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////////
/// Class: Menu
/// ------------------------------------------------------------
/// Objective:
///     Represents the main menu screen of the Pong game.
///     Displays game title, buttons for selecting game mode,
///     and the current high score (AI-mode only).
///
/// Responsibilities:
///     - Load and display text + button UI elements
///     - Detect mouse-hover and mouse-click selection
///     - Update high score display when needed
///
/// Used By:
///     Game class to render and control menu interactions.
///
/// Side Effects:
///     - Loads font from disk
///     - Draws graphical UI on the window
////////////////////////////////////////////////////////////////
class Menu {
private:

    //////////////////////////////////////////////////////////////
    // Visual + Text Resources
    //////////////////////////////////////////////////////////////
    sf::Font font;                // Loaded font used by all menu text
    sf::Text titleText;           // Title text (“PONG”)
    sf::Text highScoreText;       // High score display for AI mode

    //////////////////////////////////////////////////////////////
    // AI Button UI elements
    //////////////////////////////////////////////////////////////
    sf::RectangleShape aiButton;  // Button background rectangle
    sf::Text aiButtonText;        // “Play vs AI” label text

    //////////////////////////////////////////////////////////////
    // PVP Button UI elements
    //////////////////////////////////////////////////////////////
    sf::RectangleShape pvpButton; // Button background rectangle
    sf::Text pvpButtonText;       // “Player vs Player” label text


public:

    //////////////////////////////////////////////////////////////
    /// Constructor: Menu()
    /// ---------------------------------------------------------
    /// Objective:
    ///     Initializes all menu UI elements including buttons,
    ///     text styles, layout, positioning, and font loading.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     No return value (constructor)
    ///
    /// Side Effects:
    ///     - Loads font from file
    ///     - Positions all menu UI elements on screen
    ///
    /// Approach:
    ///     Load font → configure title text → setup buttons →
    ///     center UI elements on the window → initialize default
    ///     high-score text.
    //////////////////////////////////////////////////////////////
    Menu();


    //////////////////////////////////////////////////////////////
    /// Function: setHighScore(int score)
    /// ---------------------------------------------------------
    /// Objective:
    ///     Updates the high-score text displayed in the menu.
    ///
    /// Input:
    ///     score – integer high score (AI Mode only)
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Updates text object displaying the high score
    ///
    /// Approach:
    ///     Convert score to string → update highScoreText.
    //////////////////////////////////////////////////////////////
    void setHighScore(int score);


    //////////////////////////////////////////////////////////////
    /// Function: isAISelected(const sf::Vector2i& mousePos) const
    /// ---------------------------------------------------------
    /// Objective:
    ///     Checks whether the player's mouse click is inside
    ///     the “Play vs AI” button area.
    ///
    /// Input:
    ///     mousePos – integer window pixel coordinates of mouse
    ///
    /// Return:
    ///     bool – true if AI button pressed
    ///
    /// Approach:
    ///     Convert mousePos to FloatRect & check intersection.
    //////////////////////////////////////////////////////////////
    bool isAISelected(const sf::Vector2i& mousePos) const;


    //////////////////////////////////////////////////////////////
    /// Function: isPVPSelected(const sf::Vector2i& mousePos) const
    /// ---------------------------------------------------------
    /// Objective:
    ///     Checks whether the mouse click occurred inside the
    ///     “Player vs Player” button.
    ///
    /// Input:
    ///     mousePos – mouse coordinates relative to window
    ///
    /// Return:
    ///     bool – true if PVP button clicked
    ///
    /// Approach:
    ///     Check if mousePos lies inside pvpButton boundaries.
    //////////////////////////////////////////////////////////////
    bool isPVPSelected(const sf::Vector2i& mousePos) const;


    //////////////////////////////////////////////////////////////
    /// Function: draw(sf::RenderWindow& window)
    /// ---------------------------------------------------------
    /// Objective:
    ///     Draws the complete menu interface including the
    ///     title, high-score display, and both mode-selection
    ///     buttons.
    ///
    /// Input:
    ///     window – reference to SFML RenderWindow
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Renders UI elements to screen
    ///
    /// Approach:
    ///     window.draw(title) → draw(highScore) →
    ///     draw(AI button) → draw(PVP button).
    //////////////////////////////////////////////////////////////
    void draw(sf::RenderWindow& window);

};

#endif
