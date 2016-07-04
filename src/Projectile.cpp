#include <math.h>
#include "Definitions.h"
#include "Projectile.h"

sf::Image Projectile::projectileImg;

Projectile::Projectile(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation) :
    GameObject(ownerGame)
{
    gameManager = ownerGame;
    position = initialPosition;
    orientation = initialOrientation;
    speed = 100;
    lifeTime = 3.0f;
    sprite.SetImage(projectileImg);
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
    if (!projectileImg.LoadFromFile("graphics/Projectile01.png"))
        return false;

    return true;
}
