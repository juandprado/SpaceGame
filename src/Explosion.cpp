#include <math.h>
#include "Definitions.h"
#include "Explosion.h"
#include "GameManager.h"
#include <stdio.h>

sf::Image Explosion::ExplosionImg;

Explosion::Explosion(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, TypeExplosion tipo) :
    GameObject(ownerGame)
{

    typeExplosion = tipo;
    gameManager = ownerGame;
    position = initialPosition;
    orientation = initialOrientation;


    sprite.SetImage(ExplosionImg);
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite.SetScale(size, size);
    spriteRotation = -90;
    status = 0;
    type = EXPLOSION;
}

Explosion::~Explosion()
{

}

void Explosion::Update(float deltaTime)
{
    GameObject::Update(deltaTime);
    switch(status){
        case 0:
        ExplosionImg.LoadFromFile("graphics/SmallExp00.png");
        sprite.SetImage(ExplosionImg);
        status++;
        break;
        case 4:
        ExplosionImg.LoadFromFile("graphics/SmallExp01.png");
        sprite.SetImage(ExplosionImg);
        status++;
        break;
        case 8:
        ExplosionImg.LoadFromFile("graphics/SmallExp02.png");
        sprite.SetImage(ExplosionImg);
        status++;
        break;
        case 12:
        ExplosionImg.LoadFromFile("graphics/SmallExp03.png");
        sprite.SetImage(ExplosionImg);
        status++;
        break;
        case 16:
        ExplosionImg.LoadFromFile("graphics/SmallExp04.png");
        sprite.SetImage(ExplosionImg);
        status++;
        break;
        case 20:
        ExplosionImg.LoadFromFile("graphics/SmallExp05.png");
        sprite.SetImage(ExplosionImg);
        status++;
        break;
        default:
        status++;
        break;
    }

    if (status > 24){
        Destroy();
    }
}


void Explosion::Destroy()
{   
    GameObject::Destroy();
}

bool Explosion::LoadImages()
{
    if (!ExplosionImg.LoadFromFile("graphics/SmallExp00.png"))
        return false;

    return true;
}

Explosion::TypeExplosion Explosion::GetTypeExplosion(){
    return typeExplosion;
}
void Explosion::SetTypeExplosion(TypeExplosion typeExplosion){
    this->typeExplosion = typeExplosion;
}