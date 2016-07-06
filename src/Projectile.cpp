#include <math.h>
#include "Definitions.h"
#include "Projectile.h"
#include <iostream>
using namespace std;

sf::Image Projectile::projectileImg;
sf::Image Projectile::projectileImg2;

Projectile::Projectile(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, TypeProjectile tipo) :
    GameObject(ownerGame)
{
    gameManager = ownerGame;
    position = initialPosition;
    orientation = initialOrientation;
    
    lifeTime = 3.0f;
    

    typeProjectile = tipo;
    if (typeProjectile == WEAK) {
        sprite.SetImage(projectileImg);
        speed = 300;
    } else {
        sprite.SetImage(projectileImg2);
        speed = 500;
    }

    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite.SetScale(1.0f, 1.0f);
    spriteRotation = -90;
    
    type = PROJECTILE;
}

Projectile::~Projectile()
{

}

void Projectile::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    const float angle = orientation * PI / 180.0f;

    sf::Vector2f direction;
    direction.x = cos(angle);
    direction.y = -sin(angle);

    position += direction * speed * deltaTime;

    lifeTime -= deltaTime;
    if (lifeTime<0)
    {
        Destroy();
    }
    
}

bool Projectile::LoadImages()
{
    if (!projectileImg.LoadFromFile("graphics/Projectile10.png") || !projectileImg2.LoadFromFile("graphics/Projectile09.png"))
        return false;
    
    return true;
}

// Getters and Setters
float Projectile::GetSpeed(){
    return speed;
}
void Projectile::SetSpeed(float speed){
    this->speed = speed;
}

float Projectile::GetLifeTime(){
    return lifeTime;
}
void Projectile::SetLifeTime(float lifeTime){
    this->lifeTime = lifeTime;
}