#include "Game.h"
#include <fstream>
#include <iostream>



// ===============================================================================
// Objective  : Constructor initializes the game window, paddles, ball, scores,
//              loads fonts, high scores, and sets initial menu state.
// Input      : None (called automatically when Game object is created).
// Output     : A fully ready game instance with initialized components.
// Return     : None (constructor).
// Side effect: If font file is missing, text rendering may fail.
// ===============================================================================
Game::Game() 
    : window(sf::VideoMode(640, 600), "Pong", sf::Style::Titlebar | sf::Style::Close), // Create window with size & title
      state(GameState::MENU),       // Start game in MENU state
      leftPaddle(30, 250),          // Initialize left paddle at (30, 250)
      rightPaddle(590, 250),        // Initialize right paddle at (590, 250)
      ball(320, 300),               // Initialize ball at center
      leftScore(0),                 // Set initial player scores to 0
      rightScore(0),
      highScore(0)                  // Default high score = 0
{
    window.setFramerateLimit(60);   // Limit FPS to 60 for stable gameplay

    // Load font for score text
    if (!font.loadFromFile("assets/font.ttf")) {
        std::cout << "Failed to load font\n"; // Print error if missing
    }

    // Configure score text
    scoreText.setFont(font);                // Assign font
    scoreText.setCharacterSize(30);         // Size of displayed text
    scoreText.setFillColor(sf::Color::White); // Text color
    scoreText.setPosition(280, 20);         // Score position on screen
    scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));

    loadHighScore();     // Read high score from file
    menu.setHighScore(highScore); // Send it to menu to display
}



// ===============================================================================
// Objective  : Main game loop controlling events, updates, and rendering.
// Input      : None.
// Output     : Continuously updated game screen.
// Return     : None.
// Side effect: Infinite loop until window closes.
// ===============================================================================
void Game::run() {
    sf::Clock clock; // Measures frame time (delta time)

    while (window.isOpen()) { // Continue while window exists
        float dt = clock.restart().asSeconds(); // Time since last frame

        processEvents(); // Handle input
        update(dt);      // Update game logic
        render();        // Draw graphics on screen
    }
}



// ===============================================================================
// Objective  : Handle keyboard, mouse, and window events.
// Input      : None (reads event queue).
// Output     : State changes such as starting a game or closing window.
// Return     : None.
// Side effect: Clicking menu items can reset game state.
// ===============================================================================
void Game::processEvents() {
    sf::Event event; // Event storage

    while (window.pollEvent(event)) { // Read all events
        if (event.type == sf::Event::Closed)
            window.close(); // Close window if X button clicked

        // Handle menu click to start new game
        if (state == GameState::MENU && event.type == sf::Event::MouseButtonPressed) {

            sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Mouse coordinates

            if (menu.isNewGameClicked(mousePos)) { // Check if Start button clicked
                leftScore = 0;   // Reset scores
                rightScore = 0;
                ball.reset(320, 300); // Reset ball
                state = GameState::PLAYING; // Move to gameplay state
            }
        }
    }
}



// ===============================================================================
// Objective  : Update game state: movement, collisions, scoring.
// Input      : dt (float) — time since last frame.
// Output     : Updated ball/paddle positions and scores.
// Return     : None.
// Side effect: Incorrect dt may make movement too fast or slow.
// ===============================================================================
void Game::update(float dt) {

    if (state == GameState::PLAYING) { // Only update if game is running

        // ----- PADDLE CONTROLS -----
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            leftPaddle.moveUp(dt);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            leftPaddle.moveDown(dt);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            rightPaddle.moveUp(dt);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            rightPaddle.moveDown(dt);

        // ----- UPDATE BALL POSITION -----
        ball.update(dt);

        // ----- COLLISION WITH LEFT PADDLE -----
        if (ball.getBounds().intersects(leftPaddle.getBounds()))
            ball.bounceX(); // Reverse horizontal direction

        // ----- COLLISION WITH RIGHT PADDLE -----
        if (ball.getBounds().intersects(rightPaddle.getBounds()))
            ball.bounceX();

        // ----- SCORING LOGIC -----
        if (ball.getBounds().left < 0) { // Ball passed left boundary
            rightScore++; // Right player scores
            ball.reset(320, 300);
        }

        if (ball.getBounds().left > 640) { // Ball passed right boundary
            leftScore++; // Left player scores
            ball.reset(320, 300);
        }

        // Update score text display
        scoreText.setString(
            std::to_string(leftScore) + " : " + std::to_string(rightScore)
        );

        // ----- END GAME CONDITION -----
        if (leftScore == 10 || rightScore == 10) {

            int finalScore = std::max(leftScore, rightScore); // Winner score

            if (finalScore > highScore) { // New high score?
                highScore = finalScore;
                saveHighScore(); // Save to file
            }

            menu.setHighScore(highScore); // Update menu display
            state = GameState::MENU; // Go back to menu
        }
    }
}



// ===============================================================================
// Objective  : Draw the current frame on the window.
// Input      : None.
// Output     : Visual rendering of menu or game.
// Return     : None.
// Side effect: None.
// ===============================================================================
void Game::render() {
    window.clear(sf::Color::Black); // Clear screen with black

    if (state == GameState::MENU) {
        menu.draw(window); // Draw menu
    }
    else if (state == GameState::PLAYING) {
        leftPaddle.draw(window);   // Draw left paddle
        rightPaddle.draw(window);  // Draw right paddle
        ball.draw(window);         // Draw ball
        window.draw(scoreText);    // Draw score
    }

    window.display(); // Present frame to screen
}



// ===============================================================================
// Objective  : Load high score from text file.
// Input      : None.
// Output     : Updates highScore variable.
// Return     : None.
// Side effect: If file does not exist, highScore remains 0.
// ===============================================================================
void Game::loadHighScore() {
    std::ifstream file("highscore.txt"); // Open file for reading
    highScore = 0; // Default value

    if (file)
        file >> highScore; // Read stored high score
}



// ===============================================================================
// Objective  : Save high score to file.
// Input      : None.
// Output     : Writes highScore to text file.
// Return     : None.
// Side effect: If disk is full, score may fail to save.
// ===============================================================================
void Game::saveHighScore() {
    std::ofstream file("highscore.txt"); // Open file for writing
    file << highScore; // Save updated score
}
