#include "Planet.h"
#include "someConstants.h"

Planet::Planet(float mass, sf::Vector2f posInit, bool isMovable)
{
	this->mass = mass;
	this->position = posInit;
	this->isMovable = isMovable;
	
	velocity = sf::Vector2f(0, 0);
	planetSprite = sf::CircleShape(radiusPlanet, pointCount);
	planetSprite.setOrigin(planetSprite.getLocalBounds().width / 2, planetSprite.getLocalBounds().height / 2);
	planetSprite.setFillColor(sf::Color::Yellow);
}

Planet::Planet()
{
}


Planet::~Planet()
{
}

sf::Vector2f Planet::totalForce()				//Returns the sum of all the forces being applied to the given planet, with a maximum force of <<maxForce = 75000>>, to avoid unnatural behaviors.
{
	int maxForce = 75000;

	sf::Vector2f totForce(0, 0);

	for (sf::Vector2f currentForce : forces)
		totForce += currentForce;
	if (totForce.x > maxForce)
	{
		if (totForce.y > maxForce)
		{
			return sf::Vector2f(maxForce, maxForce);
		}
		else
		{
			return sf::Vector2f(maxForce, totForce.y);
		}
	}
	if (totForce.y > maxForce)
	{
		return sf::Vector2f(totForce.x, maxForce);
	}

	if (totForce.x < -maxForce)
	{
		if (totForce.y < -maxForce)
		{
			return sf::Vector2f(-maxForce, -maxForce);
		}
		else
		{
			return sf::Vector2f(-maxForce, totForce.y);
		}
	}
	if (totForce.y < -maxForce)
	{
		return sf::Vector2f(totForce.x, -maxForce);
	}

	return totForce;
}

void Planet::addForce(sf::Vector2f newForce)
{
	forces.push_back(newForce);
}

void Planet::draw(sf::RenderWindow& window)
{
	planetSprite.setPosition(position);
	window.draw(planetSprite);
}

void Planet::update(float dt)
{

	sf::Vector2f totForce = this->totalForce();

	velocity += totForce * (dt / mass);
	position += velocity * dt;
}

void Planet::setRadius(int radius)
{
	planetSprite.setRadius(radius);
}

void Planet::setColor(sf::Color color)
{
	planetSprite.setFillColor(color);
}

void Planet::setVelocity(sf::Vector2f newVelocity)
{
	velocity = newVelocity;
}
