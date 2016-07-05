#include <math.h>
#include "Definitions.h"
#include "Asteroid.h"
#include <stdio.h>

sf::Image Asteroid::asteroidImg;

Asteroid::Asteroid(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, int tipo) :
    GameObject(ownerGame)
{

    if(tipo == 0){
        health = 100;
        size = 0.5f;
        speed = 30;
    }else{
        health = 50;
        size = 0.25f;
        speed = 70;
    }
    gameManager = ownerGame;
    position = initialPosition;
    orientation = initialOrientation;


    sprite.SetImage(asteroidImg);
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite.SetScale(size, size);
    spriteRotation = -90;


}

Asteroid::~Asteroid()
{

}

void Asteroid::Update(float deltaTime)
{
//    printf("jojojojo\n");
    GameObject::Update(deltaTime);

    const float angle = orientation * PI / 180.0f;

    sf::Vector2f direction;
    direction.x = cos(angle);
    direction.y = sin(angle);

    position += direction * speed * deltaTime;
    
}

bool Asteroid::LoadImages()
{
    if (!asteroidImg.LoadFromFile("graphics/Asteroid01.png"))
        return false;

    return true;
}
