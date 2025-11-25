#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////
/// Class: Ball
/// ---------------------------------------------------------
/// Purpose:
///     Represents the moving ball in the Pong game.
///     Handles ball physics, movement, bouncing, drawing,
///     and collision boundaries.
///
/// Description:
///     This class contains:
///       - The ball shape (SFML CircleShape)
///       - Its horizontal & vertical velocities
///       - Functions to update movement, reset position,
///         bounce off paddles/walls, and return bounds.
///
/// Used For:
///     - Game physics simulation
///     - Collision detection
///     - Rendering the ball in the game window
//////////////////////////////////////////////////////////////

class Ball {
private:
    sf::CircleShape shape;   // Graphical representation of the ball
    float velocityX;         // Ball speed along X-axis
    float velocityY;         // Ball speed along Y-axis

public:

    //////////////////////////////////////////////////////////////
    /// Constructor: Ball(float x, float y)
    /// ---------------------------------------------------------
    /// Purpose:
    ///     Creates a new ball at the given coordinates.
    ///
    /// Parameters:
    ///     float x -> Starting X position
    ///     float y -> Starting Y position
    ///
    /// Used For:
    ///     Initializing ball position, size, color, and speed.
    //////////////////////////////////////////////////////////////
    Ball(float x, float y);

    //////////////////////////////////////////////////////////////
    /// Function: update(float dt)
    /// ---------------------------------------------------------
    /// Purpose:
    ///     Moves the ball based on its velocity and elapsed time.
    ///
    /// Parameters:
    ///     float dt -> Delta time (time between frames)
    ///
    /// Used For:
    ///     Ball movement and wall collision logic.
    //////////////////////////////////////////////////////////////
    void update(float dt);

    //////////////////////////////////////////////////////////////
    /// Function: draw(sf::RenderWindow& window)
    /// ---------------------------------------------------------
    /// Purpose:
    ///     Draws the ball on the game window.
    ///
    /// Parameters:
    ///     sf::RenderWindow& window -> Window where ball is rendered
    ///
    /// Used For:
    ///     Rendering graphics.
    //////////////////////////////////////////////////////////////
    void draw(sf::RenderWindow& window);

    //////////////////////////////////////////////////////////////
    /// Function: reset(float x, float y)
    /// ---------------------------------------------------------
    /// Purpose:
    ///     Resets the ball to a given position and reverses direction.
    ///
    /// Parameters:
    ///     float x -> New X position
    ///     float y -> New Y position
    ///
    /// Used For:
    ///     Restarting the round after a score.
    //////////////////////////////////////////////////////////////
    void reset(float x, float y);

    //////////////////////////////////////////////////////////////
    /// Function: bounceX()
    /// ---------------------------------------------------------
    /// Purpose:
    ///     Reverses horizontal velocity when ball hits a paddle.
    ///
    /// Parameters:
    ///     None
    ///
    /// Used For:
    ///     Paddle collision physics.
    //////////////////////////////////////////////////////////////
    void bounceX();

    //////////////////////////////////////////////////////////////
    /// Function: bounceY()
    /// ---------------------------------------------------------
    /// Purpose:
    ///     Reverses vertical velocity when ball hits top/bottom wall.
    ///
    /// Parameters:
    ///     None
    ///
    /// Used For:
    ///     Wall collision physics.
    //////////////////////////////////////////////////////////////
    void bounceY();

    //////////////////////////////////////////////////////////////
    /// Function: getBounds() const
    /// ---------------------------------------------------------
    /// Purpose:
    ///     Returns the ball's bounding box for collision detection.
    ///
    /// Parameters:
    ///     None
    ///
    /// Return:
    ///     sf::FloatRect -> The global boundary of the ball.
    ///
    /// Used For:
    ///     Checking collision with paddles or screen edges.
    //////////////////////////////////////////////////////////////
    sf::FloatRect getBounds() const;
};

#endif

