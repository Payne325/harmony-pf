#include "AStar.h"
#include <stdexcept>

namespace Algorithms
{
	AStar::AStar(
		char** map, 
		Point2 startPosition, 
		Point2 endPosition)
	{		
		m_map = map;
		m_startPosition = startPosition;
		m_endPosition = endPosition;

		if(startPosition.X < 0 ||
			startPosition.Y < 0)
		{
			throw std::invalid_argument(
				"StartPosition out of bounds! Algorithm Construction Failed!");
		}

		if(endPosition.X < 0 ||
			endPosition.Y < 0)
		{
			throw std::invalid_argument(
				"EndPosition out of bounds! Algorithm Construction Failed!");
		}
	}

	AStar::~AStar()
	{
		for(int i = 0; i < 32; ++i)
		{
			delete [] m_map[i];
		}

		delete [] m_map;	
	}

	Point2 AStar::StartPosition()
	{
		return m_startPosition;
	}

	Point2 AStar::EndPosition()
	{
		return m_endPosition;
	}

	bool AStar::MapContainsObsticles()
	{
		for(int i = 0; i < 32; ++i)
		{
			for(int j = 0; j < 32; ++j)
			{
				if(m_map[i][j] == 'O') 
					return true;
			}
		}

		return false;
	}
}