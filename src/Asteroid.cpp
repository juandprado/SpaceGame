#include <math.h>
#include "Definitions.h"
#include "Asteroid.h"
#include "GameManager.h"
#include <stdio.h>

sf::Image Asteroid::asteroidImg;

Asteroid::Asteroid(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, TypeAsteroid tipo) :
    GameObject(ownerGame)
{

    if(tipo == LARGE){
        health = 100;
        size = 0.5f;
        speed = 30;
    }else{
        health = 50;
        size = 0.25f;
        speed = 70;
    }
    typeAsteroid = tipo;
    gameManager = ownerGame;
    position = initialPosition;
    orientation = initialOrientation;


    sprite.SetImage(asteroidImg);
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite.SetScale(size, size);
    spriteRotation = -90;

    type = ASTEROID;
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
    direction.y = -sin(angle);

    position += direction * speed * deltaTime;

    if (health<=0){
        Destroy();
    }
   
}

void Asteroid::Damage(){
    health -= 50;
}

void Asteroid::Damage(float orientation){
    this->orientation = orientation;
    speed += 40;
    health -= 50;
}


void Asteroid::Destroy()
{   
    GameObject::Destroy();
    if (typeAsteroid == LARGE) {
        gameManager->LaunchAsteroids(GetSpacePosition().x, GetSpacePosition().y, (rand() % (int)(360 + 1)), 1);
        gameManager->LaunchAsteroids(GetSpacePosition().x, GetSpacePosition().y, (rand() % (int)(360 + 1)), 1);
        gameManager->AddPoints(20);
    } else {
        gameManager->AddPoints(50);
    }
}

bool Asteroid::LoadImages()
{
    if (!asteroidImg.LoadFromFile("graphics/Asteroid01.png"))
        return false;

    return true;
}


// Getters and Setters
float Asteroid::GetHealth(){
    return health;
}
void Asteroid::SetHealth(float health){
    this->health = health;
}

float Asteroid::GetSize(){
    return size;
}
void Asteroid::SetSize(float size){
    this->size = size;
}

float Asteroid::GetSpeed(){
    return speed;
}
void Asteroid::SetSpeed(float speed){
    this->speed = speed;
}

Asteroid::TypeAsteroid Asteroid::GetTypeAsteroid(){
    return typeAsteroid;
}
void Asteroid::SetTypeAsteroid(TypeAsteroid typeAsteroid){
    this->typeAsteroid = typeAsteroid;
}