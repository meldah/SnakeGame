#ifndef FOOD_H
#define FOOD_H

#include "GameObject.h"

//cstdlib for rand() function
#include <cstdlib>
#include <iostream>

class Food : public GameObject {
private:
	pos foodPos;

public:
	Food();
	~Food();

	void render();

	pos getFoodPos();
	void randomGenerate();
};

#endif