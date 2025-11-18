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

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

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

void Game::update(float dt) {
    if (state != GameState::PLAYING)
        return;

    // ---------- Controls & AI ----------

    if (mode == GameMode::PLAYER_VS_PLAYER) {
        // Player 1 (left) – W/S
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            leftPaddle.moveUp(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            leftPaddle.moveDown(dt);

        // Player 2 (right) – Up/Down
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

        // Simple AI for right paddle
        float ballCenterY   = ball.getBounds().top + ball.getBounds().height / 2.f;
        float paddleCenterY = rightPaddle.getBounds().top + 50.f; // half paddle height

        if (ballCenterY > paddleCenterY)
            rightPaddle.moveDown(dt);
        else if (ballCenterY < paddleCenterY)
            rightPaddle.moveUp(dt);
    }

    // ---------- Ball update ----------
    ball.update(dt);

    // ---------- Collisions with paddles ----------
    if (ball.getBounds().intersects(leftPaddle.getBounds())) {
        ball.bounceX();
    }
    if (ball.getBounds().intersects(rightPaddle.getBounds())) {
        ball.bounceX();
    }

    // ---------- Scoring logic ----------
    sf::FloatRect ballBounds = ball.getBounds();

    if (mode == GameMode::PLAYER_VS_AI) {
        // Ball passed left edge → you lose a life
        if (ballBounds.left + ballBounds.width < 0) {
            lives--;
            resetRound();
        }

        // Ball passed right edge → you gain a point
        if (ballBounds.left > WINDOW_WIDTH) {
            leftScore++;
            resetRound();
        }
    }
    else { // PLAYER_VS_PLAYER
        // Left miss → right scores
        if (ballBounds.left + ballBounds.width < 0) {
            rightScore++;
            resetRound();
        }

        // Right miss → left scores
        if (ballBounds.left > WINDOW_WIDTH) {
            leftScore++;
            resetRound();
        }
    }

    // ---------- Update on-screen score text ----------
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

    // ---------- Game Over conditions ----------
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
    else { // PvP
        if (leftScore >= TARGET_SCORE || rightScore >= TARGET_SCORE) {
            state = GameState::GAME_OVER;

            if (leftScore > rightScore)
                gameOverText.setString("Player 1 Wins!!!");
            else
                gameOverText.setString("Player 2 Wins!!!");

            gameOverHighScoreText.setString(""); // no highscore for PvP
        }
    }
}

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

void Game::loadHighScore() {
    std::ifstream file("highscore.txt");
    highScore = 0;

    if (file) {
        file >> highScore;
    }
}

void Game::saveHighScore() {
    std::ofstream file("highscore.txt");
    if (file) {
        file << highScore;
    }
}

void Game::resetRound() {
    // Just reset ball to center, reverse X so it alternates serve
    ball.reset(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
}


// =====================================================================

// #include "Game.h"
// #include <fstream>
// #include <iostream>

// namespace {
//     const int WINDOW_WIDTH  = 640;
//     const int WINDOW_HEIGHT = 600;
//     const int TARGET_SCORE  = 10;   // "dropout" value – whoever reaches this wins
// }

// Game::Game()
//     : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
//              "Pong",
//              sf::Style::Titlebar | sf::Style::Close),
//       state(GameState::MENU),
//       mode(GameMode::PLAYER_VS_AI),
//       leftPaddle(30.f, 250.f),
//       rightPaddle(590.f, 250.f),
//       ball(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f),
//       leftScore(0),
//       rightScore(0),
//       highScore(0)
// {
//     window.setFramerateLimit(60);

//     if (!font.loadFromFile("assets/font.ttf")) {
//         std::cout << "Failed to load font\n";
//     }

//     // Score text during gameplay
//     scoreText.setFont(font);
//     scoreText.setCharacterSize(30);
//     scoreText.setFillColor(sf::Color::White);
//     scoreText.setPosition(WINDOW_WIDTH / 2.f - 40.f, 20.f);
//     scoreText.setString("0 : 0");

//     // Game Over texts
//     gameOverText.setFont(font);
//     gameOverText.setCharacterSize(40);
//     gameOverText.setFillColor(sf::Color::White);
//     gameOverText.setPosition(130.f, 200.f);

//     gameOverHighScoreText.setFont(font);
//     gameOverHighScoreText.setCharacterSize(30);
//     gameOverHighScoreText.setFillColor(sf::Color::White);
//     gameOverHighScoreText.setPosition(130.f, 260.f);

//     continueText.setFont(font);
//     continueText.setCharacterSize(20);
//     continueText.setFillColor(sf::Color::White);
//     continueText.setPosition(130.f, 330.f);
//     continueText.setString("Press Enter to return to Menu");

//     loadHighScore();
//     menu.setHighScore(highScore);
// }

// void Game::run() {
//     sf::Clock clock;

//     while (window.isOpen()) {
//         float dt = clock.restart().asSeconds();

//         processEvents();
//         update(dt);
//         render();
//     }
// }

// void Game::processEvents() {
//     sf::Event event;

//     while (window.pollEvent(event)) {
//         if (event.type == sf::Event::Closed) {
//             window.close();
//         }

//         if (state == GameState::MENU &&
//             event.type == sf::Event::MouseButtonPressed &&
//             event.mouseButton.button == sf::Mouse::Left) {

//             sf::Vector2i mousePos = sf::Mouse::getPosition(window);

//             if (menu.isAISelected(mousePos)) {
//                 mode = GameMode::PLAYER_VS_AI;
//                 leftScore = rightScore = 0;
//                 scoreText.setString("0 : 0");
//                 resetRound();
//                 state = GameState::PLAYING;
//             }
//             else if (menu.isPVPSelected(mousePos)) {
//                 mode = GameMode::PLAYER_VS_PLAYER;
//                 leftScore = rightScore = 0;
//                 scoreText.setString("0 : 0");
//                 resetRound();
//                 state = GameState::PLAYING;
//             }
//         }

//         if (state == GameState::GAME_OVER &&
//             event.type == sf::Event::KeyPressed &&
//             event.key.code == sf::Keyboard::Enter) {

//             state = GameState::MENU;
//         }
//     }
// }

// void Game::update(float dt) {
//     if (state != GameState::PLAYING)
//         return;

//     // --- Controls & AI ---

//     if (mode == GameMode::PLAYER_VS_PLAYER) {
//         // Player 1 (left paddle) – W/S
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//             leftPaddle.moveUp(dt);
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//             leftPaddle.moveDown(dt);

//         // Player 2 (right paddle) – Up/Down
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//             rightPaddle.moveUp(dt);
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//             rightPaddle.moveDown(dt);
//     }
//     else if (mode == GameMode::PLAYER_VS_AI) {
//         // Player controls left paddle – W/S
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//             leftPaddle.moveUp(dt);
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//             leftPaddle.moveDown(dt);

//         // Simple AI for right paddle (tracks ball's vertical center)
//         float ballCenterY = ball.getBounds().top + ball.getBounds().height / 2.f;
//         float paddleCenterY = rightPaddle.getBounds().top + 50.f; // half paddle height

//         if (ballCenterY > paddleCenterY)
//             rightPaddle.moveDown(dt);
//         else if (ballCenterY < paddleCenterY)
//             rightPaddle.moveUp(dt);
//     }

//     // --- Ball update ---
//     ball.update(dt);

//     // --- Collisions with paddles ---
//     if (ball.getBounds().intersects(leftPaddle.getBounds())) {
//         ball.bounceX();
//     }
//     if (ball.getBounds().intersects(rightPaddle.getBounds())) {
//         ball.bounceX();
//     }

//     // --- Scoring logic ---
//     sf::FloatRect ballBounds = ball.getBounds();

//     // Ball passed left edge
//     if (ballBounds.left + ballBounds.width < 0) {
//         rightScore++;
//         resetRound();
//     }

//     // Ball passed right edge
//     if (ballBounds.left > WINDOW_WIDTH) {
//         leftScore++;
//         resetRound();
//     }

//     // Update score text
//     scoreText.setString(
//         std::to_string(leftScore) + " : " + std::to_string(rightScore)
//     );

//     // --- Win / Game Over ---
//     if (leftScore >= TARGET_SCORE || rightScore >= TARGET_SCORE) {

//         state = GameState::GAME_OVER;

//         if (mode == GameMode::PLAYER_VS_AI) {
//             int userScore = leftScore; // user is always left side

//             if (userScore > highScore) {
//                 highScore = userScore;
//                 saveHighScore();
//             }
//             menu.setHighScore(highScore);

//             gameOverText.setString("Your Score: " + std::to_string(userScore));
//             gameOverHighScoreText.setString(
//                 "High Score (vs AI): " + std::to_string(highScore)
//             );
//         }
//         else { // PLAYER_VS_PLAYER
//             if (leftScore > rightScore)
//                 gameOverText.setString("Player 1 Wins!!!");
//             else
//                 gameOverText.setString("Player 2 Wins!!!");

//             // No high score for PvP
//             gameOverHighScoreText.setString("");
//         }
//     }
// }

// void Game::render() {
//     window.clear(sf::Color::Black);

//     if (state == GameState::MENU) {
//         menu.draw(window);
//     }
//     else if (state == GameState::PLAYING) {
//         leftPaddle.draw(window);
//         rightPaddle.draw(window);
//         ball.draw(window);
//         window.draw(scoreText);
//     }
//     else if (state == GameState::GAME_OVER) {
//         window.draw(gameOverText);
//         if (!gameOverHighScoreText.getString().isEmpty())
//             window.draw(gameOverHighScoreText);
//         window.draw(continueText);
//     }

//     window.display();
// }

// void Game::loadHighScore() {
//     std::ifstream file("highscore.txt");
//     highScore = 0;

//     if (file) {
//         file >> highScore;
//     }
// }

// void Game::saveHighScore() {
//     std::ofstream file("highscore.txt");
//     if (file) {
//         file << highScore;
//     }
// }

// void Game::resetRound() {
//     // Center ball and paddles
//     ball.reset(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
//     // Optionally also reset paddles to center
//     // (Paddle currently doesn't have a direct setter, so you can add one later if you like)
// }

//==============================================================================


// #include "Game.h"
// #include <fstream>
// #include <iostream>

// Game::Game()
//     : window(sf::VideoMode(640, 600), 
//             "Pong",
//             sf::Style::Titlebar | sf::Style::Close),
//       state(GameState::MENU),
//       leftPaddle(30, 250),
//       rightPaddle(590, 250),
//       ball(320, 300),
//       leftScore(0),
//       rightScore(0),
//       highScore(0)
// {
//     window.setFramerateLimit(60);

//     if (!font.loadFromFile("assets/font.ttf"))
//     {
//         std::cout << "Failed to load font\n";
//     }

//     scoreText.setFont(font);
//     scoreText.setCharacterSize(30);
//     scoreText.setFillColor(sf::Color::White);
//     scoreText.setPosition(280, 20);
//     scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));

//     loadHighScore();
//     menu.setHighScore(highScore);
// }

// void Game::run()
// {
//     sf::Clock clock;

//     while (window.isOpen())
//     {
//         float dt = clock.restart().asSeconds();

//         processEvents();
//         update(dt);
//         render();
//     }
// }

// void Game::processEvents()
// {
//     sf::Event event;

//     while (window.pollEvent(event))
//     {
//         if (event.type == sf::Event::Closed)
//             window.close();

//         if (state == GameState::MENU && event.type == sf::Event::MouseButtonPressed)
//         {
//             sf::Vector2i mousePos = sf::Mouse::getPosition(window);

//             // if (menu.isNewGameClicked(mousePos))
//             // {
//             //     leftScore = 0;
//             //     rightScore = 0;
//             //     ball.reset(320, 300);
//             //     state = GameState::PLAYING;
//             // }

//             if (menu.isAISelected(mousePos))
//             {
//                 mode = GameMode::PLAYER_VS_AI;
//                 leftScore = rightScore = 0;
//                 ball.reset(320, 300);
//                 state = GameState::PLAYING;
//             }

//             if (menu.isPVPSelected(mousePos))
//             {
//                 mode = GameMode::PLAYER_VS_PLAYER;
//                 leftScore = rightScore = 0;
//                 ball.reset(320, 300);
//                 state = GameState::PLAYING;
//             }
//         }
//         if (state == GameState::GAME_OVER &&
//             event.type == sf::Event::KeyPressed &&
//             event.key.code == sf::Keyboard::Enter)
//         {

//             state = GameState::MENU;
//         }
//     }
// }

// void Game::update(float dt)
// {
//     if (state == GameState::PLAYING)
//     {

//         // Paddle movement: W/S and UP/DOWN
//         // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//         //     leftPaddle.moveUp(dt);
//         // if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//         //     leftPaddle.moveDown(dt);

//         // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//         //     rightPaddle.moveUp(dt);
//         // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//         //     rightPaddle.moveDown(dt);

//         if (mode == GameMode::PLAYER_VS_PLAYER)
//         {
//             // Player 1 (W/S)
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//                 leftPaddle.moveUp(dt);
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//                 leftPaddle.moveDown(dt);

//             // Player 2 (Up/Down)
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//                 rightPaddle.moveUp(dt);
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//                 rightPaddle.moveDown(dt);
//         }

//         if (mode == GameMode::PLAYER_VS_AI)
//         {
//             // Player controls left only
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//                 leftPaddle.moveUp(dt);
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//                 leftPaddle.moveDown(dt);

//             // Simple AI for right paddle
//             float ballCenter = ball.getBounds().top + ball.getBounds().height / 2;
//             float paddleCenter = rightPaddle.getBounds().top + 50;

//             if (ballCenter > paddleCenter)
//                 rightPaddle.moveDown(dt);
//             else
//                 rightPaddle.moveUp(dt);
//         }

//         // Update ball
//         ball.update(dt);

//         // Collision with paddles
//         if (ball.getBounds().intersects(leftPaddle.getBounds()))
//             ball.bounceX();
//         if (ball.getBounds().intersects(rightPaddle.getBounds()))
//             ball.bounceX();

//         // Scoring logic
//         if (ball.getBounds().left < 0)
//         {
//             rightScore++;
//             ball.reset(320, 300);
//         }

//         if (ball.getBounds().left > 640)
//         {
//             leftScore++;
//             ball.reset(320, 300);
//         }

//         // Update score text
//         scoreText.setString(
//             std::to_string(leftScore) + " : " + std::to_string(rightScore));

//         // End game condition
//         // if (leftScore == 10 || rightScore == 10)
//         // {
//         //     int finalScore = std::max(leftScore, rightScore);

//         //     if (finalScore > highScore)
//         //     {
//         //         highScore = finalScore;
//         //         saveHighScore();
//         //     }

//         //     menu.setHighScore(highScore);
//         //     state = GameState::MENU;
//         // }

//         if (leftScore == 10 || rightScore == 10)
//         {

//             state = GameState::GAME_OVER;

//             if (mode == GameMode::PLAYER_VS_AI)
//             {
//                 int userScore = leftScore; // user always left
//                 if (userScore > highScore)
//                 {
//                     highScore = userScore;
//                     saveHighScore();
//                 }

//                 gameOverText.setString("Your Score: " + std::to_string(userScore));

//                 gameOverHighScoreText.setString("High Score: " + std::to_string(highScore));
//             }
//             else
//             {
//                 if (leftScore > rightScore)
//                     gameOverText.setString("Player 1 Wins!!!");
//                 else
//                     gameOverText.setString("Player 2 Wins!!!");

//                 gameOverHighScoreText.setString(""); // hide this
//             }

//             continueText.setString("Press Enter to return to Menu");
//         }
//     }
// }

// void Game::render()
// {
//     window.clear(sf::Color::Black);

//     if (state == GameState::MENU)
//     {
//         menu.draw(window);
//     }
//     else if (state == GameState::PLAYING)
//     {
//         leftPaddle.draw(window);
//         rightPaddle.draw(window);
//         ball.draw(window);
//         window.draw(scoreText);
//     }
//     else if (state == GameState::GAME_OVER)
//     {
//         window.draw(gameOverText);
//         window.draw(gameOverHighScoreText);
//         window.draw(continueText);
//     }

//     window.display();
// }

// void Game::loadHighScore()
// {
//     std::ifstream file("highscore.txt");
//     highScore = 0;

//     if (file)
//         file >> highScore;
// }

// void Game::saveHighScore()
// {
//     std::ofstream file("highscore.txt");
//     file << highScore;
// }

