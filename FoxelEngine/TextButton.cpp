#include "TextButton.h"


TextButton::TextButton(Vec2 position, Vec2 size, std::string content)
		   : TextField(position, size, content){
	pressed = false;
}

void TextButton::press(){
	pressed = true;
}

void TextButton::release(){
	pressed = false;
}

bool TextButton::isPressed(){
	return pressed;
}

bool TextButton::intersect(Vec2 point){
	if(point.x > position.x && point.x < position.x + size.x
	&& point.y > position.y && point.y < position.y + size.y){
		return true;
	}else{
		return false;
	}
}

TextButton::~TextButton(void)
{
}
