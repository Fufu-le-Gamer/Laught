#include "Button.h"

Button::Button()
	: m_texture()
	, spriteButton(m_texture)
	, m_animManager()
{
	spriteButton.setScale({ 4.f, 4.f });
}


bool Button::loadTextureButton(const std::string& path)
{
	if (!m_texture.loadFromFile(path))
		return false;
}
bool Button::isColliding(const sf::Sprite& a, const sf::Sprite& b)
{
	return a.getGlobalBounds().findIntersection(b.getGlobalBounds()).has_value();
}

void Button::playAnimation(Character& character)
{
	bool contact = isColliding(spriteButton, character.getSprite());

	if (!contact)
		spriteButton.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 14 }));
	else
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
			spriteButton.setTextureRect(sf::IntRect({ 0, 0 }, { 15, 14 }));   
		else
			spriteButton.setTextureRect(sf::IntRect({ 17, 0 }, { 14, 14 })); //pressé
}

void Button::setPositionButton(float x, float y)
{
	spriteButton.setPosition({ x, y });
}
void Button::setScaleButton(float sx, float sy)
{
	spriteButton.setScale({ sx, sy });
}
void Button::drawButton(sf::RenderWindow& window) const
{
	window.draw(spriteButton);
}
