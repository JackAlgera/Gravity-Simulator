#pragma once
#include <SFML\Graphics.hpp>

/*
Some constants I use in the program and two useful functions.
*/

const int radiusPlanet = 5;
const int pointCount = 100;
const float G = 6.67*50;

const float norme(sf::Vector2f u1, sf::Vector2f u2);
const sf::Vector2f vectUni(float norme, sf::Vector2f u1, sf::Vector2f u2);

class someConstants
{
public:
	someConstants();
	~someConstants();
public:

};

