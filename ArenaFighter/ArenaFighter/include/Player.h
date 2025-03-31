#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class Player
{
public:
	Player(thor::ResourceHolder <sf::Texture, std::string>& t_holder);


	void update(double dt);
	void render(sf::RenderWindow& window);
	void handleKeyInput();
	sf::FloatRect getBounds();

private:
	void initSprites();
	void animate(double dt);
	sf::Sprite m_player;
	double m_speed{ 2.0 };

	int m_frameSize = 100;
	double m_frameTimer = 0.0;
	double m_timePerFrame = 0.1;
	int currentFrame = 0;
	int m_col = 0;

	int m_walkFrames = 8;
	int m_idleFrames = 6;
	int m_walkRow = 1;
	int m_idleRow = 0;

	int m_playerState = 0; //0: idle   1: moving

	thor::ResourceHolder<sf::Texture, std::string>& m_holder;

};
