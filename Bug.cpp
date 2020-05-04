#include "Bug.h"

Bug::Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, const Point* pointArray) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	//position will be dependent upon the path that is built for the bug
	buildPath(pointArray);
}

void Bug::buildPath(const Point* pointArray) // [0-10] are A-K, [11-17] are S1-S7
{

	// edges within range of spider: 0. B to E, 1. B to F, 2. B to G, 3. G to F, 4. G to H,
	// 5. H to C, 6. H to I, 7. D to I

	//choose danger edge
	srand(unsigned int(time(NULL)));
	int dangerCode = rand() % 8;
	switch (dangerCode)
	{
	case 0: // push B and E
		Path.push_back(*(pointArray + 1));
		Path.push_back(*(pointArray + 4));
		break;
	case 1: // push B and F
		Path.push_back(*(pointArray + 1));
		Path.push_back(*(pointArray + 5));
		break;
	case 2: // push B and G
		Path.push_back(*(pointArray + 1));
		Path.push_back(*(pointArray + 6));
		break;
	case 3: // push G and F
		Path.push_back(*(pointArray + 5));
		Path.push_back(*(pointArray + 6));
		break;
	case 4: // push G and H
		Path.push_back(*(pointArray + 6));
		Path.push_back(*(pointArray + 7));
		break;
	case 5: // push H and C
		Path.push_back(*(pointArray + 7));
		Path.push_back(*(pointArray + 2));
		break;
	case 6: // push H and I
		Path.push_back(*(pointArray + 7));
		Path.push_back(*(pointArray + 8));
		break;
	case 7: // push D and I
		Path.push_back(*(pointArray + 3));
		Path.push_back(*(pointArray + 8));
		break;
	}

	// build path from both ends until we hit a starting/end point
	// make sure there's no immediate doubling back (don't go A to B to A)
	const Point* newConnect = Path.begin()->getRandomConnection();
}