#pragma once
#include <SFML\Graphics.hpp>

/*
Each planet has it's own mass, position and velocity aswel as a list of forces being applied to it. (e.g the other planets pulling on the given planet)
*/

class Planet
{
public:
	Planet(float mass, sf::Vector2f posInit, bool isMovable);

	Planet();
	~Planet();

	sf::Vector2f getPos() { return position; }
	float getMass() { return mass; }
	void clearForces() { forces.clear(); }

	sf::Vector2f totalForce();
	void addForce(sf::Vector2f newForce);
	void draw(sf::RenderWindow& window);

	void update(float dt);
	void setRadius(int radius);
	void setColor(sf::Color color);

	void setVelocity(sf::Vector2f newVelocity);
	
public:
	bool isMovable;

private:
	float mass;

	sf::Vector2f position;
	sf::Vector2f velocity;
	std::vector<sf::Vector2f> forces = {};

	sf::CircleShape planetSprite;

};

