#include "SpaceShip.h"
#include "Projectile.h"
#include "GameManager.h"
#include "Asteroid.h"
#include <stdio.h>

sf::Image SpaceShip::spaceShipImg;

SpaceShip::SpaceShip(GameManager * ownerGame, sf::Vector2f initialPosition)
    : GameObject(ownerGame)
{
    gameManager = ownerGame;
    position = initialPosition;
    sprite.SetImage(spaceShipImg);
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite.SetScale(1.0f, 1.0f);
    spriteRotation = -90;
    rotationDir = 0;
    weaponTimer = 0.3;

    type = SPACESHIP;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::SetRotationDirection(float direction)
{
    rotationDir = direction;
}

// Encargado de lanzar un proyectil
void SpaceShip::EvalProjectile()
{
    if (weaponTimer < 0)
    {
        Projectile * projectile = new Projectile(gameManager, position, orientation);
        gameManager->RegisterGameObject(projectile); // Se registra la creacion del nuevo proyectil
        weaponTimer = 0.3;

//        Asteroid * asteroid = new Asteroid(gameManager, position, orientation);
//        gameManager->RegisterGameObject(asteroid);
    }
}

float SpaceShip::GetSpaceWidth(){
    return sprite.GetSize().x;
}

float SpaceShip::GetSpaceHeight(){
    return sprite.GetSize().y;
}

sf::Vector2f SpaceShip::GetSpacePosition(){
    return sprite.GetPosition();
}

void SpaceShip::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    orientation += deltaTime * rotationDir * 90;
//    printf("%f\n",orientation);

    weaponTimer -= deltaTime;
    
}

void SpaceShip::Draw(sf::RenderWindow & render)
{
    GameObject::Draw(render);
}

bool SpaceShip::LoadImages()
{
    if (!spaceShipImg.LoadFromFile("graphics/Spaceship01.png"))
        return false;

    return true;
}
