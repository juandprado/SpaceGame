#include <math.h>
#include "Definitions.h"
#include "Explosion.h"
#include "GameManager.h"
#include <stdio.h>

sf::Image Explosion::ExplosionImg;

Explosion::Explosion(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, TypeExplosion tipo) :
    GameObject(ownerGame)
{

    typeExplosion = tipo;
    gameManager = ownerGame;
    position = initialPosition;
    orientation = initialOrientation;


    sprite.SetImage(ExplosionImg);
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite.SetScale(size, size);
    spriteRotation = -90;
    status = 0;
    type = EXPLOSION;

    cout << "Pos Explosion: " << position.x << ", " << position.y << endl;
}

Explosion::~Explosion()
{

}

void Explosion::Update(float deltaTime)
{
    GameObject::Update(deltaTime);
    if (typeExplosion == SMALL){
        switch(status){
            case 0:
            cout << "Explosion peq 0 " << endl;
            ExplosionImg.LoadFromFile("graphics/SmallExp00.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 4:
            cout << "Explosion peq 4 " << endl;
            ExplosionImg.LoadFromFile("graphics/SmallExp01.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 8:
            cout << "Explosion peq 8 " << endl;
            ExplosionImg.LoadFromFile("graphics/SmallExp02.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 12:
            cout << "Explosion peq 12 " << endl;
            ExplosionImg.LoadFromFile("graphics/SmallExp03.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 16:
            cout << "Explosion peq 16 " << endl;
            ExplosionImg.LoadFromFile("graphics/SmallExp04.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 20:
            cout << "Explosion peq 20 " << endl;
            ExplosionImg.LoadFromFile("graphics/SmallExp05.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            default:
            status++;
            break;
        }

        if (status > 24){
            Destroy();
        }
    } else {
        switch(status){
            case 0:
            cout << "Explosion gr 0" << endl;
            ExplosionImg.LoadFromFile("graphics/BigExp00.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 3:
            cout << "Explosion gr 3" << endl;
            ExplosionImg.LoadFromFile("graphics/BigExp01.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 6:
            cout << "Explosion gr 6" << endl;
            ExplosionImg.LoadFromFile("graphics/BigExp02.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 9:
            cout << "Explosion gr 9" << endl;
            ExplosionImg.LoadFromFile("graphics/BigExp03.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 12:
            cout << "Explosion gr 12" << endl;
            ExplosionImg.LoadFromFile("graphics/BigExp04.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 15:
            cout << "Explosion gr 15" << endl;
            ExplosionImg.LoadFromFile("graphics/BigExp05.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 18:
            cout << "Explosion gr 18" << endl;
            ExplosionImg.LoadFromFile("graphics/BigExp06.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            case 21:
            cout << "Explosion gr 21" << endl;
            ExplosionImg.LoadFromFile("graphics/BigExp07.png");
            sprite.SetImage(ExplosionImg);
            status++;
            break;
            default:
            status++;
            break;
        }

        if (status > 24){
            Destroy();
        }
    }
    

    
}


void Explosion::Destroy()
{   
    GameObject::Destroy();
}

bool Explosion::LoadImages()
{
    if (!ExplosionImg.LoadFromFile("graphics/SmallExp00.png"))
        return false;

    return true;
}

Explosion::TypeExplosion Explosion::GetTypeExplosion(){
    return typeExplosion;
}
void Explosion::SetTypeExplosion(TypeExplosion typeExplosion){
    this->typeExplosion = typeExplosion;
}