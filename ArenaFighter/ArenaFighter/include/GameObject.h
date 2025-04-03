#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    virtual ~GameObject() = default;
    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void update(double dt) = 0;
    virtual void render(sf::RenderWindow& t_window, bool t_debugMode) = 0;
};

