#include "ColorPanel.h"

ColorPanel::ColorPanel(Vec2 position, Vec2 size) : Entity_2D(position,size)
{
	Vec2 border(6.0f,6.0f);
	Vec2 upper(0.0f,0.0f);
	float h = size.y/14;
	slider_emit = new SlideControl(position + border, Vec2(size.x - border.x*2, h),"E: "); upper.y += h+2;
	slider_blue = new SlideControl(position + upper + border, Vec2(size.x - border.x*2, h),"B: ");upper.y += h+2;
	slider_green = new SlideControl(position + upper + border, Vec2(size.x - border.x*2, h),"G: "); upper.y += h+2;
	slider_red = new SlideControl(position + upper + border, Vec2(size.x - border.x*2, h), "R: ");
	slider_emit->setValue(0.0f);
	
	
}


ColorPanel::~ColorPanel(void)
{
	delete slider_red;
	delete slider_green;
	delete slider_blue;
	delete slider_emit;
}

void ColorPanel::draw()
{
	drawBackground();
	slider_red->draw();
	slider_green->draw();
	slider_blue->draw();
	slider_emit->draw();
	drawColorCircle();
}

float clamp(float value)
{
	if(value < 0.0f) value = 0.0f;
	if(value > 1.0f) value = 1.0f;
	return value;
}

void ColorPanel::drawColorCircle()
{
	Vec2 center = position + Vec2(size.x * 0.5f,size.y - 64.0f);
	
	//glPolygonMode(GL_FRONT, GL_LINE);
	
	glTranslatef(center.x, center.y, 0.0);
	glColor3ub(color.getRed(),color.getGreen(),color.getBlue());
	glutSolidCube(120);
	glTranslatef(-center.x, -center.y, 0.0);
}

void ColorPanel::resize(Vec2 position)
{
	this->position = position;
	Vec2 border(6.0f,6.0f);
	Vec2 upper(0.0f,0.0f);
	float h = size.y/14;

	slider_red->setPosition(position + border);upper.y += h+2;
	slider_green->setPosition(position+upper +border);upper.y += h+2;
	slider_blue->setPosition(position+upper +border);upper.y += h+2;
	slider_emit->setPosition(position+upper +border);
}

void ColorPanel::mouseInteraction()
{
	if(slider_red->mouseIntersect()) slider_red->changeValue(-Screen::getMouseMotion().x);
	if(slider_green->mouseIntersect()) slider_green->changeValue(-Screen::getMouseMotion().x);
	if(slider_blue->mouseIntersect()) slider_blue->changeValue(-Screen::getMouseMotion().x);
	if(slider_emit->mouseIntersect()) slider_emit->changeValue(-Screen::getMouseMotion().x);
	color.setColor((unsigned char)(slider_red->getValue()*255.0f), (unsigned char)(slider_green->getValue()*255.0f), (unsigned char)(slider_blue->getValue()*255.0f), (unsigned char)(slider_emit->getValue()*255.0f));
}

Color ColorPanel::getColor(){
	return color;
}
