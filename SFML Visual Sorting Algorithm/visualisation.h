#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <math.h>

#ifndef VISUALISATION_H
#define VISUALISATION_H

class visualisation
{
private:
	sf::RectangleShape rect;
	float Height;
	float winHeight;
	float Width;
	int Position;
public:
	visualisation();
	visualisation(int numberOfSorts, int width, int height, int position);
	void selected(sf::Color color);
	void deselected();
	float getHeight();
	int getPosition();
	void setPosition(int position);
	sf::RectangleShape getShape();
};

#endif