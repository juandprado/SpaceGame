#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "Space Game");

    GameManager gameManager(app);

    if (!gameManager.Initialize())
    {
        std::cout << "Failure loading graphics." << std::endl;
        return EXIT_FAILURE;
    }

    // Clock used to calculate the delta time
    sf::Clock deltaClock;

	// Start the game loop
    while (app.IsOpened())
    {
        // Process events
        sf::Event event;
        while (app.GetEvent(event))
        {
            // Close window : exit
            if (event.Type == sf::Event::Closed)
                app.Close();
        }

        float elapsedTime = deltaClock.GetElapsedTime();

        if (elapsedTime > 0)
        {
            gameManager.UpdateGame(elapsedTime);
            deltaClock.Reset();
        }

        // Clear screen
        app.Clear();

        gameManager.DrawGame();

        // Update the window
        app.Display();
    }

    gameManager.FreeResources();

    return EXIT_SUCCESS;
}
