#include "Button.h"
#include "ResourceManager.h"
#include <iostream>

Button::Button(float pos_x, float pos_y, float width, float height, std::string _path) :path(_path)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->width = width;
	this->height = height;
	_textureID = ResourceManager::getTexture(path).id;
}

Button::~Button()
{
}
void Button::draw(SpriteBacth& spriteBatch, glm::vec2 position)
{
	pos_x = position.x;
	pos_y = position.y;
	Color color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(pos_x, pos_y, width, height);
	spriteBatch.draw(destRect, uvRect, _textureID, 0.0f, color);
} 


void Button::draw(SpriteBacth& spriteBatch)
{
	Color color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(pos_x, pos_y, width, height);
	spriteBatch.draw(destRect, uvRect, _textureID, 0.0f, color);
}

bool Button::click(glm::vec2 position)
{
	if (position.x >= pos_x && position.x <= (pos_x + width)) {
		std::cout << "Las x son iguales" << std::endl;
		if (position.y >= pos_y && position.y <= (pos_y + height)) {
			std::cout << "Las y son iguales" << std::endl;
			return true;
		}
	}
	return false;
}
