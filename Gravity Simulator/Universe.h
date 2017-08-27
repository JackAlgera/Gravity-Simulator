#pragma once
#include <SFML\Graphics.hpp>
#include "Planet.h"

/*
Handles the differents planets.
*/

class Universe
{
public:
	Universe();
	~Universe();

	sf::Vector2f calForce(Planet plnt1, Planet plnt2);

	void addPlanet(float mass, sf::Vector2f pos, bool isMovable);
	void update(float dt);
	void draw(sf::RenderWindow& window);

	void emptyUniverse() { theSystem = {}; }
	void setLastRadius(int radius);
	void setLastColor(sf::Color color);
	void setLastMovable(bool movable);

	sf::Vector2f lastPlanetPos();

	void addVelocityLastPlanet(sf::Vector2i mousePos);
private:
	std::vector<Planet> theSystem = {};
};

