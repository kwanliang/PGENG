#pragma once

#include "SingletonTemplate.h"

class ParticleSystem : public Singleton<ParticleSystem>
{
    friend Singleton<ParticleSystem>;
public:
    virtual void SpawnParticle();

private:
    ParticleSystem();
    ~ParticleSystem();
};