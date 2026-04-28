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

void Button::playAnimation(const std::string& texturePath)
{
	Character myCharacter;
	m_texture.loadFromFile(texturePath);
	spriteButton.setTexture(m_texture);

	sf::Sprite  characterSprite = myCharacter.getSprite();
	bool contact = isColliding(spriteButton, myCharacter.getSprite());
	if (spriteButton.getTextureRect().findIntersection(characterSprite.getTextureRect()).has_value())

		spriteButton.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 14 }));
	else
		spriteButton.setTextureRect(sf::IntRect({ 15, 0 }, { 16, 14 }));



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
