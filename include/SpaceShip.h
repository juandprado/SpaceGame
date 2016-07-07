#pragma once

#include "GameObject.h"
#include "Projectile.h"

class SpaceShip : public GameObject
{
public:

    SpaceShip(GameManager * ownerGame, sf::Vector2f initialPosition);
    virtual ~SpaceShip();

    void EvalProjectile(Projectile::TypeProjectile tipo);

    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow & render);

    static bool LoadImages();

    void Accelerate(float deltaTime, float mode);
    void Damage(float x, float y);

    // Getters and Setters
    int GetVida();
    void SetVida(int vida);

    float GetRotationDir();
    void SetRotationDir(float rotationDir);

    float GetSpeed();
    void SetSpeed(float speed);

    float GetAcceleration();
    void SetAcceleration(float acceleration);



private:

    static sf::Image spaceShipImg;
    static sf::Image trailImg;


    int vida; // Puntos de vida de la nave
    float rotationDir; // Direccion de rotacion de la nave
    
    float speed; //Velocidad de la nave
    float acceleration; // Aceleracion de la nave

    sf::Sprite sprite2;
    bool accelerating;
};
