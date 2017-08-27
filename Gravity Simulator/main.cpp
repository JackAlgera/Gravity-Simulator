#include <SFML\Graphics.hpp>
#include "Universe.h"
#include <iostream>

sf::Vector2f screenDimensions(900, 900);

/*
Gravity simulator.
Use the left mouse button to create small stars, a click and drag will give it an initial speed.
Use the right mouse button to create stationary stars with heavy mass that greatly attract the smaller ones.
Press R to refresh the simulation.

Author : Jacobus ALGERA
*/

int main()
{
	std::cout << "Welcome to the gravity simulator." << std::endl << std::endl << "Use the left mouse button to create small stars, a click and drag will give it an initial speed." << std::endl << "Use the right mouse button to create heavy stationary stars that greatly attract the smaller ones." << std::endl << "Press R to refresh the simulation." << std::endl << std::endl << "Enjoy!" << std::endl << std::endl << "Author : Jacobus ALGERA";
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Gravity Simulation", sf::Style::Default, settings);

	sf::Clock clock;						//Creation of the clock to help keep track of time

	Universe solarSystem;

	bool rightClick = false;							//Some variables used to know whether a new planet has been placed
	bool mouseClick = false;
	sf::Vector2f lastPlanetPos = sf::Vector2f(0, 0);

	sf::VertexArray vertexLine(sf::Lines, 2);			//variables used to draw the initial velocity vector
	sf::Color color = sf::Color::White;

	while (window.isOpen())
	{

		float dt = clock.restart().asSeconds();

		sf::Event evnt;
		while (window.pollEvent(evnt))					//Handles the different events
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					solarSystem.emptyUniverse();
				}
			}
			if (evnt.type == sf::Event::MouseMoved)		//Whenever the mouse has moved and a new planet is being spawned, a new velocity vector will be drawn
			{
				if (mouseClick)
				{
					vertexLine[0].position = lastPlanetPos;
					vertexLine[1].position = (sf::Vector2f)sf::Mouse::getPosition(window);

					vertexLine[0].color = color;
					vertexLine[1].color = color;

					window.draw(vertexLine);
				}
			}
			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))			//Left click to create small stars
				{
					sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
					solarSystem.addPlanet(100, mousePos, false);
					solarSystem.setLastRadius(5);
					solarSystem.setLastColor(sf::Color::Blue);

					lastPlanetPos = solarSystem.lastPlanetPos();
					mouseClick = true;

					vertexLine[0].position = lastPlanetPos;
					vertexLine[1].position = (sf::Vector2f)sf::Mouse::getPosition(window);

					vertexLine[0].color = color;
					vertexLine[1].color = color;

					window.draw(vertexLine);
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))			//Right click to create stationary planets with large mass
				{
					sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
					solarSystem.addPlanet(10000, mousePos, false);
					solarSystem.setLastRadius(15);

					rightClick = true;
				}
			}
			if (evnt.type == sf::Event::MouseButtonReleased)
			{
				if (!rightClick)
				{
					solarSystem.setLastMovable(true);
				}
				rightClick = false;
				mouseClick = false;

				solarSystem.addVelocityLastPlanet(sf::Mouse::getPosition(window));
			}
		}

		window.clear();
		solarSystem.update(dt);
		solarSystem.draw(window);

		if (mouseClick)
		{
			window.draw(vertexLine);
		}

		window.display();
	}

	return 0;
}