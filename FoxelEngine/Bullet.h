#pragma once
#include "Vec3.h"
#include <vector>

enum BulletType {NORMAL, ROCKET};

class Bullet{
	friend class BulletManager;

private:
	BulletType bulletType;

public:
	Vec3 position, velocity;

	Bullet(Vec3 start, Vec3 velocity, BulletType bulletType);
	BulletType getBulletType();
	void update();
	~Bullet(void);
};

class BulletManager{
private:
	static std::vector<Bullet*> bullets;

public:
	static void addBullet(Bullet* b);
	void detectHits();

	
};
