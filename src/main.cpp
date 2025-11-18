//==============================================================
// Header File: Game.h
// -------------------------------------------------------------
// Used for accessing the Game class, which controls the entire
// game loop, rendering, input handling, and updates.
//
// This file provides:
//   - Definition of the Game class
//   - Member functions like run(), update(), render()
//==============================================================
#include "Game.h"



//==============================================================
// Function: main
// -------------------------------------------------------------
// Objective:
//   The entry point of the program. Initializes the Game object
//   and starts the game loop by calling run().
//
// Input Parameters:
//   None.
//
// Output:
//   No direct output, but creates a visible game window.
//
// Return Value:
//   int : Returns 0 when the program ends successfully.
//
// Side Effects:
//   - Starts an SFML window loop.
//   - Allocates memory internally through Game's subsystems.
//   - If Game.run() contains an infinite/unstable loop, it may
//     freeze the application.
//
//---------------------------------------------------------------
// Approach:
//   1. Create a Game object to load and set up the game.
//   2. Call the run() function to start the main game loop.
//   3. Return 0 indicating successful execution.
//==============================================================
int main() {

    // Create a Game object which initializes the window, paddles, ball, etc.
    Game game;

    // Start the main game loop (continues until window is closed)
    game.run();

    // Return 0 to indicate that the program terminated correctly
    return 0;
}

