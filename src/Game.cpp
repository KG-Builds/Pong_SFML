#include "Game.h"
#include <fstream>
#include <iostream>

namespace {
    const int WINDOW_WIDTH  = 640;
    const int WINDOW_HEIGHT = 600;

    // For PvP mode: first to this score wins
    const int TARGET_SCORE  = 10;

    // For AI mode: starting number of lives
    const int START_LIVES   = 3;
}

/*
    Constructor: Game::Game()

    Objective:
        Set up the game window, initialize game objects (paddles, ball),
        load fonts, texts, high score, and prepare the menu.

    Input Parameters:
        - None (constructor).

    Return Value:
        - None.

    Side Effects:
        - Loads font from file.
        - Reads high score from disk.
        - Initializes SFML window and graphical objects.

    Approach:
        - Create window and set framerate.
        - Initialize paddles, ball, and game state.
        - Load resources (font).
        - Initialize UI texts.
        - Load high score and pass it to menu.
*/
Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
             "Pong",
             sf::Style::Titlebar | sf::Style::Close),
      state(GameState::MENU),
      mode(GameMode::PLAYER_VS_AI),
      leftPaddle(30.f, 250.f),
      rightPaddle(590.f, 250.f),
      ball(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f),
      leftScore(0),
      rightScore(0),
      highScore(0),
      lives(START_LIVES)
{
    window.setFramerateLimit(60);

    if (!font.loadFromFile("assets/font.ttf")) {
        std::cout << "Failed to load font\n";
    }

    // Score text during gameplay
    scoreText.setFont(font);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(150.f, 15.f);
    scoreText.setString("Score: 0   Lives: 3");

    // Game Over texts
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(110.f, 200.f);

    gameOverHighScoreText.setFont(font);
    gameOverHighScoreText.setCharacterSize(30);
    gameOverHighScoreText.setFillColor(sf::Color::White);
    gameOverHighScoreText.setPosition(110.f, 260.f);

    continueText.setFont(font);
    continueText.setCharacterSize(20);
    continueText.setFillColor(sf::Color::White);
    continueText.setPosition(110.f, 330.f);
    continueText.setString("Press Enter to return to Menu");

    loadHighScore();
    menu.setHighScore(highScore);
}


/*
    Function: void Game::run()

    Objective:
        Start the main game loop that processes events, updates game state,
        and renders frames.

    Input Parameters:
        - None

    Return Value:
        - void

    Side Effects:
        - Opens and runs the game loop which continues until window closes.

    Approach:
        - Use an SFML clock to calculate delta time.
        - Continuously call event processing, updating, and rendering.
*/
void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}


/*
    Function: void Game::processEvents()

    Objective:
        Handle user input such as keyboard and mouse interactions for
        menu, gameplay, and game over screen.

    Input Parameters:
        - None

    Return Value:
        - void

    Side Effects:
        - Changes game state (Menu → Playing → Game Over).
        - Detects paddle movement inputs.
        - May close the game window.

    Approach:
        - Poll events from SFML.
        - Handle menu clicks for choosing game mode.
        - Handle enter key to return from game over.
*/
void Game::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Menu mouse input
        if (state == GameState::MENU &&
            event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (menu.isAISelected(mousePos)) {
                mode = GameMode::PLAYER_VS_AI;

                leftScore = 0;
                rightScore = 0;
                lives = START_LIVES;
                scoreText.setString("Score: 0   Lives: " + std::to_string(lives));

                resetRound();
                state = GameState::PLAYING;
            }
            else if (menu.isPVPSelected(mousePos)) {
                mode = GameMode::PLAYER_VS_PLAYER;

                leftScore = 0;
                rightScore = 0;
                scoreText.setPosition(WINDOW_WIDTH / 2.f - 40.f, 20.f);
                scoreText.setString("0 : 0");

                resetRound();
                state = GameState::PLAYING;
            }
        }

        // Game over → back to menu
        if (state == GameState::GAME_OVER &&
            event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Enter) {

            state = GameState::MENU;
        }
    }
}


