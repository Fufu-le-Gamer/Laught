#pragma once
#include "AnimationManager.h"
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Button
{
private:
	sf::Texture m_texture;
	sf::Sprite spriteButton;
	AnimationManager m_animManager;
	Character myCharacter;
public:
	Button();
	bool loadTextureButton(const std::string& path);
	bool isColliding(const sf::Sprite& a, const sf::Sprite& b);
	void playAnimation(Character& character);
	void setPositionButton(float x, float y);
	void setScaleButton(float sx, float sy);
	void drawButton(sf::RenderWindow& window) const;

};

