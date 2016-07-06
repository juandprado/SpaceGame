#include "SpaceShip.h"
#include "Projectile.h"
#include "GameManager.h"
#include "Asteroid.h"
#include "Definitions.h"
#include <stdio.h>
#include <iostream>
using namespace std;

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

    speed = 0.0f;
    acceleration = 160.0f;
    vida = 3;
}

SpaceShip::~SpaceShip()
{

}

// Encargado de lanzar un proyectil
void SpaceShip::EvalProjectile()
{
    if (weaponTimer < 0)
    {
        Projectile * projectile = new Projectile(gameManager, position, orientation);
        gameManager->RegisterGameObject(projectile); // Se registra la creacion del nuevo proyectil
        weaponTimer = 0.3;
    }
}

void SpaceShip::Accelerate(float deltaTime, float mode){
    speed += acceleration * deltaTime * mode;
    if (speed <= 0.0f) {
        speed = 0.0f;
    }
}

void SpaceShip::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    orientation += deltaTime * rotationDir * 90;

    const float angle = orientation * PI / 180.0f;

    sf::Vector2f direction;
    direction.x = cos(-angle);
    direction.y = sin(-angle);

    position += direction * speed * deltaTime;

    weaponTimer -= deltaTime;
    
}

void SpaceShip::Damage(){
    vida--;
    printf("Vidas: %d\n", vida);
    if(vida <= 0){
        Destroy();
    }
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

// Getters and Setters

int SpaceShip::GetVida(){
    return vida;
}
void SpaceShip::SetVida(int vida){
    this->vida = vida;
}

float SpaceShip::GetRotationDir(){
    return rotationDir;
}
void SpaceShip::SetRotationDir(float rotationDir){
    this->rotationDir = rotationDir;
}

float SpaceShip::GetWeaponTime(){
    return weaponTimer;
}
void SpaceShip::SetWeaponTime(float weaponTimer){
    this->weaponTimer = weaponTimer;
}

float SpaceShip::GetSpeed(){
    return speed;
}
void SpaceShip::SetSpeed(float speed){
    this->speed = speed;
}

float SpaceShip::GetAcceleration(){
    return acceleration;
}
void SpaceShip::SetAcceleration(float acceleration){
    this->acceleration = acceleration;
}
