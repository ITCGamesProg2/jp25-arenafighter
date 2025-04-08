#pragma once
class HealthSystem
{
public:
	HealthSystem(int maxHealth) : m_maxHealth(maxHealth), m_currentHealth(maxHealth) {}

/// <summary>
///  Deducts an input amount from whatever entities has the systems health
/// </summary>
	void takeDamage(int amount);

/// <summary>
/// Checks an entities health is above 0 and is therefore "alive" 
/// </summary>
/// <returns>True if health is > 0 </returns>
	bool isAlive() const;

	int getHealth() const;

	int getMaxHealth() const;

<<<<<<< HEAD
	void setHealth(int);
=======
	void increaseHealth();

>>>>>>> obstaclesAndPickups

private:

	int m_maxHealth;
	int m_currentHealth;
};

