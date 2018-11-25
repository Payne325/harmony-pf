#include "Map.h"
#include <stdexcept>

Map::Map(
	int sizeX,
	int sizeY, 
	const std::vector<Point2>& obsticles)
{
	for(const Point2& point : obsticles)
	{
		if(point.X > sizeX || 
			point.X < 0 ||
			point.Y > sizeY ||
			point.Y < 0)
		{
			throw std::invalid_argument(
				"Obsticle out of bounds! Map Construction Failed!");
		}
	}

	m_sizeX = sizeX;
	m_sizeY = sizeY;

	m_mapSpace = new char*[m_sizeX];

	for(int i = 0; i < m_sizeX; ++i)
	{
		m_mapSpace[i] = new char[m_sizeY];
	}

	for(int i = 0; i < m_sizeX; ++i)
	{
		for(int j = 0; j < m_sizeY; ++j)
		{
			m_mapSpace[i][j] = 'E';
		}
	}

	for(const Point2& point : obsticles)
	{
		m_mapSpace[point.X][point.Y] = 'O';
	}
}

Map::~Map()
{
	for(int i = 0; i < m_sizeX; ++i)
	{
		delete [] m_mapSpace[i];
	}

	delete [] m_mapSpace;
}

bool Map::ContainsObsticles()
{
	for(int i = 0; i < m_sizeX; ++i)
	{
		for(int j = 0; j < m_sizeY; ++j)
		{
			if(m_mapSpace[i][j] == 'O') return true;
		}
	}

	return false;
}

Point2 Map::Size()
{
	return Point2(m_sizeX, m_sizeY);
}

bool Map::IsObsticle(const Point2& point)
{
	return m_mapSpace[point.X][point.Y] == 'O';
}