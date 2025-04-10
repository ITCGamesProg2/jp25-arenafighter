#include "HealthSystem.h"

void HealthSystem::takeDamage(int amount)
{
	m_currentHealth -= amount;
	if (m_currentHealth < 0)
	{
		m_currentHealth = 0;
		
	}
	notifyObservers();
}

bool HealthSystem::isAlive() const
{
	return m_currentHealth > 0;
}

int HealthSystem::getHealth() const
{
	return m_currentHealth;
}

int HealthSystem::getMaxHealth() const
{
	return m_maxHealth;
}

void HealthSystem::setHealth(int health) 
{
	m_currentHealth = health;
	notifyObservers();
}


void HealthSystem::increaseHealth()
{
	m_currentHealth += 20;
	notifyObservers();
}

void HealthSystem::attachObserver(HealthObserverInterface* observer)
{
	m_observers.push_back(observer);
}

void HealthSystem::detachObserver(HealthObserverInterface* observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void HealthSystem::notifyObservers()
{
	for (auto observer : m_observers)
	{
		observer->onHealthChange(m_currentHealth);
	}
}

