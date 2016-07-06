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
        bool CircleCollision(sf::Vector2f p1, float radius1, sf::Vector2f p2, float radius2);

        void AddPoints(int newPoints);

        int contador;

    protected:

        sf::RenderWindow & renderWindow;

        sf::Image backgroundImg;
        sf::Sprite backgroundSprite;

        SpaceShip * spaceShip;

        std::vector<GameObject *> activeGameObjects;
        std::vector<GameObject *> newGameObjects;

        float asteroidTimer;
        int points;
        float countPowerShot;
        float weaponTimer; // Variable encargada de almacenar el tiempo minimo entre cada disparo
        int shotStatus;
};

#endif // GAMEMANAGER_H
