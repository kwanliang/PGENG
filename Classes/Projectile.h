#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Projectile
{
public:
    Projectile();
    ~Projectile();

    inline Vec2 GetPosition(void) { return position; }
	inline int GetLane(void) { return lane; }
	inline int GetDamage(void) { return damage; }
    inline bool GetIsActive(void) { return isActive; }
	inline ParticleSystemQuad* GetParticle(void) { return particle; }

    inline void SetPosition(Vec2 pos) { this->position = pos; }
    inline void SetIsActive(bool active) { this->isActive = active; }

    inline void IncrementPositionY(float scale) { this->position.y += scale; }

	void Init(int lane, int damage);

    void MoveParticle(float speed);
	void update(float delta);

private:
	ParticleSystemQuad* particle;
	Vec2 position;
    int lane;
    int damage;
    bool isActive;
	float speed;
};