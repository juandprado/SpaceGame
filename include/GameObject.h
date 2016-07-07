#pragma once

#include <SFML/Graphics.hpp>

class GameManager;


class GameObject
{

public:

    GameObject(GameManager * ownerGame);
    virtual ~GameObject();

    // Definicion del tipo de dato type que determina el tipo de objeto
    typedef enum {
        SPACESHIP, ASTEROID, PROJECTILE_SPACE_SHIP, PROJECTILE_ALIEN_SHIP, ALIENSHIP, EXPLOSION
    } Type;

    void Destroy();

    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow & render);

    // Getters and Setters
    float GetSpaceWidth();
    float GetSpaceHeight();
    sf::Vector2f GetSpacePosition();
    void SetSpacePosition(sf::Vector2f position);

    sf::Sprite GetSprite();
    void SetSprite(sf::Sprite sprite);

    float GetOrientation();
    void SetOrientation(float orientation);

    float GetSpriteRotation();
    void SetSpriteRotation(float spriteRotation);

    Type GetType();
    void SetType(Type type);

protected:

    GameManager * gameManager;

    sf::Sprite sprite;
    sf::Vector2f position;
    float orientation;
    float spriteRotation;

    Type type;

};
