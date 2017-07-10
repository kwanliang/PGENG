#pragma once

#include <string>
#include "cocos2d.h"
#include "SingletonTemplate.h"

using namespace cocos2d;

class ParticleManager : public Singleton<ParticleManager>
{
    friend Singleton<ParticleManager>;
public:
    ParticleSystemQuad* SpawnParticle(Vec2 pos, float scale, std::string name);

private:
    ParticleManager();
    ~ParticleManager();
};