#include "AStar.h"

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