/*
    Function: void Game::update(float dt)

    Objective:
        Handle gameplay logic (paddle movement, AI, ball physics,
        scoring, collisions, game over conditions).

    Input Parameters:
        - float dt: delta time for frame-independent movement.

    Return Value:
        - void

    Side Effects:
        - Moves paddles and ball.
        - Updates scores and lives.
        - Triggers game over.
        - Modifies text UI.

    Approach:
        - Process player or AI paddle movement.
        - Update ball and check collisions.
        - Apply scoring rules depending on game mode.
        - Update score display.
        - Check for end-of-game conditions.
*/
void Game::update(float dt) {
    if (state != GameState::PLAYING)
        return;

    // ---------- Controls & AI ----------
    if (mode == GameMode::PLAYER_VS_PLAYER) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            leftPaddle.moveUp(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            leftPaddle.moveDown(dt);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            rightPaddle.moveUp(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            rightPaddle.moveDown(dt);
    }
    else if (mode == GameMode::PLAYER_VS_AI) {
        // Player controls left paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            leftPaddle.moveUp(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            leftPaddle.moveDown(dt);

        // AI moves right paddle to follow ball
        float ballCenterY   = ball.getBounds().top + ball.getBounds().height / 2.f;
        float paddleCenterY = rightPaddle.getBounds().top + 50.f;

        if (ballCenterY > paddleCenterY)
            rightPaddle.moveDown(dt);
        else if (ballCenterY < paddleCenterY)
            rightPaddle.moveUp(dt);
    }

    // ---------- Ball update ----------
    ball.update(dt);

    // ---------- Paddle collisions ----------
    if (ball.getBounds().intersects(leftPaddle.getBounds())) {
        ball.bounceX();
    }
    if (ball.getBounds().intersects(rightPaddle.getBounds())) {
        ball.bounceX();
    }

    // ---------- Scoring ----------
    sf::FloatRect ballBounds = ball.getBounds();

    if (mode == GameMode::PLAYER_VS_AI) {
        if (ballBounds.left + ballBounds.width < 0) {
            lives--;
            resetRound();
        }
        if (ballBounds.left > WINDOW_WIDTH) {
            leftScore++;
            resetRound();
        }
    }
    else {
        if (ballBounds.left + ballBounds.width < 0) {
            rightScore++;
            resetRound();
        }
        if (ballBounds.left > WINDOW_WIDTH) {
            leftScore++;
            resetRound();
        }
    }

    // ---------- Update score text ----------
    if (mode == GameMode::PLAYER_VS_AI) {
        scoreText.setPosition(150.f, 15.f);
        scoreText.setString(
            "Score: " + std::to_string(leftScore) +
            "   Lives: " + std::to_string(lives)
        );
    }
    else {
        scoreText.setPosition(WINDOW_WIDTH / 2.f - 40.f, 20.f);
        scoreText.setString(
            std::to_string(leftScore) + " : " + std::to_string(rightScore)
        );
    }

    // ---------- Game Over ----------
    if (mode == GameMode::PLAYER_VS_AI) {
        if (lives <= 0) {
            state = GameState::GAME_OVER;

            if (leftScore > highScore) {
                highScore = leftScore;
                saveHighScore();
            }
            menu.setHighScore(highScore);

            gameOverText.setString("Your Score: " + std::to_string(leftScore));
            gameOverHighScoreText.setString(
                "High Score (vs AI): " + std::to_string(highScore)
            );
        }
    }
    else {
        if (leftScore >= TARGET_SCORE || rightScore >= TARGET_SCORE) {
            state = GameState::GAME_OVER;

            if (leftScore > rightScore)
                gameOverText.setString("Player 1 Wins!!!");
            else
                gameOverText.setString("Player 2 Wins!!!");

            gameOverHighScoreText.setString("");
        }
    }
}


/*
    Function: void Game::render()

    Objective:
        Draw the menu, gameplay, or game over screen depending on the current state.

    Input Parameters:
        - None

    Return Value:
        - void

    Side Effects:
        - Clears and updates the contents of the window each frame.

    Approach:
        - Clear the screen.
        - Draw appropriate objects depending on state.
        - Display updated frame.
*/
void Game::render() {
    window.clear(sf::Color::Black);

    if (state == GameState::MENU) {
        menu.draw(window);
    }
    else if (state == GameState::PLAYING) {
        leftPaddle.draw(window);
        rightPaddle.draw(window);
        ball.draw(window);
        window.draw(scoreText);
    }
    else if (state == GameState::GAME_OVER) {
        window.draw(gameOverText);
        if (!gameOverHighScoreText.getString().isEmpty())
            window.draw(gameOverHighScoreText);
        window.draw(continueText);
    }

    window.display();
}


/*
    Function: void Game::loadHighScore()

    Objective:
        Load the high score from a text file.

    Input Parameters:
        - None

    Return Value:
        - void

    Side Effects:
        - Reads from disk.
        - Changes the highScore variable.

    Approach:
        - Open "highscore.txt"
        - Read integer value if file exists.
*/
void Game::loadHighScore() {
    std::ifstream file("highscore.txt");
    highScore = 0;

    if (file) {
        file >> highScore;
    }
}


/*
    Function: void Game::saveHighScore()

    Objective:
        Save the current high score to disk.

    Input Parameters:
        - None

    Return Value:
        - void

    Side Effects:
        - Writes to disk (overwrites existing file).

    Approach:
        - Open "highscore.txt" for output.
        - Write the highScore value.
*/
void Game::saveHighScore() {
    std::ofstream file("highscore.txt");
    if (file) {
        file << highScore;
    }
}


/*
    Function: void Game::resetRound()

    Objective:
        Reset the ball to the center of the screen and alternate serve direction.

    Input Parameters:
        - None

    Return Value:
        - void

    Side Effects:
        - Resets ball position.
        - Reverses ball velocityX.

    Approach:
        - Call ball.reset() with center coordinates.
*/
void Game::resetRound() {
    ball.reset(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
}
