#include "Player.h"

Player::Player(int typ) : PropDynamic(){
	playerTyp = typ;
	switch(playerTyp){
	case PLAYER_NORMAL: health = 100; armor = 0;   noclip = false;
						rotation.x = 270; rotation.z = -45;
	case PLAYER_EDIT:   health = 100; armor = 100; noclip = true;
						rotation.x = 335; rotation.z = -45;
						position.x = 4; position.y = -10; position.z = 3;
	case PLAYER_FOX:	health = 100; armor = 0;   noclip = true;
						rotation.x = 290; rotation.z = -45;
	}

	position = Vec3d(720,128,256);

	maxMoveSpeed = 0.025f;
	accelerateValue = 0.0001f;
	pistol = new Pistol();
	pistol->load();
	camera = new Camera();
	camera->setRotation(rotation);
	controler = new PlayerControler(playerTyp);
}

void Player::catchKeyDown(SDLKey sym){
	controler->getKeyDown(sym);
}

void Player::catchKeyUp(SDLKey sym){
	controler->getKeyUp(sym);
}

void Player::catchMouseMotion(float x, float y){
	drx = x/16.0f;
	dry = y/16.0f;
	rotation.z += drx;
	rotation.x += dry;
	if(rotation.z > 360) rotation.z -= 360;
	if(rotation.x > 360) rotation.x = 360;
	if(rotation.z <  0 ) rotation.z += 360;
	if(rotation.x <  180 ) rotation.x = 180;
}

void Player::update(float* time){
	if(controler->sprint){
		accelerateValue = 0.001f;
		maxMoveSpeed = 0.25f;
	}else{
		accelerateValue = 0.0001f;
		maxMoveSpeed = 0.025f;
	}
	if(controler->backward){
		float speed = accelerateValue **time ;
		velocity.x -= speed * sin(-Convert::degToRad(&rotation.z))*sin(Convert::degToRad(&rotation.x));
		velocity.y += speed * cos(-Convert::degToRad(&rotation.z))*sin(Convert::degToRad(&rotation.x));
		if(noclip) velocity.z += speed * cos(Convert::degToRad(&rotation.x));
	}
	if(controler->forward){
		float speed = accelerateValue **time ;
		velocity.x += speed * sin(-Convert::degToRad(&rotation.z))*sin(Convert::degToRad(&rotation.x));
		velocity.y -= speed * cos(-Convert::degToRad(&rotation.z))*sin(Convert::degToRad(&rotation.x));
		if(noclip) velocity.z -= speed * cos(Convert::degToRad(&rotation.x));
	}
	if(controler->right){
		float speed = accelerateValue **time ;
		velocity.x += speed * cos(Convert::degToRad(&rotation.z));
		velocity.y -= speed * sin(Convert::degToRad(&rotation.z));
	}
	if(controler->left){
		float speed = accelerateValue **time ;
		velocity.x -= speed * cos(Convert::degToRad(&rotation.z));
		velocity.y += speed * sin(Convert::degToRad(&rotation.z));
	}
	if(controler->shoot){
		pistol->shoot(position, calcDirVector());
		controler->shoot = false;
	}
	if(controler->zoom){
		pistol->shoot2(position, calcDirVector());
	}


	PropDynamic::update(time);
	camera->setPosition(-position);
	camera->setRotation(rotation);
	pistol->forceR(Vec3d(-dry,0,-drx));

	pistol->update(time);
	createEvents();

	FoxelManager::setLodCenter(position);

	//std:: cout << "x\t" << position.x << "\ty\t" << position.y << "\tz\t" << position.z << std::endl;
}

void Player::render(){
	
	GLSL::PM::useProg(GLSL::PROGRAM_MODEL);
	//pistol->draw();
	camera->setupView();
}

/*
	====================================
	calculate the (view)direction vector 
	====================================
*/
Vec3 Player::calcDirVector(){
	Vec3 direction;
	direction.x = (float) sin(-Convert::degToRad(&rotation.z)) * (float)sin(Convert::degToRad(&rotation.x));
	direction.y = (float)-cos(-Convert::degToRad(&rotation.z)) * (float)sin(Convert::degToRad(&rotation.x));
	direction.z = (float)-cos(Convert::degToRad(&rotation.x));
	return direction;
}

void Player::createEvents(){

	// TODO
	//if(playerTyp != PLAYER_EDIT && controler->setFoxel){
	//	if(controler->setFoxel){ // debug
	//	new Event::setFoxel(&position, 1);
	//}
}

PlayerControler* Player::getControler(){
	return controler;
}

void Player::setTyp(int typ){
	playerTyp = typ;
	controler->controleMode = typ;
}

Player::~Player(void){
}
