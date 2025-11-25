//////////////////////////////////////////////////////////////
/// File: main.cpp
/// ---------------------------------------------------------
/// Objective:
///     This is the entry point of the Pong game application.
///     It creates a Game object and starts the game loop
///     by calling game.run().
///
/// Input Parameters:
///     None (program starts without any command-line arguments)
///
/// Return Values:
///     int -> Returns 0 on successful execution.
///
/// Side Effects:
///     - Launches a game window through the Game class.
///     - Allocates resources needed for running the game
///       such as textures, fonts, and SFML objects.
///     - If the Game class encounters issues (e.g., missing assets),
///       the application may terminate early.
///
/// Approach:
///     - Instantiate a Game object.
///     - Call the run() function to start the main game loop.
///     - Return 0 after the game loop ends.
///
//////////////////////////////////////////////////////////////

#include "Game.h"

int main() {
    Game game;
    game.run();
    return 0;
}
