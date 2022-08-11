#include "visualisation.h"
#include <iostream>

/*MAIN CONSTRUCTOR*/
visualisation::visualisation(int numberOfSorts, int width, int height, int position) {
	//Height = floor((float)rand() / RAND_MAX * 750.0f);	//UNCOMMENT FOR RANDOM GENERATION
	Height = floor(750.0f / numberOfSorts) * (position + 1);
	winHeight = height;
	Width = floor(width / numberOfSorts);
	Position = position;
	rect = sf::RectangleShape(sf::Vector2f(Width, Height));
	rect.setFillColor(sf::Color(255, 255, 255));
	rect.setPosition(sf::Vector2f(
		Width * Position,
		winHeight - Height
	));
}

/*BASIC CONSTRUCTOR OVERRIDDEN BY MAIN ONE ABOVE*/
visualisation::visualisation(){
	Height = 0;
	Width = 0;
	Position = 0;
	rect = sf::RectangleShape(sf::Vector2f(Height, Width));
}

/*IF SELECTED SET COLOR TO PARAM IF DESELECTED RESET TO DEFAULT*/
void visualisation::selected(sf::Color color) {
	rect.setFillColor(color);
}
void visualisation::deselected() {
	rect.setFillColor(sf::Color(255, 255, 255));
}

/*GET HEIGHT OF POLE TO SORT*/
float visualisation::getHeight() {
	return Height;
}

/*POSITION IS LINKED DIRECTLY TO ARRAYS POSITION*/
int visualisation::getPosition() {
	return Position;
}
void visualisation::setPosition(int position) {
	/*SET NEW POSITION AND UPDATE RECTANGLE POSITION*/
	Position = position;
	rect.setPosition(sf::Vector2f(
		Width * Position,
		winHeight - Height
	));
}

/*PRIMARY USE FOR DEBUGGING*/
sf::RectangleShape visualisation::getShape() {
	return rect;
}