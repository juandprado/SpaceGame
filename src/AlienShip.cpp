#include "AlienShip.h"
#include "Projectile.h"
#include "GameManager.h"
#include "Asteroid.h"
#include "Definitions.h"
#include <stdio.h>
#include <iostream>
using namespace std;

sf::Image AlienShip::alienShipImg;

AlienShip::AlienShip(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation)
    : GameObject(ownerGame)
{
    gameManager = ownerGame;
    position = initialPosition;
    sprite.SetImage(alienShipImg);
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite.SetScale(1.0f, 1.0f);
    spriteRotation = -90;
    orientation = initialOrientation;

    type = ALIENSHIP;

    speed = 50.0f;
    acceleration = 160.0f;
}

AlienShip::~AlienShip()
{

}

// Encargado de lanzar un proyectil
void AlienShip::EvalProjectile(Projectile::TypeProjectile typeProjectile)
{
    
        Projectile * projectile = new Projectile(gameManager, position, orientation, typeProjectile, GameObject::PROJECTILE_ALIEN_SHIP);
        gameManager->RegisterGameObject(projectile); // Se registra la creacion del nuevo proyectil
}


void AlienShip::Accelerate(float deltaTime, float mode){
    speed += acceleration * deltaTime * mode;
    if (speed <= 0.0f) {
        speed = 0.0f;
    }
}

void AlienShip::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    alienShootTimer -= deltaTime;
    if (alienShootTimer<0.0f){
        EvalProjectile(Projectile::WEAK);
        alienShootTimer = 6.0f;
    }


    const float angle = orientation * PI / 180.0f;

    sf::Vector2f direction;
    direction.x = cos(-angle);
    direction.y = sin(-angle);

    position += direction * speed * deltaTime;
    
}

bool AlienShip::LoadImages()
{
    if (!alienShipImg.LoadFromFile("graphics/Spaceship03.png"))
        return false;

    return true;
}

float AlienShip::GetSpeed(){
    return speed;
}
void AlienShip::SetSpeed(float speed){
    this->speed = speed;
}

float AlienShip::GetAcceleration(){
    return acceleration;
}
void AlienShip::SetAcceleration(float acceleration){
    this->acceleration = acceleration;
}
