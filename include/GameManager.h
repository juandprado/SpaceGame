#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
using namespace std;

class GameObject;
class SpaceShip;

class GameManager
{
    public:

        typedef enum {
            MENU, GAME, GAMEOVER
        } GameState;

        GameManager(sf::RenderWindow & appWindow);
        virtual ~GameManager();

        bool Initialize();
        void FreeResources();

        void UpdateGame(float deltaTime);
        void DrawGame();

        void RegisterGameObject(GameObject * newGameObject);
        void RemoveGameObject(GameObject * gameObjectToRemove);

        void LaunchRandomAsteroids();
        void LaunchAsteroids(float x, float y, int ori, int tipo);
        void LaunchRandomAlienShips();
        void LaunchAlienShips(float x, float y, int ori);
        bool CircleCollision(sf::Vector2f p1, float radius1, sf::Vector2f p2, float radius2);

        void AddPoints(int newPoints);
        void Game(float deltaTime);

        int flag_menu; // Variable que verifica si la flecha esta arriba o abajo

        // Getters and Setters
        GameState GetGameState();
        void SetGameState(GameState gameState);

    protected:

        sf::RenderWindow & renderWindow;

        sf::Image menuImg;
        sf::Sprite menuSprite;

        sf::Image arrowLeftImg;
        sf::Sprite arrowLeftSprite;

        sf::Image arrowRightImg;
        sf::Sprite arrowRightSprite;

        sf::Image gameOverImg;
        sf::Sprite gameOverSprite;

        sf::Image backgroundImg;
        sf::Sprite backgroundSprite;

        SpaceShip * spaceShip;

        std::vector<GameObject *> activeGameObjects;
        std::vector<GameObject *> newGameObjects;

        float asteroidTimer;
        float alienShipTimer;
        int points;
        float countPowerShot;
        float weaponTimer; // Variable encargada de almacenar el tiempo minimo entre cada disparo
        int shotStatus;

        GameState gameState;
};

#endif // GAMEMANAGER_H
