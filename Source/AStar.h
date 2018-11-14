#include "IAlgorithm.h"

namespace Algorithms
{
	class AStar : public IAlgorithm
	{
	public:
		AStar(char** map, Point2 startPosition, Point2 endPosition);
		~AStar();
		
		Point2 StartPosition();
		Point2 EndPosition();

		bool MapContainsObsticles();

	private:

		char** m_map;
		Point2 m_startPosition;
		Point2 m_endPosition;
	};
}