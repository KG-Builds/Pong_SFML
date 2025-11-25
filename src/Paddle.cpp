#include "Paddle.h"

//////////////////////////////////////////////////////////////
/// Constructor: Paddle::Paddle
/// ---------------------------------------------------------
/// Objective:
///     Creates a paddle object at a given initial position with
///     a fixed size and movement speed.
///
/// Input Parameters:
///     float x -> Initial horizontal (X-axis) position
///     float y -> Initial vertical (Y-axis) position
///
/// Return Value:
///     None (constructor)
///
/// Side Effects:
///     - Allocates SFML rectangle shape and sets its properties.
///     - If incorrect values are passed, paddle may be placed off-screen.
///
/// Approach:
///     - Initialize a rectangular paddle of size 20x100.
///     - Set white color, assign position, and set a constant speed.
///
//////////////////////////////////////////////////////////////
Paddle::Paddle(float x, float y) {
    shape.setSize(sf::Vector2f(20, 100));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);
    speed = 300.f;
}

//////////////////////////////////////////////////////////////
/// Function: moveUp
/// ---------------------------------------------------------
/// Objective:
///     Moves the paddle upward based on delta time.
///
/// Input Parameters:
///     float dt -> Time elapsed between frames (prevents speed variations)
///
/// Return Value:
///     None
///
/// Side Effects:
///     - If misused, can cause jittery motion if dt is incorrect.
///     - Paddle will stop at upper boundary (y > 0 check).
///
/// Approach:
///     - Only move upwards if paddle is not touching the top.
///
//////////////////////////////////////////////////////////////
void Paddle::moveUp(float dt) {
    if (shape.getPosition().y > 0)
        shape.move(0, -speed * dt);
}

//////////////////////////////////////////////////////////////
/// Function: moveDown
/// ---------------------------------------------------------
/// Objective:
///     Moves the paddle downward based on delta time.
///
/// Input Parameters:
///     float dt -> Time elapsed since last frame
///
/// Return Value:
///     None
///
/// Side Effects:
///     - Incorrect dt values may cause buggy speeds.
///     - Paddle stays within window height limit (600px).
///
/// Approach:
///     - Allow movement only if paddle bottom has not crossed screen.
///
//////////////////////////////////////////////////////////////
void Paddle::moveDown(float dt) {
    if (shape.getPosition().y + shape.getSize().y < 600)
        shape.move(0, speed * dt);
}

//////////////////////////////////////////////////////////////
/// Function: draw
/// ---------------------------------------------------------
/// Objective:
///     Draws the paddle on the game window.
///
/// Input Parameters:
///     sf::RenderWindow& window -> Window where paddle is drawn
///
/// Return Value:
///     None
///
/// Side Effects:
///     - Relies on window state; if window is closed or invalid,
///       drawing will fail silently.
///     - No game logic is affected.
///
/// Approach:
///     - Simply call renderWindow.draw() using SFML.
///
//////////////////////////////////////////////////////////////
void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

//////////////////////////////////////////////////////////////
/// Function: getBounds
/// ---------------------------------------------------------
/// Objective:
///     Provide the paddle’s bounding box for collision detection.
///
/// Input Parameters:
///     None
///
/// Return Value:
///     sf::FloatRect -> Rectangle representing paddle boundaries
///
/// Side Effects:
///     None (pure accessor)
///
/// Approach:
///     - Return the global bounds of the paddle shape.
///
//////////////////////////////////////////////////////////////
sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}
