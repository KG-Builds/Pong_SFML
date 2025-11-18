#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Paddle.h"
#include "Ball.h"

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

enum class GameMode {
    PLAYER_VS_AI,
    PLAYER_VS_PLAYER
};


class Game {
private:
    sf::RenderWindow window;
    GameState state;
    GameMode mode;     // user-chosen mode

    
    Menu menu;
    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;
    
    int leftScore;
    int rightScore;
    int highScore; // only from vs-AI matches
    int lives;
    
    sf::Font font;
    sf::Text scoreText;

    // Game Over UI
    sf::Text gameOverText;
    sf::Text gameOverHighScoreText;
    sf::Text continueText;
    
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    void loadHighScore();
    void saveHighScore();
    void resetRound();
};

#endif
