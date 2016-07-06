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

// Getters and Setters

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

sf::Sprite GameObject::GetSprite(){
    return sprite;
}
void GameObject::SetSprite(sf::Sprite sprite){
    this->sprite = sprite;
}

float GameObject::GetOrientation(){
    return orientation;
}
void GameObject::SetOrientation(float orientation){
    this->orientation = orientation;
}

float GameObject::GetSpriteRotation(){
    return spriteRotation;
}
void GameObject::SetSpriteRotation(float spriteRotation){
    this->spriteRotation = spriteRotation;
}

GameObject::Type GameObject::GetType(){
    return type;
}

void GameObject::SetType(Type type){
    this->type = type;
}