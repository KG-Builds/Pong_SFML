#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////////
/// Class: Paddle
/// -----------------------------------------------------------
/// Objective:
///     Represents a vertical paddle used by either a player
///     or AI in the Pong game. Handles movement, drawing,
///     collision boundaries, and speed settings.
///
/// Responsibilities:
///     - Store paddle shape and movement speed
///     - Move paddle up/down based on input or AI
///     - Keep paddle inside window bounds
///     - Provide collision rectangle for ball interaction
///
/// Side Effects:
///     - Modifies its position each frame when moved
///
/// Used By:
///     Game class (both left and right paddles)
////////////////////////////////////////////////////////////////
class Paddle {
private:
    sf::RectangleShape shape;   // Visual rectangular paddle
    float speed;                // Movement speed in pixels/second

public:

    ////////////////////////////////////////////////////////////
    /// Constructor: Paddle(float x, float y)
    /// --------------------------------------------------------
    /// Objective:
    ///     Initializes a paddle at a given starting position.
    ///
    /// Input:
    ///     x – initial X coordinate
    ///     y – initial Y coordinate
    ///
    /// Return:
    ///     None (constructor)
    ///
    /// Side Effects:
    ///     - Creates rectangle shape
    ///     - Positions it on screen
    ///
    /// Approach:
    ///     Set paddle size → set position → assign speed.
    ////////////////////////////////////////////////////////////
    Paddle(float x, float y);

    ////////////////////////////////////////////////////////////
    /// Function: moveUp(float dt)
    /// --------------------------------------------------------
    /// Objective:
    ///     Moves the paddle upward based on delta time.
    ///
    /// Input:
    ///     dt – time elapsed since last frame
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Changes paddle Y-position
    ///
    /// Approach:
    ///     newY = oldY - speed * dt
    ////////////////////////////////////////////////////////////
    void moveUp(float dt);

    ////////////////////////////////////////////////////////////
    /// Function: moveDown(float dt)
    /// --------------------------------------------------------
    /// Objective:
    ///     Moves the paddle downward based on delta time.
    ///
    /// Input:
    ///     dt – time elapsed since last frame
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Changes paddle Y-position
    ///
    /// Approach:
    ///     newY = oldY + speed * dt
    ////////////////////////////////////////////////////////////
    void moveDown(float dt);

    ////////////////////////////////////////////////////////////
    /// Function: update(float dt)
    /// --------------------------------------------------------
    /// Objective:
    ///     Ensures paddle stays within screen boundaries.
    ///
    /// Input:
    ///     dt – delta time (not always required, but kept
    ///          for consistency with other update functions)
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Clamps paddle position if it leaves the window
    ///
    /// Approach:
    ///     Check upper/lower limits → correct position if needed.
    ////////////////////////////////////////////////////////////
    void update(float dt);

    ////////////////////////////////////////////////////////////
    /// Function: draw(sf::RenderWindow& window)
    /// --------------------------------------------------------
    /// Objective:
    ///     Draws the paddle in the game window.
    ///
    /// Input:
    ///     window – reference to main render window
    ///
    /// Return:
    ///     void
    ///
    /// Side Effects:
    ///     - Renders paddle to screen
    ///
    /// Approach:
    ///     window.draw(shape)
    ////////////////////////////////////////////////////////////
    void draw(sf::RenderWindow& window);

    ////////////////////////////////////////////////////////////
    /// Function: getBounds() const
    /// --------------------------------------------------------
    /// Objective:
    ///     Retrieves the paddle's collision boundary.
    ///
    /// Input:
    ///     None
    ///
    /// Return:
    ///     sf::FloatRect – bounding rectangle of paddle
    ///
    /// Side Effects:
    ///     None
    ///
    /// Approach:
    ///     return shape.getGlobalBounds()
    ////////////////////////////////////////////////////////////
    sf::FloatRect getBounds() const;
};

#endif

