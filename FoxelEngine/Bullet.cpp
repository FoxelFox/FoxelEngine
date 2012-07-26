#include "Bullet.h"
#include "FoxelManager.h"


Bullet::Bullet(Vec3 start,Vec3 direction, BulletType bulletType){
	position = start;
	velocity = direction;
	this->bulletType = bulletType;
}


Bullet::~Bullet(void)
{
}

void Bullet::update(){
	position += velocity;
}

BulletType Bullet::getBulletType(){
	return bulletType;
}


/////////////////////////////////////////////////////////////////
// BulletManager
/////////////////

std::vector<Bullet*> BulletManager::bullets;

void BulletManager::addBullet(Bullet* b){
	bullets.push_back(b);
}

void BulletManager::detectHits(){
	for(int i = 0; i < bullets.size(); i++){
		
		if(FoxelManager::detectBulletHit(&bullets[i]->position,&bullets[i]->velocity)){
			// Hit detected

		}
		delete bullets[i];
	}
	
	bullets.clear();
}