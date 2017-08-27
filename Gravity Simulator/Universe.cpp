#include "Universe.h"
#include "someConstants.h"
#include <iostream>

Universe::Universe()
{
}


Universe::~Universe()
{
}

sf::Vector2f Universe::calForce(Planet plnt1, Planet plnt2)
{


	return sf::Vector2f();
}

void Universe::addPlanet(float mass, sf::Vector2f pos, bool isMovable)
{
	theSystem.push_back(Planet(mass, pos, isMovable));
}

void Universe::update(float dt)
{
	int nbrPlanets = theSystem.size();
	for (int i = 0; i < nbrPlanets; i++)
	{
		for (int j = i + 1; j < nbrPlanets; j++)
		{
			Planet planetI = theSystem[i];
			Planet planetJ = theSystem[j];

			float dist = norme(planetI.getPos(), planetJ.getPos());
			sf::Vector2f vect = vectUni(dist, planetI.getPos(), planetJ.getPos());
			
			sf::Vector2f forceIJ = ((G * planetI.getMass() * planetJ.getMass()) / pow(dist, 2)) * vect;

			theSystem[i].addForce(forceIJ);
			theSystem[j].addForce(-forceIJ);
		}
	}
	for (int i = 0; i < theSystem.size(); i++)
	{
		if (theSystem[i].isMovable)
		{
			theSystem[i].update(dt);
		}
		theSystem[i].clearForces();
	}
}

void Universe::draw(sf::RenderWindow& window)
{
	for (Planet plnt : theSystem)
	{
		plnt.draw(window);
	}
}

void Universe::setLastRadius(int radius)
{
	theSystem[theSystem.size() - 1].setRadius(radius);
}

void Universe::setLastColor(sf::Color color)
{
	theSystem[theSystem.size() - 1].setColor(color);
}

void Universe::setLastMovable(bool movable)
{
	theSystem[theSystem.size() - 1].isMovable = movable;
}

sf::Vector2f Universe::lastPlanetPos()
{
	return theSystem[theSystem.size() - 1].getPos();
}

void Universe::addVelocityLastPlanet(sf::Vector2i mousePos)
{
	float factorOfSpeed = 1.5;

	sf::Vector2f currentPosPlanet = theSystem[theSystem.size() - 1].getPos();

	sf::Vector2f initVelocity = (currentPosPlanet - (sf::Vector2f)mousePos);
	initVelocity = sf::Vector2f(initVelocity.x * factorOfSpeed, initVelocity.y * factorOfSpeed);

	theSystem[theSystem.size() - 1].setVelocity(initVelocity);
}
