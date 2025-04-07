#include "HealthSystem.h"

void HealthSystem::takeDamage(int amount)
{
	m_currentHealth -= amount;
	if (m_currentHealth < 0)
	{
		m_currentHealth = 0;
	}
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
}

