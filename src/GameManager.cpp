#include "GameManager.h"
#include "SpaceShip.h"
#include "Projectile.h"
#include "Asteroid.h"

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

    if (!Asteroid::LoadImages())
        return false;

    spaceShip = new SpaceShip(this, sf::Vector2f(renderWindow.GetWidth()/2, renderWindow.GetHeight()/2));
    RegisterGameObject(spaceShip);

    return true;
}

void GameManager::FreeResources()
{
    if (spaceShip)
        delete spaceShip;
}

void GameManager::LaunchAsteroids(){
//    Projectile * projectile = new Projectile(gameManager, position, orientation);
    Asteroid * asteroid = new Asteroid(this, sf::Vector2f(renderWindow.GetWidth()/2, renderWindow.GetHeight()/2), 0, 0);
    RegisterGameObject(asteroid);
}

void GameManager::UpdateGame(float deltaTime)
{
    const sf::Input & input = renderWindow.GetInput();

    float rotationDir = 0;

    // Se establecen los eventos para el movimiento de la nave
    if (input.IsKeyDown(sf::Key::Left))
        rotationDir += 1.0f;

    if (input.IsKeyDown(sf::Key::Right))
        rotationDir -= 1.0f;

    spaceShip->SetRotationDirection(rotationDir);

    if (input.IsKeyDown(sf::Key::Space))
        spaceShip->EvalProjectile();

    if (input.IsKeyDown(sf::Key::Down))
        LaunchAsteroids();

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
    // Se dibuja el fondo
    renderWindow.Draw(backgroundSprite);
    // Se dibuja cada uno de los objetos activos
    for (std::vector<GameObject *>::iterator it = activeGameObjects.begin();
         it != activeGameObjects.end(); ++it)
    {
        (*it)->Draw(renderWindow);
    }
    
}

// Agrega un objeto a la lista de objetos nuevos
void GameManager::RegisterGameObject(GameObject * newGameObject)
{
    newGameObjects.push_back(newGameObject);
}

// Elimina un objeto de la lista de objetos nuevos
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
