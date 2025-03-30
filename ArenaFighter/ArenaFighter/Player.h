#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class Player
{
public:
	Player(thor::ResourceHolder <sf::Texture, std::string>& t_holder);


	void update();
	void render(sf::RenderWindow& window);
	void handleKeyInput();

private:
	void initSprites();
	sf::Sprite m_player;
	double m_speed{ 0.0 };
	thor::ResourceHolder<sf::Texture, std::string>& m_holder;
};
