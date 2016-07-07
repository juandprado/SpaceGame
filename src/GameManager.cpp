#include "GameManager.h"
#include "SpaceShip.h"
#include "Projectile.h"
#include "Asteroid.h"
#include "AlienShip.h"
#include "Explosion.h"
#include <stdio.h>
#include <iostream>
#include <sstream>

GameManager::GameManager(sf::RenderWindow & appWindow) :
    renderWindow(appWindow)
{
    spaceShip = NULL;
    asteroidTimer = 3.0f;
    points = 0;
    weaponTimer = 0.3f;
    countPowerShot = 0.0f;
    shotStatus = 0;

    gameState = MENU;

    flag_menu = 0;
}

GameManager::~GameManager()
{
    //dtor
}

bool GameManager::Initialize()
{
    activeGameObjects.clear();
    points = 0;
    shotStatus = 0;
    if(!menuImg.LoadFromFile("graphics/menu.png"))
        return false;

    menuSprite.SetImage(menuImg);
    menuSprite.SetScale(1.0f, 1.0f);

    if(!arrowLeftImg.LoadFromFile("graphics/arrow1.png"))
        return false;

    arrowLeftSprite.SetImage(arrowLeftImg);
    arrowLeftSprite.SetScale(1.0f, 1.0f);
    arrowLeftSprite.SetPosition(250.0f, 331.0f);

    if(!arrowRightImg.LoadFromFile("graphics/arrow2.png"))
        return false;

    arrowRightSprite.SetImage(arrowRightImg);
    arrowRightSprite.SetScale(1.0f, 1.0f);
    arrowRightSprite.SetPosition(510.0f, 331.0f);

    if(!gameOverImg.LoadFromFile("graphics/gameOver.png"))
        return false;

    gameOverSprite.SetImage(gameOverImg);

    if (!backgroundImg.LoadFromFile("graphics/Background.png"))
        return false;

    backgroundSprite.SetImage(backgroundImg);
    backgroundSprite.SetScale(0.5f, 0.5f);

    if (!SpaceShip::LoadImages())
        return false;

    if (!Projectile::LoadImages())
        return false;

    if (!Asteroid::LoadImages())
        return false;

    if (!Explosion::LoadImages())
        return false;

    if (!AlienShip::LoadImages())
        return false;

    spaceShip = new SpaceShip(this, sf::Vector2f(renderWindow.GetWidth()/2, renderWindow.GetHeight()/2));
    RegisterGameObject(spaceShip);

    countPowerShot = 0.0f;

//    for (int i=0; i<3; i++){
//        LaunchRandomAsteroids();
//    }

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
//    printf("Pos x: %f  pos y: %f\n", spaceShip->GetSpacePosition().x, spaceShip->GetSpacePosition().y);
    while (flag){
        xrand = ((rand() % (int)(renderWindow.GetWidth() + 1)));
        if ( (xrand < (shipPos.x-100) ) || ( xrand > (shipPos.x + spaceShip->GetSpaceWidth() + 100) )){
            flag = false;
        }
    }

    flag = true;
    while (flag){
        yrand = ((rand() % (int)(renderWindow.GetHeight() + 1)));
        if ( (yrand < (shipPos.y-100) ) || ( yrand > (shipPos.y + spaceShip->GetSpaceWidth() + 100) )){
            flag = false;
        }
    }

    LaunchAsteroids(xrand , yrand, (rand() % (int)(360 + 1)), (rand() % (int)(1 + 1)));
}

void GameManager::AddPoints(int newPoints){
    points += newPoints;
    cout << "Puntos: " << points << endl;
}

void GameManager::LaunchAsteroids(float x, float y, int ori, int tipo){
    Asteroid * asteroid = new Asteroid(this, sf::Vector2f(x, y), ori, static_cast<Asteroid::TypeAsteroid>(tipo+1));
    RegisterGameObject(asteroid);
}

