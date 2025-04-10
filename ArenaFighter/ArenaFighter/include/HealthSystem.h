#pragma once
#include "HealthObserverInterface.h"
#include <vector>
#include <algorithm>

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

	void setHealth(int);

	void increaseHealth(); 

	void attachObserver(HealthObserverInterface* observer);
	void detachObserver(HealthObserverInterface* observer);


private:

	int m_maxHealth;
	int m_currentHealth;

	void notifyObservers();

	std::vector<HealthObserverInterface*> m_observers;
};

