#include "GameManager.h"
#include "SpaceShip.h"
#include "Projectile.h"
//#include "Asteroid.h"

GameManager::GameManager(sf::RenderWindow & appWindow) :
    renderWindow(appWindow)
{
    spaceShip = NULL;
}

GameManager::~GameManager()
{
    //dtor
}

bool GameManager::Initialize()
{
    if (!backgroundImg.LoadFromFile("graphics/BackgroundWhite.png"))
        return false;

    backgroundSprite.SetImage(backgroundImg);
    backgroundSprite.SetScale(0.5f, 0.5f);

    if (!SpaceShip::LoadImages())
        return false;

    if (!Projectile::LoadImages())
        return false;

    spaceShip = new SpaceShip(this, sf::Vector2f(300, 300));
    RegisterGameObject(spaceShip);

    return true;
}

void GameManager::FreeResources()
{
    if (spaceShip)
        delete spaceShip;
}

void GameManager::UpdateGame(float deltaTime)
{
    const sf::Input & input = renderWindow.GetInput();

    float rotationDir = 0;

    if (input.IsKeyDown(sf::Key::Left))
        rotationDir += 1.0f;

    if (input.IsKeyDown(sf::Key::Right))
        rotationDir -= 1.0f;

    spaceShip->SetRotationDirection(rotationDir);

    if (input.IsKeyDown(sf::Key::Space))
        spaceShip->EvalProjectile();

    activeGameObjects.insert(activeGameObjects.end(),
                             newGameObjects.begin(),
                             newGameObjects.end());
    newGameObjects.clear();

    for (std::vector<GameObject *>::iterator it = activeGameObjects.begin();
         it != activeGameObjects.end(); ++it)
    {
        (*it)->Update(deltaTime);
        if (it == activeGameObjects.end())
        {
            break;
        }
    }
}

void GameManager::DrawGame()
{
    
    renderWindow.Draw(backgroundSprite);

    for (std::vector<GameObject *>::iterator it = activeGameObjects.begin();
         it != activeGameObjects.end(); ++it)
    {
        (*it)->Draw(renderWindow);
    }
    
}

void GameManager::RegisterGameObject(GameObject * newGameObject)
{
    newGameObjects.push_back(newGameObject);
}

void GameManager::RemoveGameObject(GameObject * gameObjectToRemove)
{
    for (std::vector<GameObject *>::iterator
            it = newGameObjects.begin();
         it != newGameObjects.end(); ++it)
    {
        if (*it == gameObjectToRemove)
        {
            newGameObjects.erase(it);
            break;
        }
    }

    for (std::vector<GameObject *>::iterator
            it = activeGameObjects.begin();
         it != activeGameObjects.end(); ++it)
    {
        if (*it == gameObjectToRemove)
        {
            activeGameObjects.erase(it);
            break;
        }
    }

}
