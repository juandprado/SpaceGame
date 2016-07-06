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

float GameObject::GetSpaceWidth(){
    return sprite.GetSize().x;
}

float GameObject::GetSpaceHeight(){
    return sprite.GetSize().y;
}

sf::Vector2f GameObject::GetSpacePosition(){
    return sprite.GetPosition();
}

void GameObject::SetSpacePosition(sf::Vector2f position){
    this->position = position;
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
