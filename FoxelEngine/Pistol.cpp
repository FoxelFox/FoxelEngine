#include "Pistol.h"
#include "ShaderProgram.h"
#include "Convert.h"


Pistol::Pistol(void) : PropDynamic(){
	model = new Model();
	objMatrix = Matrix4::Identity();
	bulletType = NORMAL;
	cooldown = 250;
}


void Pistol::load(){
	Screen::ViewMatrix.translate(position);
	Screen::updateViewMatix();
	model->load("Models/Pistol.obj");
	Screen::ViewMatrix.translate(position);
}

void Pistol::update(float* time){
	//PropDynamic::update(time);
	rVelocity = (rVelocity * (0.95));
	objMatrix = Matrix4::Identity();

	if(cooldown > 0) cooldown -= (int)*time;
	//objMatrix = objMatrix * Matrix4::CreateFromAxisAngle(Vec3(0,0,1),-rotation.z+90);
	//objMatrix = objMatrix * Matrix4::CreateFromAxisAngle(Vec3(0,1,0), rotation.x+90);
		//objMatrix.translate(1,4,1);
}

void Pistol::forceR(Vec3d rForce){
	rVelocity += (rForce*0.05);
}

void Pistol::draw(){
	//Screen::buildProjectionMatrix(45, Screen::getAspectRatio(), 1.0, 1600.0);
	Screen::ViewMatrix = Matrix4::Identity();
	Screen::ViewMatrix.translate(3,-3,-8);
	Screen::ViewMatrix.rotate((float)(-90+rVelocity.x), 1.0f, 0.0f, 0.0f);
	Screen::ViewMatrix.rotate((float)(90+rVelocity.z), 0.0f, 0.0f, 1.0f);

	GLSL::PM::useProg(GLSL::PROGRAM_MODEL);
	glUniform3f(GLSL::PM::getActiveUnifLoc("player_position"),-1.5,1.5,4);
	Screen::updateViewMatix();
	//glUniform3f(GLSL::PM::getActiveUnifLoc("player_position"),-position.x,-position.y,-position.z);
	glUniformMatrix4fv(GLSL::PM::getActiveUnifLoc("objMatrix"),1,false,objMatrix.matrix);
	model->draw();
}

void Pistol::shoot(Vec3 position, Vec3 direction){
	if(cooldown <= 0){
		BulletManager::addBullet(new Bullet(position + direction * 16, direction * 1024, bulletType));
		rVelocity.x += 10;
		cooldown = 250;
	}
}

void Pistol::shoot2(Vec3 position, Vec3 direction){
	if(cooldown <= 0){
		BulletManager::addBullet(new Bullet(position + direction * 16, direction * 256, bulletType));

		BulletManager::addBullet(new Bullet(position + Vec3( 1,0, 1)  + direction * 16, direction * 196, bulletType));
		BulletManager::addBullet(new Bullet(position + Vec3(-1,0, 1)  + direction * 16, direction * 196, bulletType));
		BulletManager::addBullet(new Bullet(position + Vec3( 1,0,-1)  + direction * 16, direction * 196, bulletType));
		BulletManager::addBullet(new Bullet(position + Vec3(-1,0,-1)  + direction * 16, direction * 196, bulletType));

		BulletManager::addBullet(new Bullet(position + Vec3( 0,0,-1)  + direction * 16, direction * 196, bulletType));
		BulletManager::addBullet(new Bullet(position + Vec3( 0,0, 1)  + direction * 16, direction * 196, bulletType));
		BulletManager::addBullet(new Bullet(position + Vec3( 1,0, 0)  + direction * 16, direction * 196, bulletType));
		BulletManager::addBullet(new Bullet(position + Vec3(-1,0, 0)  + direction * 16, direction * 196, bulletType));

		BulletManager::addBullet(new Bullet(position + Vec3( 0,0,-2)  + direction * 16, direction * 196, bulletType));
		BulletManager::addBullet(new Bullet(position + Vec3( 0,0, 2)  + direction * 16, direction * 196, bulletType));
		BulletManager::addBullet(new Bullet(position + Vec3( 2,0, 0)  + direction * 16, direction * 196, bulletType));
		BulletManager::addBullet(new Bullet(position + Vec3(-2,0, 0)  + direction * 16, direction * 196, bulletType));


		rVelocity.x += 1;
		cooldown = 10;
	}
}

Pistol::~Pistol(void)
{
}
