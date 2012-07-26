#include "SlideControl.h"
#include "Screen.h"

SlideControl::SlideControl(Vec2 position, Vec2 size, std::string prefix) : Entity_2D(position, size){
	value = 0.5f;
	buffValue = 0.0f;
	this->prefix = prefix;
	backColor.setColor(128,128,128,255);
	text = new TextField(position + 3,size,prefix+"0.5");
	text->setWithBox(false);
	text->setBigText(false);
}

void SlideControl::changeValue(float nValue){
	if(nValue < 0.0f){
		buffValue -= 0.010f ;
	}else{
		buffValue += 0.010f ;
	}

	if(buffValue <= -0.025f){
		value -= 0.025f;
		buffValue = 0.0f;
	}
	if(buffValue >= 0.025f){
		value += 0.025f;
		buffValue = 0.0f;
	}

	if(value < 0.025f) value = 0.0f;
	if(value > 0.975f) value = 1.0f;

	setText();
}

void SlideControl::setValue(float nValue){
	if(nValue < 0.0f) nValue = 0.0f;
	if(nValue > 1.0f) nValue = 1.0f;
	this->value = nValue;
	setText();
}

void SlideControl::setText(){
	std::stringstream ss;
	ss << prefix << value;
	text->setContent(0,ss.str());
}

float SlideControl::getValue(){
	return value;
}

void SlideControl::draw(){
	drawBackground();
	
	glColor3f(0.8f,0.2f,0.2f);
	glBegin(GL_QUADS);
	glVertex3f(position.x+2, position.y+1, -63.0f);
	glVertex3f(position.x-2 + size.x * value, position.y+1, -63.0f);
	glVertex3f(position.x-2 + size.x * value, position.y + size.y-2, -63.0f);
	glVertex3f(position.x+2, position.y + size.y-2, -63.0f);

	glEnd();

	text->draw();

}

void SlideControl::setPosition(Vec2 position){
	Entity_2D::setPosition(position);
	text->setPosition(position+3);
}