void GameManager::LaunchRandomAlienShips(){
    bool flag = true;
    int xrand = 0;
    int yrand = 0;

    //Se calcula la posicion del nuevo asteroide para que no se solape con la nave
    sf::Vector2f shipPos = spaceShip->GetSpacePosition();
//    printf("Pos x: %f  pos y: %f\n", spaceShip->GetSpacePosition().x, spaceShip->GetSpacePosition().y);
    while (flag){
        xrand = ((rand() % (int)(renderWindow.GetWidth() + 1)));
        if ( (xrand < (shipPos.x-100) ) || ( xrand > (shipPos.x + spaceShip->GetSpaceWidth() + 100) )){
            flag = false;
        }
    }

    flag = true;
    while (flag){
        yrand = ((rand() % (int)(renderWindow.GetHeight() + 1)));
        if ( (yrand < (shipPos.y-100) ) || ( yrand > (shipPos.y + spaceShip->GetSpaceWidth() + 100) )){
            flag = false;
        }
    }
    LaunchAlienShips(xrand , yrand, (rand() % (int)(360 + 1)));
}

void GameManager::LaunchAlienShips(float x, float y, int ori){
    AlienShip * alienShip = new AlienShip(this, sf::Vector2f(x, y), ori);
    RegisterGameObject(alienShip);
}

