#include "GameObject.h"
#include "GameManager.h"

GameObject::GameObject(GameManager * ownerGame)
{
    gameManager = ownerGame;

    position.x = 0;
    position.y = 0;
    orientation = 0;
    spriteRotation = 0;
}

GameObject::~GameObject()
{

}

void GameObject::Destroy()
{
    gameManager->RemoveGameObject(this);
}

void GameObject::Update(float deltaTime)
{

}

void GameObject::Draw(sf::RenderWindow & render)
{
    sprite.SetRotation(orientation + spriteRotation);
    sprite.SetPosition(position);
    render.Draw(sprite);
}
