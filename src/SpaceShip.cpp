#include "SpaceShip.h"
#include "Projectile.h"
#include "GameManager.h"

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
    weaponTimer = 1;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::SetRotationDirection(float direction)
{
    rotationDir = direction;
}

void SpaceShip::EvalProjectile()
{
    if (weaponTimer < 0)
    {
        Projectile * projectile = new Projectile(gameManager, position, orientation);
        gameManager->RegisterGameObject(projectile);
        weaponTimer = 1;
    }
}

void SpaceShip::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    orientation += deltaTime * rotationDir * 90;

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
