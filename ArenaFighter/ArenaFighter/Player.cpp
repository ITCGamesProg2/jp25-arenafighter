#include "Player.h"
#include <iostream>
Player::Player(thor::ResourceHolder<sf::Texture, std::string>& t_holder)
	: m_holder(t_holder)
{
	initSprites();
}

void Player::handleKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{

	}

}


void Player::update()
{


}

void Player::render(sf::RenderWindow& window)
{
	//window.draw(m_player);
}

void Player::initSprites()
{
	std::cout << "player created";
}

