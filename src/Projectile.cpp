#include <math.h>
#include "Definitions.h"
#include "Projectile.h"
#include <iostream>
using namespace std;

sf::Image Projectile::projectileImg;
sf::Image Projectile::projectileImg2;
sf::Image Projectile::projectileImg3;

Projectile::Projectile(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, TypeProjectile typeProjectile, Type type) :
    GameObject(ownerGame)
{
    gameManager = ownerGame;
    position = initialPosition;
    orientation = initialOrientation;

    if(type == PROJECTILE_SPACE_SHIP){
        lifeTime = 3.0f;
    }else{
        lifeTime = 7.0f;
    }


    this->type = type;
    this->typeProjectile = typeProjectile;
    if (typeProjectile == WEAK && type == PROJECTILE_SPACE_SHIP) {
        sprite.SetImage(projectileImg);
        speed = 300;
    } else if(typeProjectile == STRONG && type == PROJECTILE_SPACE_SHIP){
        sprite.SetImage(projectileImg2);
        speed = 500;
    } else if(typeProjectile == WEAK && PROJECTILE_ALIEN_SHIP){
        sprite.SetImage(projectileImg3);
        speed = 200;
    } else{
        sprite.SetImage(projectileImg3);
        speed = 300;
    }

    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite.SetScale(1.0f, 1.0f);
    spriteRotation = -90;
    

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
    if (!projectileImg.LoadFromFile("graphics/Projectile10.png") ||
            !projectileImg2.LoadFromFile("graphics/Projectile09.png") ||
            !projectileImg3.LoadFromFile("graphics/Projectile10.png"))
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