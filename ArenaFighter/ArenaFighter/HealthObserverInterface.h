#pragma once

class HealthObserverInterface
{
public:
	virtual ~HealthObserverInterface() = default;
	virtual void onHealthChange(int t_newHealth) = 0;
};