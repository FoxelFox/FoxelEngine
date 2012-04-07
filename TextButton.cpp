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

TextButton::~TextButton(void)
{
}
