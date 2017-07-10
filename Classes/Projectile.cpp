#include "Projectile.h"
#include "ParticleManager.h"

Projectile::Projectile()
{

}

Projectile::~Projectile()
{

}

ParticleSystemQuad* Projectile::Init(int lane)
{
    isActive = true;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    switch (lane) {
    case 0:
    {
        position = Vec2((visibleSize.width / 6) * 0.95, (visibleSize.height * 0.5));
        break;
    }
    case 1:
    {
        position = Vec2((visibleSize.width / 6) * 1.7, (visibleSize.height * 0.5));
        break;
    }
    case 2:
    {
        position = Vec2((visibleSize.width / 6) * 2.5, (visibleSize.height * 0.5));
        break;
    }
    case 3:
    {
        position = Vec2((visibleSize.width / 6) * 3.3, (visibleSize.height * 0.5));
        break;
    }
    case 4:
    {
        position = Vec2((visibleSize.width / 6) * 4.1, (visibleSize.height * 0.5));
        break;
    }
    case 5:
    {
        position = Vec2((visibleSize.width / 6) * 4.9, (visibleSize.height * 0.5));
        break;
    }
    default:
        break;
    }


    particle = ParticleSystemQuad::create("projectile.plist");
    particle->setAnchorPoint(Vec2::ZERO);
    particle->setPosition(position);
    particle->setScale(0.1f);
    particle->setAutoRemoveOnFinish(true);

    MoveParticle(1.0f);

    return particle;
}

void Projectile::MoveParticle(float speed)
{
    auto moveEvent = MoveBy::create(speed, Vec2(0, position.y));
    particle->runAction(moveEvent);
    ////Vec2 vec = Vec2(0, 1000);
    ////auto moveEvent = MoveBy::create(vec.length() * 0.005f, vec);
    ////particle->runAction(moveEvent);

    //auto move = MoveBy::create(0, Vec2(0, speed));
}