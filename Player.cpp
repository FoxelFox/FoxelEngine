#include "Player.h"

Player::Player(void) : PropDynamic(){
	maxMoveSpeed = 0.025f;
	accelerateValue = 0.0001f;
	camera = new Camera();
	controler = new PlayerControler();
	rotation.x = 270;
	rotation.z = 0;
}

Player::Player(Vec3d position)
			  : PropDynamic(position){
	camera = new Camera(position);
}

void Player::catchKeyDown(SDLKey sym){
	controler->getKeyDown(sym);
}

void Player::catchKeyUp(SDLKey sym){
	controler->getKeyUp(sym);
}

void Player::catchMouseMotion(float x, float y){
	rotation.z += x/16.0f;
	rotation.x += y/16.0f;
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
		velocity.z += speed * cos(Convert::degToRad(&rotation.x));
	}
	if(controler->forward){
		float speed = accelerateValue **time ;
		velocity.x += speed * sin(-Convert::degToRad(&rotation.z))*sin(Convert::degToRad(&rotation.x));
		velocity.y -= speed * cos(-Convert::degToRad(&rotation.z))*sin(Convert::degToRad(&rotation.x));
		velocity.z -= speed * cos(Convert::degToRad(&rotation.x));
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
	PropDynamic::update(time);
	camera->setPosition(-position);
	camera->setRotation(rotation);
	createEvents();

	//std:: cout << "x\t" << position.x << "\ty\t" << position.y << "\tz\t" << position.z << std::endl;
}

void Player::render(){
	camera->setupView();
}

void Player::createEvents(){
	if(controler->setFoxel){
		new Event::setFoxel(&position, 1);
	}
}

Player::~Player(void){
}
