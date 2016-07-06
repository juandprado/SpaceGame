#pragma once

#include "GameObject.h"

class SpaceShip : public GameObject
{
public:

    SpaceShip(GameManager * ownerGame, sf::Vector2f initialPosition);
    virtual ~SpaceShip();

    void EvalProjectile();

    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow & render);

    static bool LoadImages();

    void Accelerate(float deltaTime, float mode);
    void Damage();

    // Getters and Setters
    int GetVida();
    void SetVida(int vida);

    float GetRotationDir();
    void SetRotationDir(float rotationDir);

    float GetWeaponTime();
    void SetWeaponTime(float rotationDir);

    float GetSpeed();
    void SetSpeed(float speed);

    float GetAcceleration();
    void SetAcceleration(float acceleration);



private:

    static sf::Image spaceShipImg;


    int vida; // Puntos de vida de la nave
    float rotationDir; // Direccion de rotacion de la nave
    float weaponTimer; // Variable encargada de almacenar el tiempo minimo entre cada disparo
    float speed; //Velocidad de la nave
    float acceleration; // Aceleracion de la nave
};
