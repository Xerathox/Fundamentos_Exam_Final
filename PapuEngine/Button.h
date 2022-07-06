#pragma once
#include <glm/glm.hpp>
#include <string>
#include "SpriteBacth.h"
#include "GLTexture.h"

class Button
{
private:
	std::string path;
	int _textureID;
public:
	float pos_x;
	float pos_y;
	float width;
	float height;
	Button(float pos_x, float pos_y, float width, float height, std::string _path);
	//Button(std::string _path);
	~Button();
	void draw(SpriteBacth& spriteBatch);
	void draw(SpriteBacth& spriteBatch, glm::vec2 position);
	bool click(glm::vec2 position);
};

