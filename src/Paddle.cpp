//==============================================
// Header file included
// <Paddle.h> is included to access the Paddle class
// declaration, its member variables, and functions.
//==============================================
#include "Paddle.h"


//==============================================================
// Class: Paddle
// Member Variables:
//   - shape : Rectangle representing the paddle on screen.
//   - speed : Determines how fast the paddle moves vertically.
//
// Member Functions:
//   - Paddle(float x, float y) : Constructor to initialize paddle.
//   - moveUp(float dt)        : Moves paddle upward.
//   - moveDown(float dt)      : Moves paddle downward.
//   - draw(window)            : Draws paddle to window.
//   - getBounds()             : Returns paddle collision bounds.
//==============================================================


//==============================================================
// Function: Paddle Constructor
// -------------------------------------------------------------
// Objective:
//   Initialize the paddle object at a given position with
//   predefined size, color, and movement speed.
//
// Input Parameters:
//   - float x : Starting X position of the paddle.
//   - float y : Starting Y position of the paddle.
//
// Output:
//   No direct output.
//
// Return value:
//   No return value (constructor).
//
// Side effects:
//   - Allocates and sets SFML shape properties.
//   - Incorrect position inputs may place paddle off-screen.
//
//---------------------------------------------------------------
// Approach:
//   1. Create a rectangle shape.
//   2. Assign a size (20x100).
//   3. Give it a white color.
//   4. Place it at the requested coordinates.
//   5. Set its speed.
//==============================================================
Paddle::Paddle(float x, float y) {
    // Set paddle size (width=20, height=100)
    shape.setSize(sf::Vector2f(20, 100));

    // Set paddle color to white
    shape.setFillColor(sf::Color::White);

    // Position paddle at user-defined coordinates
    shape.setPosition(x, y);

    // Set vertical movement speed (pixels/second)
    speed = 300.f;
}



//==============================================================
// Function: moveUp
// -------------------------------------------------------------
// Objective:
//   Move the paddle upward while ensuring it does not move
//   outside the top boundary of the game window.
//
// Input Parameters:
//   - float dt : Delta time to ensure frame-rate independent
//                movement.
//
// Output:
//   No direct output.
//
// Return Value:
//   void.
//
// Side effects:
//   - If dt is extremely large, paddle may jump unexpectedly.
//
//---------------------------------------------------------------
// Approach:
//   1. Check if paddle
