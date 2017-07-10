#include "ParticleManager.h"

ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{

}

ParticleSystemQuad* ParticleManager::SpawnParticle(Point pos, float scale, std::string name)
{
    auto particle = ParticleSystemQuad::create(name);
    particle->setAnchorPoint(Vec2::ZERO);
    particle->setPosition(pos);
    particle->setScale(scale);
    particle->setAutoRemoveOnFinish(true);

    return particle;
}