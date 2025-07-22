#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "visualisation.h"
#include <iostream>
#include <Windows.h>

/*FOR MAPPING VALUES BETWEEN RANGES. USED FOR PITCH CONTROL*/
#define MAP(X, MAX, MIN) (X-MIN)/(MAX-MIN)

/*VALUES THAT NEED TO BE VISUAL FOR ALL*/
extern int preJ = 0;
extern int valJ = 0;
extern int allDone = 0;

void bubbleSort(visualisation items[], int n, int j) {
	visualisation temp;
	if (items[j].getHeight() > items[j + 1].getHeight()) {
		items[preJ].deselected();			//use to be [j]
		items[preJ + 1].deselected();		//use to be [j+1]
		temp = items[j];
		items[j] = items[j+1];
		items[j].setPosition(j);
		items[j+1] = temp;
		items[j+1].setPosition(j+1);
		items[j].selected(sf::Color(255,0,0));
		items[j + 1].selected(sf::Color(255,0,0));
		preJ = j;
		allDone = 0;
	}
	else {
		items[j].selected(sf::Color(0, 255, 0));
		items[j + 1].selected(sf::Color(0, 255, 0));
	}

}

int main() {

	/*WINDOW SETTINGS AND GRAPHICS DETAIL*/
	const int width = 1200, height = 800;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(width, height), "Visual Representation of Bubble Sort", sf::Style::Default, settings);

	/*SETTING UP THE OBJECTS THAT NEEDED TO BE SORTED*/
	srand(time(NULL));
	int const numberOfSorts = 120;
	visualisation* items = new visualisation[numberOfSorts];
	for (int i = 0; i < numberOfSorts; i++) {
		items[i] = visualisation(numberOfSorts, width, height, i);
	}
	std::random_shuffle(&items[0], &items[numberOfSorts]);
	for (int i = 0; i < sizeof(*items) / sizeof(visualisation); i++) {
		items[i].setPosition(i);
	}

	/*SETTING UP AUDIO STREAM FOR SOUND EFFECTS WHEN SORTING*/
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("beep-08b.wav")) { return -1; }
	sf::Sound sound;
	sound.setBuffer(buffer);

	while (window.isOpen()) {

		/*KILL THE WINDOW OR NOT*/
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				window.close();
			}
		}

		/*SORTING ALGORITHM*/
		valJ++;
		if (valJ >= numberOfSorts - 1) { valJ = 0; }
		bubbleSort(items, numberOfSorts, valJ);

		/*DISPLAY TO WINDOW*/
		window.clear();
		for (int _pos = 0; _pos < numberOfSorts; _pos++) {

			/*IF STATEMENTS TO CHECK IF ALL DONE AND STOP NOISE EFFECTS*/
			if (items[_pos].getShape().getFillColor() == sf::Color(0, 255, 0)) { allDone++; }
			else { allDone = 0; }
			if (allDone > numberOfSorts) { sound.setVolume(0); }

			sound.setPitch(MAP(items[_pos].getHeight(), 750, 0));
			sound.play();
			window.draw(items[_pos].getShape());
		}
		window.display();
	}

	/*DELETE DYNAMIC POINTER TO PREVENT MEMORY LEAKS*/
	delete []items;
	return 0;
}
