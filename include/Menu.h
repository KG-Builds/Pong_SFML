#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Paddle.h"
#include "Ball.h"

////////////////////////////////////////////////////////////////
/// Enum: GameState
/// -----------------------------------------------------------
/// Objective:
///     Represents the primary stages/screens of the game.
/// 
/// Values:
///     MENU       – The main menu screen.
///     PLAYING    – The game is currently in progress.
///     GAME_OVER  – The game has ended; shows results.
/// 
/// Side Notes:
///     Used by the Game class to control rendering
///     and behavior depending on current mode.
////////////////////////////////////////////////////////////////
enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

////////////////////////////////////////////////////////////////
/// Enum: GameMode
/// -----------------------------------------------------------
/// Objective:
///     Defines which type of match is being played.
///
/// Values:
///     PLAYER_VS_AI      – Player competes against computer AI.
///     PLAYER_VS_PLAYER  – Two human players using keyboard.
///
/// Side Notes:
///     AI mode awards high scores; PVP does not.
////////////////////////////////////////////////////////////////
enum class GameMode {
    PLAYER_VS_AI,
    PLAYER_VS_PLAYER
};

////////////////////////////////////////////////////////////////
/// Class: Game
/// -----------------------------------------------------------
/// Objective:
///     The central controller for the Pong game. It manages:
///         - Window creation
///         - Input handling
///         - Game updates & physics
///         - Rendering
///         - Menu navigation
///         - Player/AI behavior
///         - Collision handling
///         - High score system (AI mode)
///
/// Responsibilities:
///     - Maintain game state machine.
///     - Update paddles, ball, scores, lives.
///     - Display menu, HUD, and game-over screens.
///     - Manage file operations for high score.
///
/// Side Effects:
///     - Opens graphical window.
///     - Loads external font file.
///     - Reads/writes "highscore.txt".
///     - Draws frames to screen every loop.
///
/// Used By:
///     main.cpp — calls Game.run() to start the game.
////////////////////////////////////////////////////////////////
class Game {
private:
    sf::RenderWindow window;   // Main window for rendering everything
    GameState state;           // Current state (Menu/Playing/Game Over)
    GameMode mode;             // Mode chosen by user (AI or PVP)

    Menu menu;                 // Menu handler/UI
    Paddle leftPaddle;         // Player 1 paddle
    Paddle rightPaddle;        // Player 2 or AI paddle
    Ball ball;                 // Ball used in gameplay

    int leftScore;             // Score of left paddle
    int rightScore;            // Score of right paddle
    int highScore;             // Highest score achieved in vs-AI mode
    int lives;                 // Player lives (only in AI mode)

    sf::Font font;             // Main font for score & UI
    sf::Text scoreText;        // Score display text

    // Game Over UI elements
    sf::Text gameOverText;
    sf::Text gameOverHighScoreText;
    sf::Text continueText;

public:

    ////////////////////////////////////////////////////////////
    /// Constructor: Game()
    /// --------------------------------------------------------
    /// Objective:
    ///     Initializes the game engine, loads resources,
    ///     prepares paddles/ball, initializes UI and variables.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     Constructor — no return value
    ///
    /// Side Effects:
    ///     - Creates an SFML window
    ///     - Loads font from disk
    ///     - Reads high score file
    ///
    /// Approach:
    ///     Set up window → initialize objects → center ball →
    ///     load fonts → configure texts → load highscore.
    ////////////////////////////////////////////////////////////
    Game();

    ////////////////////////////////////////////////////////////
    /// Function: run()
    /// --------------------------------------------------------
    /// Objective:
    ///     Executes the main game loop. Repeats:
    ///         - processEvents()
    ///         - update(dt)
    ///         - render()
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     Redraws screen every frame and updates physics.
    ///
    /// Approach:
    ///     Use sf::Clock to compute delta time for smooth motion.
    ////////////////////////////////////////////////////////////
    void run();

private:

    ////////////////////////////////////////////////////////////
    /// Function: processEvents()
    /// --------------------------------------------------------
    /// Objective:
    ///     Handles all keyboard/mouse/window events.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Moves paddles according to player input
    ///     - Navigates through menu
    ///     - Closes window if requested
    ///
    /// Approach:
    ///     Poll SFML events → interpret → update game state.
    ////////////////////////////////////////////////////////////
    void processEvents();

    ////////////////////////////////////////////////////////////
    /// Function: update(float dt)
    /// --------------------------------------------------------
    /// Objective:
    ///     Updates:
    ///         - Ball movement & physics
    ///         - Paddle movement (Player/AI)
    ///         - Collision logic
    ///         - Score/lives
    ///         - Game-over detection
    ///
    /// Input:
    ///     dt — time elapsed since last frame
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Moves objects
    ///     - Changes score/lives
    ///     - Triggers GAME_OVER state
    ///
    /// Approach:
    ///     Move paddles → AI logic → ball update →
    ///     detect collisions → update UI.
    ////////////////////////////////////////////////////////////
    void update(float dt);

    ////////////////////////////////////////////////////////////
    /// Function: render()
    /// --------------------------------------------------------
    /// Objective:
    ///     Draws all current game objects to the screen.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     Renders to window using double buffering.
    ///
    /// Approach:
    ///     window.clear() → draw state-specific elements →
    ///     window.display().
    ////////////////////////////////////////////////////////////
    void render();

    ////////////////////////////////////////////////////////////
    /// Function: loadHighScore()
    /// --------------------------------------------------------
    /// Objective:
    ///     Loads highest AI-mode score from "highscore.txt".
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     Reads from disk.
    ////////////////////////////////////////////////////////////
    void loadHighScore();

    ////////////////////////////////////////////////////////////
    /// Function: saveHighScore()
    /// --------------------------------------------------------
    /// Objective:
    ///     Saves current high score to disk.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     Writes to "highscore.txt".
    ////////////////////////////////////////////////////////////
    void saveHighScore();

    ////////////////////////////////////////////////////////////
    /// Function: resetRound()
    /// --------------------------------------------------------
    /// Objective:
    ///     Reset ball to center and prepare for next rally.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     Changes ball velocity and position.
    ////////////////////////////////////////////////////////////
    void resetRound();
};

#endif
