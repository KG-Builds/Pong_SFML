#include "Ball.h"

// =============================================================
// Objective  : Initialize the ball with a size, color and speed.
// Input      : Initial X and Y coordinates.
// Output     : A fully ready ball object.
// Return     : None (constructor).
// Side effect: None.
// =============================================================
Ball::Ball(float x, float y) {

    // Set the radius of the circular ball shape to 10 pixels.
    shape.setRadius(10.f);

    // Set the fill color of the ball to white.
    shape.setFillColor(sf::Color::White);

    // Place the ball at the given coordinates.
    shape.setPosition(x, y);

    // Initialize horizontal velocity.
    // Negative means the ball starts moving toward the left.
    velocityX = -300.f;

    // Initialize vertical velocity.
    // Positive means the ball starts moving downward.
    velocityY = 300.f;
}



// =============================================================
// Objective  : Move the ball and make it bounce off walls.
// Input      : dt (delta time), time since last frame.
// Output     : Updated ball position.
// Return     : None.
// Side effect: If logic is wrong, ball may clip through screen.
// =============================================================
void Ball::update(float dt) {

    // Move the ball based on its velocity multiplied by dt.
    // dt ensures consistent speed independent of FPS.
    shape.move(velocityX * dt, velocityY * dt);

    // If ball touches top of screen (y <= 0)
    // OR touches bottom (y >= 580)
    // then reverse vertical direction.
    if (shape.getPosition().y <= 0 || shape.getPosition().y >= 580) {
        bounceY(); // Reverse Y velocity.
    }
}



// =============================================================
// Objective  : Draw the ball on the game window.
// Input      : Reference to the render window.
// Output     : Ball rendered on screen.
// Return     : None.
// Side effect: None.
// =============================================================
void Ball::draw(sf::RenderWindow& window) {

    // Render the ball shape.
    window.draw(shape);
}



// =============================================================
// Objective  : Reset ball position when a point is scored.
// Input      : new X and Y coordinates.
// Output     : Ball moves instantly to new location.
// Return     : None.
// Side effect: Ball direction flips (may confuse if unexpected).
// =============================================================
void Ball::reset(float x, float y) {

    // Move ball to the new given position.
    shape.setPosition(x, y);

    // Reverse horizontal direction so the next rally switches sides.
    velocityX = -velocityX;
}



// =============================================================
// Objective  : Reverse horizontal velocity.
// Input      : None.
// Output     : Direction change in X movement.
// Return     : None.
// Side effect: If overused, movement becomes jerky.
// =============================================================
void Ball::bounceX() {
    velocityX = -velocityX; // Flip horizontal direction.
}



// =============================================================
// Objective  : Reverse vertical velocity.
// Input      : None.
// Output     : Direction change in Y movement.
// Return     : None.
// Side effect: None.
// =============================================================
void Ball::bounceY() {
    velocityY = -velocityY; // Flip vertical direction.
}



// =============================================================
// Objective  : Provide bounding box for collision detection.
// Input      : None.
// Output     : Returns FloatRect with position + size.
// Return     : sf::FloatRect
// Side effect: None.
// =============================================================
sf::FloatRect Ball::getBounds() const {

    // Return rectangle covering the ball (for paddle collision detection).
    return shape.getGlobalBounds();
}
