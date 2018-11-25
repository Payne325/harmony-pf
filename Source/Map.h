#include "Point2.h"
#include <vector>

class Map
{
public:
	Map(
		int sizeX,
		int sizeY, 
		const std::vector<Point2>& obsticles = std::vector<Point2>());

	~Map();

	bool ContainsObsticles();

	Point2 Size();

	bool IsObsticle(const Point2& point);

private:
	int m_sizeX;
	int m_sizeY;

	char** m_mapSpace;
};