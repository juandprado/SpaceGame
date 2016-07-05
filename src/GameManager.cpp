#include "GameManager.h"
#include "SpaceShip.h"
#include "Projectile.h"
#include "Asteroid.h"
#include <stdio.h>

GameManager::GameManager(sf::RenderWindow & appWindow) :
    renderWindow(appWindow)
{
    spaceShip = NULL;
    asteroidTimer = 3.0f;
    contador = 0;
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

    for (int i=0; i<3; i++){
        LaunchRandomAsteroids();
    }

    return true;
}

void GameManager::FreeResources()
{
    if (spaceShip)
        delete spaceShip;
}

void GameManager::LaunchRandomAsteroids(){
    bool flag = true;
    int xrand = 0;
    int yrand = 0;

    //Se calcula la posicion del nuevo asteroide para que no se solape con la nave
    sf::Vector2f shipPos = spaceShip->GetSpacePosition();
    while (flag){
        xrand = ((rand() % (int)(renderWindow.GetWidth() + 1)));
        if ( (xrand < (shipPos.x-60) ) || ( xrand > (shipPos.x + spaceShip->GetSpaceWidth() + 60) )){
            flag = false;
        }
    }

    flag = true;
    while (flag){
        yrand = ((rand() % (int)(renderWindow.GetHeight() + 1)));
        if ( (yrand < (shipPos.y-60) ) || ( yrand > (shipPos.y + spaceShip->GetSpaceWidth() + 60) )){
            flag = false;
        }
    }

    LaunchAsteroids(xrand , yrand, (rand() % (int)(360 + 1)), (rand() % (int)(1 + 1)));
}

void GameManager::LaunchAsteroids(float x, float y, int ori, int tipo){
//    Projectile * projectile = new Projectile(gameManager, position, orientation);
    Asteroid * asteroid = new Asteroid(this, sf::Vector2f(x, y), ori, tipo);
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
    //Se calcula el timer para nuevos astaroides y se crean nuevos
    asteroidTimer -= deltaTime;
    if (asteroidTimer<0.0f){
        LaunchRandomAsteroids();
        asteroidTimer = 3.0f;
    }

    activeGameObjects.insert(activeGameObjects.end(),
                             newGameObjects.begin(),
                             newGameObjects.end());
    newGameObjects.clear();

    for(int i = 0; i < activeGameObjects.size(); i++){
        for (int j = 0; j < activeGameObjects.size(); j++){
            float radio1 = activeGameObjects[i]->GetSpaceWidth();
            if(radio1 < activeGameObjects[i]->GetSpaceHeight()){
                radio1 = activeGameObjects[i]->GetSpaceHeight();
            }

            float radio2 = activeGameObjects[j]->GetSpaceWidth();
            if(radio2 < activeGameObjects[j]->GetSpaceHeight()){
                radio2 = activeGameObjects[j]->GetSpaceHeight();
            }

            if(activeGameObjects[i]->type == GameObject::PROJECTILE &&
                    activeGameObjects[j]->type == GameObject::ASTEROID &&
                    CircleCollision(activeGameObjects[i]->GetSpacePosition(),
                    radio1 / 2,
                    activeGameObjects[j]->GetSpacePosition(),
                    radio2 / 2)){
                activeGameObjects[j]->Destroy();
                printf("jojojojo\n");
            }
        }
    }

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

bool GameManager::CircleCollision(sf::Vector2f p1, float radius1, sf::Vector2f p2, float radius2){
    float sumRadius = radius1 + radius2;
    sf::Vector2f delta = p2 - p1;
    float distanceSquare = delta.x * delta.x + delta.y * delta.y;
    return (distanceSquare < sumRadius * sumRadius);
}
