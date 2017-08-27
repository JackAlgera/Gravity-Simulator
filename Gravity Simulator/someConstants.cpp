#include "someConstants.h"



someConstants::someConstants()
{
}


someConstants::~someConstants()
{
}

const float norme(sf::Vector2f u1, sf::Vector2f u2)
{
	float theNorme = sqrt(pow(u2.x - u1.x, 2) + pow(u2.y - u1.y, 2));
	if (theNorme < 30)
	{
		return 30;
	}
	else
	{
		return theNorme;
	}
}

const sf::Vector2f vectUni(float norme, sf::Vector2f u1, sf::Vector2f u2)
{
	return sf::Vector2f((u2.x - u1.x) / norme, (u2.y - u1.y) / norme); 
}