void GameManager::Game(float deltaTime){
    const sf::Input & input = renderWindow.GetInput();

    float rotationDir = 0;

    // Se establecen los eventos para el movimiento de la nave
    if (input.IsKeyDown(sf::Key::Left))
        rotationDir += 2.0f;

    if (input.IsKeyDown(sf::Key::Right))
        rotationDir -= 2.0f;

    spaceShip->SetRotationDir(rotationDir);
    weaponTimer -= deltaTime;

    if (input.IsKeyDown(sf::Key::Space)){
        if (weaponTimer <= 0){
            if (shotStatus == 0) {
                spaceShip->EvalProjectile(Projectile::WEAK);
                weaponTimer = 0.3f;
                shotStatus = 1;
            }
        }
        countPowerShot += deltaTime;
    } else {
        countPowerShot = 0.0f;
        shotStatus = 0;
    }

    if (countPowerShot >= 0.5f) {
        spaceShip->EvalProjectile(Projectile::STRONG);
        countPowerShot = 0.0f;
        weaponTimer = 0.3f;
    }

    if (input.IsKeyDown(sf::Key::Up)) {
        spaceShip->Accelerate(deltaTime, 1.0f);
    } else {
        spaceShip->Accelerate(deltaTime, -1.0f);
    }

    // Se calcula el timer para nuevos astaroides y se crean nuevos
    asteroidTimer -= deltaTime;
    if (asteroidTimer<0.0f){
        LaunchRandomAsteroids();
        asteroidTimer = 3.0f;
    }

    alienShipTimer -= deltaTime;
    if (alienShipTimer<0.0f){
        LaunchRandomAlienShips();
        alienShipTimer = 15.0f;
    }

    activeGameObjects.insert(activeGameObjects.end(),
                             newGameObjects.begin(),
                             newGameObjects.end());
    newGameObjects.clear();

    // Encargado de detectar las colisiones
    for(int i = 0; i < activeGameObjects.size(); i++){
        for (int j = 0; j < activeGameObjects.size(); j++){
            float radio1 = activeGameObjects[i]->GetSpaceWidth() / 2;
            if(radio1 < activeGameObjects[i]->GetSpaceHeight()){
                radio1 = activeGameObjects[i]->GetSpaceHeight() / 2;
            }

            float radio2 = activeGameObjects[j]->GetSpaceWidth() / 2;
            if(radio2 < activeGameObjects[j]->GetSpaceHeight()){
                radio2 = activeGameObjects[j]->GetSpaceHeight() / 2;
            }

            // Verifica la colision entre proyectiles y asteroides
            if(activeGameObjects[i]->GetType() == GameObject::PROJECTILE_SPACE_SHIP &&
               activeGameObjects[j]->GetType() == GameObject::ASTEROID &&
               CircleCollision(activeGameObjects[i]->GetSpacePosition(),
                               radio1*0.8,
                               activeGameObjects[j]->GetSpacePosition(),
                               radio2)){
                activeGameObjects[i]->Destroy();
                ((Asteroid *)activeGameObjects[j])->Damage(activeGameObjects[i]->GetOrientation());
            }

            // Verifica la colision entre la nave y asteroides
            if(activeGameObjects[i]->GetType() == GameObject::SPACESHIP &&
               activeGameObjects[j]->GetType() == GameObject::ASTEROID &&
               CircleCollision(activeGameObjects[i]->GetSpacePosition(),
                               radio1,
                               activeGameObjects[j]->GetSpacePosition(),
                               radio2)){
                ((SpaceShip *)activeGameObjects[i])->Damage(renderWindow.GetWidth()/2, renderWindow.GetHeight()/2);
                activeGameObjects[j]->Destroy();
            }

            // Verifica la colision entre la nave y la nave alienigena
            if(activeGameObjects[i]->GetType() == GameObject::SPACESHIP &&
               activeGameObjects[j]->GetType() == GameObject::ALIENSHIP &&
               CircleCollision(activeGameObjects[i]->GetSpacePosition(),
                               radio1,
                               activeGameObjects[j]->GetSpacePosition(),
                               radio2)){
                ((SpaceShip *)activeGameObjects[i])->Damage(renderWindow.GetWidth()/2, renderWindow.GetHeight()/2);
                activeGameObjects[j]->Destroy();
            }

            // Verifica la colision entre proyectiles y aliens
            if(activeGameObjects[i]->GetType() == GameObject::PROJECTILE_SPACE_SHIP &&
               activeGameObjects[j]->GetType() == GameObject::ALIENSHIP &&
               CircleCollision(activeGameObjects[i]->GetSpacePosition(),
                               radio1,
                               activeGameObjects[j]->GetSpacePosition(),
                               radio2)){
                activeGameObjects[i]->Destroy();
                ((AlienShip *)activeGameObjects[j])->Destroy();
            }

            // Verifica la colision entre alien y asteroides
            if(activeGameObjects[i]->GetType() == GameObject::ALIENSHIP &&
               activeGameObjects[j]->GetType() == GameObject::ASTEROID &&
               CircleCollision(activeGameObjects[i]->GetSpacePosition(),
                               radio1,
                               activeGameObjects[j]->GetSpacePosition(),
                               radio2)){
                activeGameObjects[i]->Destroy();
                activeGameObjects[j]->Destroy();
            }

            // Verifica la colision entre la nave y los disparos enemigos
            if(activeGameObjects[i]->GetType() == GameObject::SPACESHIP &&
               activeGameObjects[j]->GetType() == GameObject::PROJECTILE_ALIEN_SHIP &&
               CircleCollision(activeGameObjects[i]->GetSpacePosition(),
                               radio1,
                               activeGameObjects[j]->GetSpacePosition(),
                               radio2)){
                ((SpaceShip *)activeGameObjects[i])->Damage(renderWindow.GetWidth()/2, renderWindow.GetHeight()/2);
                activeGameObjects[j]->Destroy();
            }
        }
    }

    for (std::vector<GameObject *>::iterator it = activeGameObjects.begin();
         it != activeGameObjects.end(); ++it)
    {
        // renderWindow.GetWidth()/2, renderWindow.GetHeight()/2
        // Verifica si se pasa del borde izquierdo
        if((*it)->GetSpacePosition().x < 0){
            (*it)->SetSpacePosition(sf::Vector2f(renderWindow.GetWidth(), (*it)->GetSpacePosition().y));
        }
        // Verifica si se pasa del borde derecho
        if((*it)->GetSpacePosition().x > renderWindow.GetWidth()){
            (*it)->SetSpacePosition(sf::Vector2f(0, (*it)->GetSpacePosition().y));
        }

        // Verifica si se pasa del borde superior
        if((*it)->GetSpacePosition().y < 0){
            (*it)->SetSpacePosition(sf::Vector2f((*it)->GetSpacePosition().x, renderWindow.GetHeight()));
        }

        // Verifica si se pasa del borde inferior
        if((*it)->GetSpacePosition().y > renderWindow.GetHeight()){
            (*it)->SetSpacePosition(sf::Vector2f((*it)->GetSpacePosition().x, 0));
        }

        (*it)->Update(deltaTime);
        if (it == activeGameObjects.end())
        {
            break;
        }
    }
}

