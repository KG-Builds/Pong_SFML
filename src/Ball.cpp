#include "Ball.h"

/*
    Constructor: Ball::Ball(float x, float y)

    Objective:
        Initialize the ball object with a default radius, color, position,
        and initial velocities.

    Input Parameters:
        - float x: The starting X position of the ball.
        - float y: The starting Y position of the ball.

    Return Value:
        - None (constructor).

    Side Effects:
        - Initializes velocity values which affect ball movement throughout the game.

    Approach:
        - Set visual properties of the ball (radius, color).
        - Place the ball at the given starting position.
        - Assign default velocity in both X and Y directions.
*/
Ball::Ball(float x, float y) {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);

    velocityX = -300.f;
    velocityY = 300.f;
}


/*
    Function: void Ball::update(float dt)

    Objective:
        Update the ball's position every frame and handle top/bottom wall collision.

    Input Parameters:
        - float dt: Delta time (time elapsed between frames).

    Return Value:
        - void

    Side Effects:
        - Modifies the internal position of the ball.
        - May change velocityY if the ball hits the top or bottom boundary.

    Approach:
        - Move the ball based on velocity and delta time.
        - Check collision with top (y <= 0) or bottom boundary (y >= 580).
        - If collision occurs, reverse Y velocity using bounceY().
*/
void Ball::update(float dt) {
    shape.move(velocityX * dt, velocityY * dt);

    if (shape.getPosition().y <= 0 || shape.getPosition().y >= 580) {
        bounceY();
    }
}


/*
    Function: void Ball::draw(sf::RenderWindow& window)

    Objective:
        Render the ball onto the game window.

    Input Parameters:
        - sf::RenderWindow& window: The window where the ball is drawn.

    Return Value:
        - void

    Side Effects:
        - None.

    Approach:
        - Simply draw the ball shape on the given SFML window.
*/
void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}


/*
    Function: void Ball::reset(float x, float y)

    Objective:
        Reset the ball to a specified position and reverse its X direction.

    Input Parameters:
        - float x: New X position.
        - float y: New Y position.

    Return Value:
        - void

    Side Effects:
        - Reverses velocityX, which changes ball direction.
        - Teleports the ball to a new position.

    Approach:
        - Set the new position.
        - Reverse horizontal velocity to start movement toward the scoring player.
*/
void Ball::reset(float x, float y) {
    shape.setPosition(x, y);
    velocityX = -velocityX;
}


/*
    Function: void Ball::bounceX()

    Objective:
        Reverse the horizontal direction of the ball.

    Input Parameters:
        - None

    Return Value:
        - void

    Side Effects:
        - Changes velocityX, affecting movement direction.

    Approach:
        - Multiply X velocity by -1.
*/
void Ball::bounceX() {
    velocityX = -velocityX;
}


/*
    Function: void Ball::bounceY()

    Objective:
        Reverse the vertical direction of the ball.

    Input Parameters:
        - None

    Return Value:
        - void

    Side Effects:
        - Changes velocityY, affecting movement direction.

    Approach:
        - Multiply Y velocity by -1.
*/
void Ball::bounceY() {
    velocityY = -velocityY;
}


/*
    Function: sf::FloatRect Ball::getBounds() const

    Objective:
        Get the bounding box of the ball for collision detection.

    Input Parameters:
        - None

    Return Value:
        - sf::FloatRect: The rectangle representing ball boundaries.

    Side Effects:
        - None.

    Approach:
        - Return SFML’s global bounds for the circle shape.
*/
sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}
