#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>

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

    protected:

        sf::RenderWindow & renderWindow;

        sf::Image backgroundImg;
        sf::Sprite backgroundSprite;

        SpaceShip * spaceShip;

        std::vector<GameObject *> activeGameObjects;
        std::vector<GameObject *> newGameObjects;
};

#endif // GAMEMANAGER_H
