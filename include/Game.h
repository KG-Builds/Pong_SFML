#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Paddle.h"
#include "Ball.h"

///////////////////////////////////////////////////////////////
/// Enum: GameState
/// ----------------------------------------------------------
/// Objective:
///     Represents the different screens/stages of the game.
///
/// Values:
///     MENU       – Main menu interface
///     PLAYING    – Actual gameplay running
///     GAME_OVER  – End screen after game finishes
///////////////////////////////////////////////////////////////
enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

///////////////////////////////////////////////////////////////
/// Enum: GameMode
/// ----------------------------------------------------------
/// Objective:
///     Defines which type of game is being played.
///
/// Values:
///     PLAYER_VS_AI      – Player vs computer
///     PLAYER_VS_PLAYER  – Two human players using keyboard
///////////////////////////////////////////////////////////////
enum class GameMode {
    PLAYER_VS_AI,
    PLAYER_VS_PLAYER
};

///////////////////////////////////////////////////////////////
/// Class: Game
/// ----------------------------------------------------------
/// Objective:
///     Central class that manages the entire Pong game.
///     It controls window creation, menu navigation,
///     paddle/ball objects, scoring, AI logic, rendering,
///     and state transitions.
///
/// Side Effects:
///     - Creates a graphical window.
///     - Loads files from the system (font, highscore).
///     - Updates global game state.
///     - Writes to a text file for high score.
///
/// Used By:
///     main() to start the game loop.
///////////////////////////////////////////////////////////////
class Game {
private:
    sf::RenderWindow window;     // Main game window
    GameState state;             // Current state of the game
    GameMode mode;               // Selected game mode (AI or PVP)

    Menu menu;                   // Menu UI object
    Paddle leftPaddle;           // Player 1 paddle
    Paddle rightPaddle;          // AI or Player 2 paddle
    Ball ball;                   // Ball object controlling gameplay
    
    int leftScore;               // Player 1 score
    int rightScore;              // Player 2 / AI score
    int highScore;               // Highest score achieved in AI mode
    int lives;                   // Lives remaining (only in AI mode)
    
    sf::Font font;               // Loaded game font
    sf::Text scoreText;          // Score display text

    sf::Text gameOverText;           // “Game Over” message
    sf::Text gameOverHighScoreText;  // High-score text for AI mode
    sf::Text continueText;           // “Press Enter to continue”
    
public:

    ///////////////////////////////////////////////////////////
    /// Constructor: Game()
    /// ------------------------------------------------------
    /// Objective:
    ///     Initializes game objects, loads fonts,
    ///     sets default values, prepares UI text,
    ///     and loads previous high score.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     No return value (constructor)
    ///
    /// Side Effects:
    ///     - Creates a window.
    ///     - Loads font from file system.
    ///     - Reads highscore.txt.
    ///
    /// Approach:
    ///     Initialize SFML window → configure paddles →
    ///     center ball → set initial game state → load assets.
    ///////////////////////////////////////////////////////////
    Game();


    ///////////////////////////////////////////////////////////
    /// Function: run()
    /// ------------------------------------------------------
    /// Objective:
    ///     Starts and executes the main game loop
    ///     (event handling → updating → drawing).
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Continuously updates game state.
    ///     - Renders frames to the window.
    ///
    /// Approach:
    ///     Uses a clock to compute delta time,
    ///     calls processEvents(), update(), and render().
    ///////////////////////////////////////////////////////////
    void run();

private:

    ///////////////////////////////////////////////////////////
    /// Function: processEvents()
    /// ------------------------------------------------------
    /// Objective:
    ///     Handles all input events such as keyboard presses,
    ///     mouse clicks, and window closing.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Changes game state based on menu selection.
    ///     - Moves paddles based on keyboard.
    ///     - Can close the game window.
    ///
    /// Approach:
    ///     Poll SFML events → check type → act accordingly.
    ///////////////////////////////////////////////////////////
    void processEvents();


    ///////////////////////////////////////////////////////////
    /// Function: update(float dt)
    /// ------------------------------------------------------
    /// Objective:
    ///     Updates game physics, AI movement, ball movement,
    ///     scoring logic, and game-over detection.
    ///
    /// Input:
    ///     dt – Time elapsed since last frame (delta time)
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Moves paddles and ball.
    ///     - Modifies scores & lives.
    ///     - Triggers GAME_OVER state.
    ///
    /// Approach:
    ///     Paddle movement → AI logic → ball update →
    ///     collision detection → scoring → UI update.
    ///////////////////////////////////////////////////////////
    void update(float dt);


    ///////////////////////////////////////////////////////////
    /// Function: render()
    /// ------------------------------------------------------
    /// Objective:
    ///     Draws game objects onto the window depending
    ///     on the current state (menu, game, game over).
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     Draws pixels on the window.
    ///
    /// Approach:
    ///     window.clear() → draw objects → window.display().
    ///////////////////////////////////////////////////////////
    void render();


    ///////////////////////////////////////////////////////////
    /// Function: loadHighScore()
    /// ------------------------------------------------------
    /// Objective:
    ///     Reads the high score from "highscore.txt".
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     Reads from disk.
    ///
    /// Approach:
    ///     Open file → read integer → store in highScore.
    ///////////////////////////////////////////////////////////
    void loadHighScore();


    ///////////////////////////////////////////////////////////
    /// Function: saveHighScore()
    /// ------------------------------------------------------
    /// Objective:
    ///     Saves the highest score obtained in AI mode.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     Writes to disk (highscore.txt).
    ///
    /// Approach:
    ///     Open file → write integer → close file.
    ///////////////////////////////////////////////////////////
    void saveHighScore();


    ///////////////////////////////////////////////////////////
    /// Function: resetRound()
    /// ------------------------------------------------------
    /// Objective:
    ///     Resets the ball to the center and alternates
    ///     the direction after each point/life loss.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     Resets ball physics.
    ///
    /// Approach:
    ///     Ball.reset(centerX, centerY).
    ///////////////////////////////////////////////////////////
    void resetRound();
};

#endif
