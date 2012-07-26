#pragma once
#include "Model.h"
#include "PropDynamic.h"
#include "Screen.h"
#include "Matrix4.h"
#include "Bullet.h"
class Pistol : public PropDynamic{
private:
	Model* model;
	Matrix4 objMatrix;
	Vec3d rVelocity;
	BulletType bulletType;
	int cooldown;
public:
	Pistol(void);
	~Pistol(void);
	void load();
	void draw();
	void forceR(Vec3d rForce);
	void update(float* time);
	void shoot(Vec3 position, Vec3 direction);
	void shoot2(Vec3 position, Vec3 direction);
};