void GameManager::UpdateGame(float deltaTime)
{
    const sf::Input & input = renderWindow.GetInput();
    if(gameState == MENU){
        if(spaceShip->GetVida() == 0){
            Initialize();
        }
        if (input.IsKeyDown(sf::Key::Up) && flag_menu == 1) {
            arrowLeftSprite.SetPosition(arrowLeftSprite.GetPosition().x, arrowLeftSprite.GetPosition().y - 55);
            arrowRightSprite.SetPosition(arrowRightSprite.GetPosition().x, arrowRightSprite.GetPosition().y - 55);
            flag_menu = 0;
        }
        if (input.IsKeyDown(sf::Key::Down) && flag_menu == 0){
            arrowLeftSprite.SetPosition(arrowLeftSprite.GetPosition().x, arrowLeftSprite.GetPosition().y + 55);
            arrowRightSprite.SetPosition(arrowRightSprite.GetPosition().x, arrowRightSprite.GetPosition().y + 55);
            flag_menu = 1;
        }

        if(input.IsKeyDown(sf::Key::Return) && flag_menu == 0){
            gameState = GAME;
        }else if(input.IsKeyDown(sf::Key::Return) && flag_menu == 1){
            exit(0);
        }
    }else if(gameState == GAME){
        Game(deltaTime);

    }else if(gameState == GAMEOVER){
        if (input.IsKeyDown(sf::Key::Back)){
            gameState = MENU;
        }
    }


}

void GameManager::DrawGame()
{
    if(gameState == MENU){
        renderWindow.Draw(menuSprite);
        renderWindow.Draw(arrowLeftSprite);
        renderWindow.Draw(arrowRightSprite);
    } else if (gameState == GAME){
        // Se dibuja el fondo
        renderWindow.Draw(backgroundSprite);


        // Se dibuja cada uno de los objetos activos
        for (std::vector<GameObject *>::iterator it = activeGameObjects.begin();
             it != activeGameObjects.end(); ++it){
            (*it)->Draw(renderWindow);
        }

        // Imprime la puntuacion en pantalla
        sf::String text;
        stringstream convert;
        convert << points;
        text.SetText(convert.str());
        text.SetPosition(10,10);
        renderWindow.Draw(text);

        //Imprime las vidas

        sf::Image vidaImg;
        int dezplazamiento = 0;
        for(int i = 0; i < spaceShip->GetVida(); i++, dezplazamiento+=30){
            sf::Sprite vida;
            vidaImg.LoadFromFile("graphics/Spaceship01.png");
            vida.SetImage(vidaImg);
            vida.SetScale(0.3f, 0.3f);
            vida.SetPosition(50 + dezplazamiento,50);
            renderWindow.Draw(vida);
        }


    } else if(gameState == GAMEOVER){
        renderWindow.Draw(gameOverSprite);
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

// Getter and Setters
GameManager::GameState GameManager::GetGameState(){
    return gameState;
}

void GameManager::SetGameState(GameManager::GameState gameState){
    this->gameState = gameState;
}